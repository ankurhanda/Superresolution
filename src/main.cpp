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

//extern "C" void launch_kernel(int *d_Darray, int size);



int width_window = 512;
int height_window = 512;


int main( int argc, char* argv[] )
{

    //buildWMatrixBilinearInterpolation(N_imgs, N_rows_upimg, N_cols_upimg, WMatvalPtr, WMatrowPtr, WMatcolPtr);

    float L = sqrt(8);
    float tau = 1.0f/L;
    float sigma = 1.0f/L;
    float lambda = 10;


    /*cudaGLSetGLDevice(cutGetMaxGflopsDeviceId());
    CreateGlutWindowAndBind("Main",width_window*2,height_window*2);
    glewInit();*/

    CVD::Image<float> input_image;

    img_load(input_image,"../data/images/car_001.pgm");

    int N_cols_low_img = 4;
    int N_rows_low_img = 4;

    int size_have  = N_rows_low_img*N_cols_low_img;
    float scale = 2;

    int N_rows_upimg = (int)(scale*N_rows_low_img);
    int N_cols_upimg = (int)(scale*N_cols_low_img);
    int size_wanted  = N_rows_upimg*N_cols_upimg;
    int NnzDMat = 4*size_have;


    float *DMatvalPtr = new float[NnzDMat];
    int *DMatcolPtr = new int[NnzDMat];
    int *DMatrowPtr = new int[size_have+1];

    TooN::Matrix<>A(size_have,size_wanted);
    A = TooN::Zeros(size_have,size_wanted);

    std::map<int,float>matindex_matval;

    //DMatvalPtr, DMatrowPtr, DMatcolPtr,
    buildDMatrixLebesgueMeasure(NnzDMat, size_have,size_wanted, N_rows_upimg, N_cols_upimg, scale, A, matindex_matval);
    cout << "In here" << endl;

//    for(int i = 0; i< NnzDMat ; i++)
//    {

//    }

//    sort(matindex_matval.begin(),matindex_matval.end());


    std::map<int,float>::iterator it;
    cout << "Map begins " << endl;

    for(int i = 0 ; i < size_have ; i++)
    {
        DMatrowPtr[i] = 0;
    }
    DMatrowPtr[size_have] = NnzDMat;

    int index = 0, prev_row = -1;
    for(it = matindex_matval.begin(); it != matindex_matval.end(); it++ )
    {
        cout << (it->first)%size_wanted << " " ;//<< it->second << endl;
        DMatvalPtr[index] = (it->second);
        DMatcolPtr[index] = (it->first)%size_wanted;

        int row = ((it->first) - (it->first)%size_wanted)/size_wanted;

        if ( DMatrowPtr[row] == 0 && prev_row != row)
        {
            DMatrowPtr[row] = index;
            prev_row = row;
        }

        index++;
    }
    cout << endl;

    cout << "DMatcolPtr" << endl;
    cout << "index = " << index << endl;
    cout << "NnzDMat = " << NnzDMat << endl;
    for(int i = 0 ; i < NnzDMat ; i++ )
    {
        cout << DMatcolPtr[i] << " ";
    }
    cout << endl;


    cout <<"A Matrix" << endl;
    cout << A << endl;


    cout << "DMatrowPtr = " << endl;
    for(int i = 0; i < size_have+1 ; i++)
    {
        cout << DMatrowPtr[i] << " ";
    }
    cout << endl;

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
    float *d_A;
    float *d_A_copy;
    float *h_A;


    cutilSafeCall(cudaMalloc((void**)&d_DMatvalPtr, NnzDMat*sizeof (float)));

    cutilSafeCall(cudaMalloc((void**)&d_DMatcolPtr, NnzDMat*sizeof (int)));

    cutilSafeCall(cudaMalloc((void**)&d_DMatrowPtr, (size_have+1)*sizeof(int)));
    cutilSafeCall(cudaMalloc((void**)&d_A, (size_have)*sizeof(float)*size_wanted));

    cutilSafeCall(cudaMalloc((void**)&d_A_copy, (size_have)*sizeof(float)*size_wanted));
    cutilSafeCall(cudaMallocPitch(&(d_img ), &(imagePitchFloat), N_cols_upimg* sizeof (float), N_rows_upimg));

    cudaMemcpy(d_DMatvalPtr, DMatvalPtr, NnzDMat*sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_DMatcolPtr, DMatcolPtr, NnzDMat*sizeof(int), cudaMemcpyHostToDevice);

    cudaMemcpy(d_DMatrowPtr, DMatrowPtr, (size_have+1)*sizeof(int), cudaMemcpyHostToDevice);





    int* h_nnzPerRow;
    int* d_nnzPerRow;

    float* d_csrValA;
    float* h_csrValA;

    int* d_csrRowPtrA;
    int* h_csrRowPtrA;

    int* d_csrColIndA;
    int* h_csrColIndA;


    cutilSafeCall(cudaMalloc((void**)&d_nnzPerRow, size_have*sizeof (int)));
    cutilSafeCall(cudaMalloc((void**)&d_csrRowPtrA, (size_have+1)*sizeof (int)));
    cutilSafeCall(cudaMalloc((void**)&d_csrColIndA, NnzDMat*sizeof (int)));
    cutilSafeCall(cudaMalloc((void**)&d_csrValA, NnzDMat*sizeof (float)));


    h_nnzPerRow  = (int*)malloc(sizeof(int)*size_have);
    h_csrValA    = (float*)malloc(sizeof(float)*NnzDMat);
    h_csrRowPtrA = (int*)malloc(sizeof(int)*(size_have+1));
    h_csrColIndA = (int*)malloc(sizeof(int)*size_have);
    h_A          = (float*)malloc(sizeof(float)*size_have*size_wanted);

    for (int i  = 0 ; i < size_have;i++)
        h_nnzPerRow[i] = 4;

    cout << endl;
    index = 0;
    for(int i = 0 ; i < size_have ; i++)
    {
        for(int j = 0 ; j < size_wanted; j++)
        {
            index = i*size_wanted+j;
            h_A[index] = A(i,j);
//            cout << A(i,j) << " ";
            index++;
        }
    }


    float* h_A_permuted = new float[size_have*size_wanted];
    int H = size_have, x = 0;

    for(int i = 0 ; i < size_have*size_wanted ; i++ )
    {
        h_A_permuted[i] = h_A[x];
        x = x + H;
        if ( x >= size_wanted*size_have)
        {
            static int count = 1;
            x = count;
            count++;
        }
    }

    cout<<  endl << "h_A is" << endl;
    for(int i = 0 ; i < size_have*size_wanted;i++)
    {
        cout << h_A[i] << " ";
    }
    cout << endl;

    cout << "h_A_permuted is" << endl;
    for(int i = 0 ; i < size_have*size_wanted;i++)
    {
        cout << h_A_permuted[i] << " ";
    }
    cout << endl;


    TooN::Matrix<>newA(size_have,size_wanted);
    for(int i = 0 ; i < size_have ; i++ )
    {
        for(int j = 0 ; j < size_wanted ; j++ )
        {
            int idx = i*size_wanted + j;
            newA(i,j) = h_A_permuted[idx];
        }
    }

    cout<<"A permuted"<<endl;
    cout << newA<<endl;



    cudaMemcpy(d_A,h_A,sizeof(float)*size_have*size_wanted,cudaMemcpyHostToDevice );
    cudaMemcpy(d_nnzPerRow,h_nnzPerRow,sizeof(int)*size_have,cudaMemcpyHostToDevice );


   cusparseSdense2csr(handle,size_have,size_wanted,descr,d_A,size_have,d_nnzPerRow,d_csrValA,d_csrRowPtrA,d_csrColIndA);

   cudaMemcpy(h_csrValA,d_csrValA,sizeof(float)*NnzDMat,cudaMemcpyDeviceToHost );
   cudaMemcpy(h_csrRowPtrA,d_csrRowPtrA,sizeof(int)*(size_have+1),cudaMemcpyDeviceToHost );
   cudaMemcpy(h_csrColIndA,d_csrColIndA,sizeof(int)*NnzDMat,cudaMemcpyDeviceToHost );


   cout <<"\n Here is the csrRowPtr at Host" << endl;
   for(int i = 0 ; i < size_have+1; i++)
   {
       cout << h_csrRowPtrA[i]<<" ";
   }
   cout << endl;

   for(int i = 0 ; i < NnzDMat ; i++)
   {
       cout << h_csrColIndA[i] << " ";
   }
   cout << endl;

    cusparseStatus_t status_t;

    status_t = cusparseScsr2dense(handle,size_have,size_wanted,descr,d_DMatvalPtr,d_DMatrowPtr,d_DMatcolPtr,d_A_copy,size_have);

    if ( status_t == CUSPARSE_STATUS_SUCCESS)
    {
        cout << "Bingo!" << endl;
    }


    float *hh_A;

    hh_A = (float*)malloc(sizeof(float)*size_wanted*size_have);

    cudaMemcpy(hh_A,d_A_copy,sizeof(float)*size_wanted*size_have,cudaMemcpyDeviceToHost);
    cout << "hh_A copied here" << endl;
    for(int i = 0 ; i < size_wanted*size_have;i++)
    {
        cout << hh_A[i] << " ";
    }
    cout << endl;
    cout << "Copied Data!" << endl;


//    for (int i = 0 ; i < size_have ; i++)
//    {
//        for(int j = 0 ; j < size_wanted ; j++)
//        {

//            A(i,j) = hh_A[j+i*size_wanted];

//        }
//    }
//    A = TooN::Matrix<>(hh_A,size_have,size_wanted);
//    cout << endl;
//    cout<< A << endl;




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

    /*int width = input_image.size().x;
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
                 .SetBounds(1.0, 0.5, 150, 1.0, false)
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

                view_image1.ActivateScissorAndClear();
                DisplayFloatDeviceMem(&view_image1, d_img,imagePitchFloat, greypbo,greyTexture);

//                view_image2.ActivateScissorAndClear();
//                DisplayFloatDeviceMem(&view_image2, d_img,imagePitchFloat, greypbo,greyTexture);

            }
        }


        //        if(HadInput())
        //        d_panel.Render();

        glutSwapBuffers();
        glutMainLoopEvent();
    }
   */

    return 0;
}
