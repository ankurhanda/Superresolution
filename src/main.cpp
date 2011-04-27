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
#include "flow.h"
//#include "color_flow.h"
//#include "colorcode.h"

using namespace std;
using namespace pangolin;
using namespace CVD;

//#define TAG_FLOAT 202021.25  // check for this when READING the file
//#define TAG_STRING "PIEH"



//extern "C" void launch_kernel(float *var, unsigned int stride, unsigned int mesh_width, unsigned int mesh_height);
extern "C" void launch_kernel_update_u(float *px, float *py, float *u, float *u_, float* g, unsigned int stride,
                                       unsigned int mesh_width, unsigned int mesh_height, float tau, float lambda);

extern "C" void launch_kernel_dual_variable_p(float *px, float *py, float* ux_, float *uy_, float sigma, unsigned int stride,
                                              unsigned int mesh_width, unsigned int mesh_height);

extern "C" void launch_kernel_derivative_u(float* ux, float *uy, float* u_, unsigned int stride, unsigned int mesh_width, unsigned int mesh_height);




int width_window = 512;
int height_window = 512;


int main( int argc, char* argv[] )
{

    float L = sqrt(8);
    float tau = 1.0f/L;
    float sigma = 1.0f/L;
    float lambda = 10;


    cudaGLSetGLDevice(cutGetMaxGflopsDeviceId());
    CreateGlutWindowAndBind("Main",width_window*2,height_window*2);
    glewInit();

    CVD::Image<float> input_image;

    img_load(input_image,"../data/images/car_001_up.pgm");

    for(int i = 0 ; i < input_image.size().y; i++)
    {
        for(int j = 0 ; j < input_image.size().x ; j++)
        {
            cout << "val = " << input_image[ImageRef(j,i)] << endl;
        }
    }


    float** WMatvalPtr, *DMatvalPtr;
    int** WMatcolPtr, *DMatcolPtr;
    int** WMatrowPtr, *DMatrowPtr;

    int N_cols_low_img = input_image.size().x;
    int N_rows_low_img = input_image.size().y;

    int size_have  = N_rows_low_img*N_cols_low_img;

    float scale = 2;

    int N_rows_upimg = (int)(scale*N_rows_low_img);
    int N_cols_upimg = (int)(scale*N_cols_low_img);

    int size_wanted  = N_rows_upimg*N_cols_upimg;

    int N_rows = size_wanted, Nnz = size_wanted*4, N_imgs= 9, NnzDMat = 8*size_have;

//    CVD::Image<float>inputimages[N_imgs];


//    WMatvalPtr = (float**)malloc(sizeof(float*)*N_imgs);
//    WMatcolPtr = (int**)malloc(sizeof(int*)*N_imgs);
//    WMatrowPtr = (int**)malloc(sizeof(int*)*N_imgs);

    DMatvalPtr = (float*)malloc(sizeof(float*)*NnzDMat);
    DMatcolPtr = (int*)malloc(sizeof(int*)*NnzDMat);
    DMatrowPtr = (int*)malloc(sizeof(int*)*(size_have+1));

//    for (int i = 0 ; i < N_imgs; i++)
//    {
//        WMatvalPtr[i] = (float*)malloc(sizeof(float)*Nnz);
//        WMatcolPtr[i] = (int*)malloc(sizeof(int)*Nnz);
//        WMatrowPtr[i] = (int*)malloc(sizeof(int)*(N_rows+1));
//    }


    // Check if sparse matrix building is true!
    {
        //buildWMatrixBilinearInterpolation(N_imgs, N_rows_upimg, N_cols_upimg, WMatvalPtr, WMatrowPtr, WMatcolPtr);
//        scale = 2.4;
        buildDMatrixLebesgueMeasure(NnzDMat, N_rows_low_img, N_rows_upimg, N_cols_upimg, DMatvalPtr, DMatrowPtr, DMatcolPtr, scale);
    }

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

    size_t imagePitchFloat;

    float *d_DMatvalPtr;
    int *d_DMatcolPtr;
    int *d_DMatrowPtr;
    float *d_img;
    float *d_Ax;

    cutilSafeCall(cudaMalloc((void**)&d_DMatvalPtr, NnzDMat*sizeof (float)));
    cutilSafeCall(cudaMalloc((void**)&d_DMatcolPtr, NnzDMat*sizeof (int)));
    cutilSafeCall(cudaMalloc((void**)&d_DMatcolPtr, (size_have+1)*sizeof(int)));
    cutilSafeCall(cudaMalloc((void**)&d_Ax, size_have*sizeof(float)));
    cutilSafeCall(cudaMallocPitch(&(d_img ), &(imagePitchFloat), N_cols_upimg* sizeof (float), N_rows_upimg));



    cudaMemcpy(d_DMatvalPtr, DMatvalPtr, NnzDMat*sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_DMatcolPtr, DMatcolPtr, NnzDMat*sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_DMatrowPtr, DMatrowPtr, (size_have+1)*sizeof(int), cudaMemcpyHostToDevice);

    cutilSafeCall(cudaMemcpy2D(d_img,imagePitchFloat,input_image.data(),sizeof(float)*N_cols_upimg,sizeof(float)*N_cols_upimg,N_rows_upimg,cudaMemcpyHostToDevice));

    cusparseScsrmv(handle,CUSPARSE_OPERATION_NON_TRANSPOSE, size_have, size_wanted, 1.0, descr, d_DMatvalPtr, d_DMatrowPtr, d_DMatcolPtr, d_img, 0.0, d_Ax);

    float *h_Ax;
    h_Ax = (float*)malloc(sizeof(float)*size_have);
    cudaMemcpy(h_Ax,d_Ax,sizeof(float)*size_have,cudaMemcpyDeviceToHost);

    ofstream ofile("downsampled_image.txt");
    for (int i = 0 ; i < size_wanted;i++)
    {
        ofile<< h_Ax[i] << " ";
    }
    ofile << endl;


//    cusparseScsr2dense(handle,size_have,size_wanted,descr,d_DMatvalPtr,d_DMatrowPtr,d_DMatcolPtr,d_A,size_have);


//    float *h_A;

//    h_A = (float*)malloc(sizeof(float)*size_wanted*size_have);

//    cudaMemcpy(h_A,d_A,sizeof(float)*size_wanted*size_have,cudaMemcpyDeviceToHost);

//    ofstream ofile("D.txt");
//    for(int i = 0 ; i < size_wanted*size_have; i++)
//    {
//         ofile << h_A[i] << " ";
//    }
//    ofile << endl;
//    ofile.close();


//    cutilSafeCall(cudaMemcpy2D();





    /*
    // Read Input Images;
    for (int i = 0 ; i < N_imgs; i++)
    {
        char filename[30];
        sprintf(filename,"../data/images/car_%03d.pgm",i+1);
        img_load(inputimages[i],filename);
    }



    size_t imagePitchInt;

    float **d_valPtrW;
    int **d_colPtrW;
    int **d_rowPtrW;
    float **d_inputimages;

    float *d_p;
    float *d_u;
    float *d_u_;
    float **d_q;


    cutilSafeCall(cudaMallocPitch((d_valPtrW ), &(imagePitchFloat), size_wanted* sizeof (float), N_imgs));
    cutilSafeCall(cudaMallocPitch((d_colPtrW ), &(imagePitchInt), Nnz* sizeof (int), N_imgs));
    cutilSafeCall(cudaMallocPitch((d_rowPtrW ), &(imagePitchInt), (N_rows+2)* sizeof (int), N_imgs));
    cutilSafeCall(cudaMallocPitch((d_inputimages ), &(imagePitchFloat), (size_have)* sizeof(float), N_imgs));

    cutilSafeCall(cudaMallocPitch(&(d_p ), &(imagePitchFloat), size_wanted* sizeof (float), N_imgs));
    cutilSafeCall(cudaMallocPitch((d_q ), &(imagePitchFloat), size_wanted* sizeof (float), N_imgs));

    cutilSafeCall(cudaMallocPitch(&(d_u ), &(imagePitchFloat), size_wanted* sizeof (float), N_imgs));
    cutilSafeCall(cudaMallocPitch(&(d_ux_ ), &(imagePitchFloat), size_wanted* sizeof (float), N_imgs));
    cutilSafeCall(cudaMallocPitch(&(d_uy_ ), &(imagePitchFloat), size_wanted* sizeof (float), N_imgs));

    cutilSafeCall(cudaMemcpy2D(d_valPtrW,imagePitchFloat,valPtr,sizeof(float)*size_wanted,sizeof(float)*size_wanted,N_imgs,cudaMemcpyHostToDevice));
    cutilSafeCall(cudaMemcpy2D(d_colPtrW,imagePitchInt,colPtr,sizeof(int)*Nnz,sizeof(int)*Nnz,N_imgs,cudaMemcpyHostToDevice));
    cutilSafeCall(cudaMemcpy2D(d_rowPtrW,imagePitchInt,rowPtr,sizeof(int)*(N_rows+1),sizeof(int)*(N_rows+1),N_imgs,cudaMemcpyHostToDevice));

    for (int i = 0 ; i< N_imgs; i++)
    {
        cutilSafeCall(cudaMemcpy2D(d_inputimages[i],imagePitchFloat,inputimages[i],sizeof(int)*(size_have),sizeof(int)*(size_have),1,cudaMemcpyHostToDevice));
    }
    */

    int width = input_image.size().x;
    int height = input_image.size().y;

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




    long doIt =0;
    while(!pangolin::ShouldQuit())
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        {
//            if(doIt%100==0){

//                    ScopedCuTimer cuTime("Iteration time");

//                    launch_kernel_derivative_u(ux_,uy_,u_,imageStrideFloat,N_cols_upimg, N_rows_upimg);
//                    launch_kernel_dual_variable_p(px,py,ux_,uy_,sigma,imageStrideFloat,N_cols_upimg,N_rows_upimg);

//                    for (int i = 0 ; i < N_imgs; i++)
//                    {
//                         // use cusparse to find out DBW_u..

//                    }

//                    launch_kernel_dual_variable_q(N_imgs, q, DBWu_,epsilon_d, sigma, f, xisqr,imageStride, N_cols_upimg, N_rows_upimg);

//                    for (int i = 0 ; i < N_imgs; i++)
//                    {
//                         // use cusparse to sum up the qs ..
//                    }

//                    launch_kernel_update_u(px,py,u,u_,sum_wiT_biT_diT_q,imageStrideFloat,N_cols_upimg,N_rows_upimg,tau,xisqr);

//            }
//            doIt++;

            //do some display stuff
            {

//                view_image0.ActivateScissorAndClear();
//                DisplayFloatDeviceMem(&view_image0, d_Ax,imagePitchFloat, greypbo,greyTexture);

//                view_image1.ActivateScissorAndClear();
//                DisplayFloatDeviceMem(&view_image1, d_img,imagePitchFloat, greypbo,greyTexture);

//                view_image2.ActivateScissorAndClear();
//                DisplayFloatDeviceMem(&view_image2, d_img,imagePitchFloat, greypbo,greyTexture);

            }
        }


        //        if(HadInput())
        //        d_panel.Render();

        glutSwapBuffers();
        glutMainLoopEvent();
    }

    return 0;
}
