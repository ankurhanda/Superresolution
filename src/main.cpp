#include <limits>
#include <iostream>
#include <pangolin/pangolin.h>
#include <pangolin/glcuda.h>

#include <cuda_runtime.h>
#include <cutil_inline.h>
#include <cutil_gl_inline.h>
#include <cutil_gl_error.h>
#include <cuda_gl_interop.h>
#include <vector_types.h>

#include <cvd/image.h>
#include <cvd/image_io.h>
#include <cvd/image_ref.h>

#include <shrUtils.h>
#include <shrQATest.h>
#include <cutil_inline.h>
#include <cusparse.h>
#include <cublas.h>

#include "utils.h"

using namespace std;
using namespace pangolin;
using namespace CVD;




//extern "C" void launch_kernel(float *var, unsigned int stride, unsigned int mesh_width, unsigned int mesh_height);
extern "C" void launch_kernel_update_u(float *px, float *py, float *u, float *u_, float* g, unsigned int stride,
                                       unsigned int mesh_width, unsigned int mesh_height, float tau, float lambda);

extern "C" void launch_kernel_dual_variable_p(float *px, float *py, float* ux_, float *uy_, float sigma, unsigned int stride,
                                              unsigned int mesh_width, unsigned int mesh_height);

extern "C" void launch_kernel_derivative_u(float* ux, float *uy, float* u_, unsigned int stride, unsigned int mesh_width, unsigned int mesh_height);




int width = 512;
int height = 512;


int main( int /*argc*/, char* argv[] )
{

    float L = sqrt(8);
    float tau = 1.0f/L;
    float sigma = 1.0f/L;
    float lambda = 10;


    cudaGLSetGLDevice(cutGetMaxGflopsDeviceId());
    CreateGlutWindowAndBind("Main",width*2,height*2);
    glewInit();

    CVD::Image<float> input_image;

    img_load(input_image,"../src/lena_sigma25.png");


    size_t imagePitchFloat;
    float * d_data;
    float* px;
    float* py;
    float *ux_, *uy_, *u_, *u;
    float * input_img_data;
    float *g;

    input_img_data = (float*)malloc(sizeof(float)*width*height);

    input_img_data = input_image.data();


    cutilSafeCall(cudaMallocPitch(&(d_data ), &(imagePitchFloat), width* sizeof (float), height));

    cutilSafeCall(cudaMallocPitch(&(px ), &(imagePitchFloat), width* sizeof (float), height));
    cutilSafeCall(cudaMallocPitch(&(py ), &(imagePitchFloat), width* sizeof (float), height));

    cutilSafeCall(cudaMallocPitch(&(ux_ ), &(imagePitchFloat), width* sizeof (float), height));
    cutilSafeCall(cudaMallocPitch(&(uy_ ), &(imagePitchFloat), width* sizeof (float), height));

    cutilSafeCall(cudaMallocPitch(&(u ), &(imagePitchFloat), width* sizeof (float), height));
    cutilSafeCall(cudaMallocPitch(&(u_ ), &(imagePitchFloat), width* sizeof (float), height));

    cutilSafeCall(cudaMallocPitch(&(g ), &(imagePitchFloat), width* sizeof (float), height));

    cutilSafeCall(cudaMemcpy2D(d_data, imagePitchFloat, input_img_data, sizeof(float)*width, sizeof(float)*width, height, cudaMemcpyHostToDevice));
    cutilSafeCall(cudaMemcpy2D(g, imagePitchFloat, input_img_data, sizeof(float)*width, sizeof(float)*width, height, cudaMemcpyHostToDevice));



    cutilSafeCall(cudaMemset(px,0,sizeof(float)*width*height));
    cutilSafeCall(cudaMemset(py,0,sizeof(float)*width*height));

    cutilSafeCall(cudaMemset(ux_,0,sizeof(float)*width*height));
    cutilSafeCall(cudaMemset(uy_,0,sizeof(float)*width*height));

    cutilSafeCall(cudaMemset( u,0,sizeof(float)*width*height));
    cutilSafeCall(cudaMemset(u_,0,sizeof(float)*width*height));


    float aspect = width*1.0f/height*1.0f;

    GlTexture greyTexture(width,height,GL_LUMINANCE32F_ARB);
    GlBufferCudaPtr greypbo( GlPixelUnpackBuffer, width*height*sizeof(float), cudaGraphicsMapFlagsNone, GL_STREAM_DRAW );


    View& view_image0 = Display("image0").SetAspect(aspect);
    View& view_image1 = Display("image1").SetAspect(aspect);
    View& view_image2 = Display("image2").SetAspect(aspect);
    View& view_image3 = Display("image3").SetAspect(aspect);


    View& d_panel = pangolin::CreatePanel("ui")
                    .SetBounds(1.0, 0.0, 0, 150);



    View& d_imgs = pangolin::Display("images")
                   //.SetBounds(1.0, 0.8, 150, 1.0, false)
                   //first distance from bottom left of opengl window i.e. 0.7 is 70%
                   //co-ordinate from bottom left of screen from
                   //0.0 to 1.0 for top, bottom, left, right.
                   .SetBounds(1.0, 0.5, 150/*cus this is width in pixels of our panel*/, 1.0, false)
                   .SetLayout(LayoutEqual)
                   .AddDisplay(view_image0)
                   .AddDisplay(view_image1)
                   .AddDisplay(view_image2)
                   .AddDisplay(view_image3)
                   ;




    int imageStrideFloat=imagePitchFloat/sizeof(float);

    cusparseHandle_t handle = 0;
    cusparseStatus_t status;
    status = cusparseCreate(&handle);
    if (status != CUSPARSE_STATUS_SUCCESS) {
        fprintf( stderr, "!!!! CUSPARSE initialization error\n" );
        return EXIT_FAILURE;
    }


    cusparseMatDescr_t descr = 0;
    status = cusparseCreateMatDescr(&descr);
    if (status != CUSPARSE_STATUS_SUCCESS) {
        fprintf( stderr, "!!!! CUSPARSE cusparseCreateMatDescr error\n" );
        return EXIT_FAILURE;
    }
    cusparseSetMatType(descr,CUSPARSE_MATRIX_TYPE_GENERAL);
    cusparseSetMatIndexBase(descr,CUSPARSE_INDEX_BASE_ZERO);



    long doIt =0;
    while(!pangolin::ShouldQuit())
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //static Var<float> lambda_val("ui.lambda_val",10,100);
        // static Var<bool> doIt("ui.doit",false,false);

        //        lambda = lambda_val;

        //if((doIt))
        {
            if(doIt%100==0){
                //cout<<"It:" << (doIt/100) <<endl;

                    ScopedCuTimer cuTime("Iteration time");
                    launch_kernel_derivative_u(ux_,uy_,u_,imageStrideFloat,width, height);
                    launch_kernel_dual_variable_p(px,py,ux_,uy_,sigma,imageStrideFloat,width,height);
                    launch_kernel_update_u(px,py,u,u_,g,imageStrideFloat,width,height,tau,lambda);

            }
            doIt++;

            //do some display stuff
            {

                view_image0.ActivateScissorAndClear();
                DisplayFloatDeviceMem(&view_image0, d_data,imagePitchFloat, greypbo,greyTexture);

                view_image1.ActivateScissorAndClear();
                DisplayFloatDeviceMem(&view_image1, ux_,imagePitchFloat, greypbo,greyTexture);

                view_image2.ActivateScissorAndClear();
                DisplayFloatDeviceMem(&view_image2, u,imagePitchFloat, greypbo,greyTexture);

            }
        }


        //        if(HadInput())
        //        d_panel.Render();

        glutSwapBuffers();
        glutMainLoopEvent();
    }


    return 0;
}
