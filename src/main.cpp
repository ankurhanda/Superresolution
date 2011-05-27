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

#include <sstream>
#include <fstream>

//#include <thrust/host_vector.h>
//#include <thrust/device_vector.h>
//#include <thrust/tuple.h>

#include "utils.h"
#include "flow.h"


using namespace std;
using namespace pangolin;
using namespace CVD;

//#define TAG_FLOAT 202021.25  // check for this when READING the file
//#define TAG_STRING "PIEH"




extern "C" void launch_kernel_primal_u(float *px, float *py, float* u_, float *u, int upImageStrideFloat, float epsilon_u, float* d_tau, float xisqr, float *WiT_BiT_DiT_qi,
                                       unsigned int WTBTDTstride, unsigned int width_up, unsigned int height_up, int N_imgs);

//extern "C" void launch_kernel_q_SubtractDBWiu_fAdd_yAndReproject(float *d_qi, int qStride,
//                                                                 float *d_DBWiu_fi, int DBWiu_fiStride,
//                                                                 float sigma_q,float xisqr,float epsilon_d,
//                                                                 int width_down, int height_down);


extern "C" void launch_kernel_q_SubtractDBWiu_fAdd_yAndReproject(float *d_qi, int qStride,
                                                                 float *d_DBWiu_fi, int DBWiu_fiStride,
                                                                 float sigma_q,float xisqr,float epsilon_d,
                                                                 int N_cols_low_img, int N_rows_low_img, int N_imgs);


extern "C" void launch_kernel_dual_variable_p(float *px, float *py, float* ux_, float *uy_, float epsilon_u, float sigma, float lambda,
                                              unsigned int stride, unsigned int mesh_width, unsigned int mesh_height);

extern "C" void launch_kernel_blur(float *out, int outStride, float *in, int inStride, float* blur_kernel, int blurWidth, int width, int height);

extern "C" void launch_kernel_Mult_Wi_u(float *out, int outStride, float *d_u_, int u_Stride, float *horizontal_flow, float* vertical_flow, int velStride,
                                         int imgNo, int width, int height);

extern "C" void launch_kernel_derivative_u(float* ux_, float *uy_, float* u_, unsigned int stride, unsigned int mesh_width, unsigned int mesh_height);


extern "C" void  launch_kernel_subtract(float* d_fi, int imgVectorsStrideFloat, float* d_res_stacked, int qVectorsStrideFloat, int size, int width, int height);


//extern "C" void launch_kernel_dual_variable_p(float *px, float *py, float* ux_, float *uy_, float epsilon_u, float sigma_p, float lambda,
//                                              unsigned int stride, unsigned int mesh_width, unsigned int mesh_height)

int width_window = 512;
int height_window = 512;


















int main( int argc, char* argv[] )
{




    srand ( time(NULL) );


    cudaGLSetGLDevice(cutGetMaxGflopsDeviceId());
    CreateGlutWindowAndBind("Main",width_window*2,height_window*2);
    glewInit();


    CVD::Image<float> input_image_low;
    img_load(input_image_low,"../data/images/car_003.pgm");

    CVD::Image<float> input_image_up;
    img_load(input_image_up,"../data/images/car_003_up.pgm");

    cout<< "height_up_image ="<< input_image_up.size().y << endl;
    cout<< " width_up_image ="<< input_image_up.size().x << endl;



    int N_cols_low_img = input_image_low.size().x;
    int N_rows_low_img = input_image_low.size().y;

    int size_have  = N_rows_low_img*N_cols_low_img;
    float scale = 2;

    int N_rows_upimg = (int)(scale*N_rows_low_img);
    int N_cols_upimg = (int)(scale*N_cols_low_img);

    int size_wanted  = N_rows_upimg*N_cols_upimg;


    int input_vector_size = size_wanted;
    float *input_image_data_up = new float[size_wanted];

//    for(int i = 0 ; i < input_vector_size ; i++)
//    {
//        input_image_data_up[i] = i;
//    }

    float *input_image_data_down = new float[size_have];

//    for(int i = 0 ; i < size_have ; i++)
//    {
//        input_image_data_down[i] = i;
//    }

    input_image_data_up = input_image_up.data();






    //############################### Computing the W^{T}'s for all the flow vectors ###########################

    int N_imgs = 9;
    std::vector< std::map <int, float> > h_vectorofMaps(N_imgs);

    int test_size = 8*8;
    float *hflow = new float [test_size];
    float *vflow = new float [test_size];

    buildWMatrixBilinearInterpolation(N_imgs, size_wanted, N_rows_upimg, N_cols_upimg, h_vectorofMaps, hflow, vflow);//,WMatT );
//    buildWMatrixBilinearInterpolation(N_imgs, test_size, 8, 8, h_vectorofMaps, hflow, vflow);//,WMatT );



    float **WMatvalPtr;
    WMatvalPtr = (float**)malloc(sizeof(float*)*N_imgs);

    int **WMatcolPtr;
    WMatcolPtr = (int**)malloc(sizeof(int*)*N_imgs);

    int **WMatrowPtr;
    WMatrowPtr = (int**)malloc(sizeof(int*)*N_imgs);

    int **h_nnzPerRow;
    h_nnzPerRow = (int**)malloc(sizeof(int*)*N_imgs);



    float *d_csrWMatStackedval;
    int *d_csrWMatStackedrow;
    int *d_csrWMatStackedcol;




    int total_nonzeros=0;

    for(int i = 0 ; i < N_imgs ; i++)
    {
        std::map<int, float>::iterator it;
        std::map<int, float> mapW = h_vectorofMaps[i];
        total_nonzeros += (int)mapW.size();

    }






    float *h_csrWMatStackedval = new float[total_nonzeros];
    int *h_csrWMatStackedrow = new int[size_wanted*N_imgs+1];
    int *h_csrWMatStackedcol = new int[total_nonzeros];


    float *d_WMatvalPtr;
    int *d_WMatrowPtr;
    int *d_WMatcolPtr;


    for(int i = 0 ; i < N_imgs ; i++)
    {
        std::map<int, float>::iterator it;
        std::map<int, float> mapW = h_vectorofMaps[i];

        int NnzWMat = (int)mapW.size();

        WMatvalPtr[i] = new float[NnzWMat];
        WMatcolPtr[i] = new int[NnzWMat];
        WMatrowPtr[i] = new int[size_wanted+1];
        h_nnzPerRow[i] = new int[size_wanted];

        int index = 0, prev_row=-1;

        cout<< "NnzWMat = "<<NnzWMat <<endl;

        WMatrowPtr[i][0] = 0;
        h_nnzPerRow[i][0] = 0;

        for(int j = 1 ; j < size_wanted; j++)
        {
            WMatrowPtr[i][j] =-1;
            h_nnzPerRow[i][j] = 0;
        }
        WMatrowPtr[i][size_wanted] = NnzWMat;

        cout<<"have initialised the matrices"<<endl;

        index = 0;
        for(it = mapW.begin(); it != mapW.end() ; it++)
        {

            WMatcolPtr[i][index] = (it->first)%size_wanted;
            WMatvalPtr[i][index] = (it->second);

            int row = ((it->first) - (it->first)%size_wanted)/size_wanted;
            h_nnzPerRow[i][row]++;

            if ( WMatrowPtr[i][row] == -1 && prev_row != row)
            {
                WMatrowPtr[i][row] = index;
                prev_row = row;
            }
            index++;

        }

        index = 1;
        while(1)
        {
            if( index > size_wanted)
                break;

            int startindex = index;
            while( WMatrowPtr[i][index] == -1)
            {
                index++;
            }
            for(int j = startindex; j <= index-1 ; j++)
            {
                WMatrowPtr[i][j] = WMatrowPtr[i][index];
            }
            index++;
        }
        WMatrowPtr[i][0] = 0;


        if ( i == 0)
        {

            cutilSafeCall(cudaMalloc((void**)&d_WMatvalPtr, NnzWMat*sizeof (float)));
            cutilSafeCall(cudaMalloc((void**)&d_WMatcolPtr, (NnzWMat)*sizeof(int)));
            cutilSafeCall(cudaMalloc((void**)&d_WMatrowPtr, (size_wanted+1)*sizeof (int)));

            cudaMemcpy(d_WMatvalPtr, WMatvalPtr[i], NnzWMat*sizeof(float), cudaMemcpyHostToDevice);
            cudaMemcpy(d_WMatcolPtr, WMatcolPtr[i], NnzWMat*sizeof(int), cudaMemcpyHostToDevice);
            cudaMemcpy(d_WMatrowPtr, WMatrowPtr[i], (size_wanted+1)*sizeof(int), cudaMemcpyHostToDevice);

        }

        static int total_non_zeros_so_far = 0;

        for(int index = 0 ; index < NnzWMat ; index++)
        {
            h_csrWMatStackedval[total_non_zeros_so_far + index] = WMatvalPtr[i][index];
            h_csrWMatStackedcol[total_non_zeros_so_far + index] = WMatcolPtr[i][index];
        }

        for(int rv = 0 ; rv < size_wanted ; rv++)
        {
            h_csrWMatStackedrow[rv+size_wanted*i] = WMatrowPtr[i][rv] + total_non_zeros_so_far;
        }

        total_non_zeros_so_far = total_non_zeros_so_far +NnzWMat;
    }

    h_csrWMatStackedrow[size_wanted*N_imgs] = total_nonzeros;






    cutilSafeCall(cudaMalloc((void**)&d_csrWMatStackedval, total_nonzeros*sizeof (float)));
    cutilSafeCall(cudaMalloc((void**)&d_csrWMatStackedcol, (total_nonzeros)*sizeof(int)));
    cutilSafeCall(cudaMalloc((void**)&d_csrWMatStackedrow, (N_imgs*size_wanted+1)*sizeof (int)));

    cudaMemcpy(d_csrWMatStackedval, h_csrWMatStackedval, total_nonzeros*sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_csrWMatStackedcol, h_csrWMatStackedcol, total_nonzeros*sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_csrWMatStackedrow, h_csrWMatStackedrow, (size_wanted*N_imgs+1)*sizeof(int), cudaMemcpyHostToDevice);

   //###########################################################################################################

    float sigma_kernel = 0.25* ( sqrt(scale*scale-1) );

    int kernel_size = (int)ceil(3*(0.25* ( sqrt(scale*scale-1) )));

    if ( kernel_size % 2 == 0 )
    {
        kernel_size = kernel_size+1;
    }

    int kernelhalfwidth = kernel_size/2;

    cout << "kernel_size = " << kernel_size << endl;
    cout << "blurWidth = " << kernelhalfwidth << endl;

    float blur_kernel_h[kernel_size*kernel_size];

    float* blur_kernel_d;

    float sum_kernel_values = 0;

    cout << "sigma_kernel = " << sigma_kernel << endl;

    for(int i = 0 ; i < kernel_size; i++)
    {
        for(int j = 0 ; j < kernel_size; j++)
        {
            float val = (i-kernelhalfwidth)*(i-kernelhalfwidth) + (j-kernelhalfwidth)*(j-kernelhalfwidth);


            val = val / (2*sigma_kernel*sigma_kernel);

            blur_kernel_h[i*kernel_size+j] = exp(-val)/(2*M_PI*sigma_kernel*sigma_kernel);

            sum_kernel_values += blur_kernel_h[i*kernel_size+j];

        }
    }



  //###################### ALL RELATED TO DATAMATRIX ###################################
    std::map<int,float>matindex_matval;
    std::map<int,float>matindex_matvalT;

    buildDMatrixLebesgueMeasure(size_have,size_wanted, N_rows_upimg, N_cols_upimg, scale, /*A,*/ matindex_matval,matindex_matvalT);

    int NnzDMat = (int)matindex_matval.size();
    int NnzDMatT = (int)matindex_matvalT.size();


    float *DMatvalPtr = new float[NnzDMat];
    float *DMatvalPtrT = new float[NnzDMatT];

    int *DMatcolPtr = new int[NnzDMat];
    int *DMatcolPtrT = new int[NnzDMatT];

    int *DMatrowPtr = new int[size_have+1];
    int *DMatrowPtrT = new int[size_wanted+1];


    int index = 0, prev_row = -1;


    cout << "In here" << endl;


    std::map<int,float>::iterator it;
    cout << "Map begins " << endl;
    cout << "NnzDMat   = "<<NnzDMat << endl;
    cout << "NnzDMatT   = "<<NnzDMatT << endl;

    for(int i = 0 ; i < size_have ; i++)
    {
        DMatrowPtr[i] = 0;
    }
    DMatrowPtr[size_have] = NnzDMat;

    for(int i = 0 ; i < size_wanted ; i++)
    {
        DMatrowPtrT[i] = 0;
    }
    DMatrowPtrT[size_wanted] = NnzDMatT;


    cout << "Transpose data begins" << endl;
    index = 0; prev_row = -1;
    for(it = matindex_matvalT.begin(); it != matindex_matvalT.end(); it++ )
    {
        DMatcolPtrT[index] = (it->first)%size_have;
        DMatvalPtrT[index]  = it->second;
        int row = ((it->first) - (it->first)%size_have)/size_have;

        if ( DMatrowPtrT[row] == 0 && prev_row != row)
        {
            DMatrowPtrT[row] = index;
            prev_row = row;
        }

        index++;
    }


    index = 0; prev_row=-1;
    for(it = matindex_matval.begin(); it != matindex_matval.end(); it++ )
    {
//        cout << (it->first)%size_wanted << " " ;//<< it->second << endl;
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

  //######################################################################################


  //############### ALL RELATED TO BLUR MATRIX ############################################
    cout << "Into the Blur function!" << endl;

//    TooN::Matrix<>B(size_wanted,size_wanted);
//    B = TooN::Zeros(size_wanted,size_wanted);

    std::map<int,float>Blurmatindex_matval;
    std::map<int,float>Blurmatindex_matvalT;


    buildBlurMatrixFromKernel(size_wanted, N_rows_upimg, N_cols_upimg, blur_kernel_h, kernel_size, /*B,*/ Blurmatindex_matval,Blurmatindex_matvalT);


    int NnzBlurMat  = (int)Blurmatindex_matval.size();
    int NnzBlurMatT = (int)Blurmatindex_matvalT.size();

    float *BMatvalPtr = new float[NnzBlurMat];
    float *BMatvalPtrT = new float[NnzBlurMatT];

    int *BMatcolPtr = new int[NnzBlurMat];
    int *BMatcolPtrT = new int[NnzBlurMatT];

    int *BMatrowPtr = new int[size_wanted+1];
    int *BMatrowPtrT = new int[size_wanted+1];



    index = 0; prev_row = -1;

//    std::map<int,float>::iterator it;
    cout << "Map begins " << endl;
    cout << "NnzBlurMat   = "<<NnzBlurMat << endl;
    cout << "NnzBlurMatT   = "<<NnzBlurMatT << endl;

    for(int i = 0 ; i < size_wanted ; i++)
    {
        BMatrowPtr[i] = 0;
    }
    BMatrowPtr[size_wanted] = NnzBlurMat;

    for(int i = 0 ; i < size_wanted ; i++)
    {
        BMatrowPtrT[i] = 0;
    }
    BMatrowPtrT[size_wanted] = NnzBlurMatT;


    cout << "Transpose data begins" << endl;
    index = 0; prev_row = -1;

    for(it = Blurmatindex_matvalT.begin(); it != Blurmatindex_matvalT.end(); it++ )
    {
        BMatcolPtrT[index] = (it->first)%size_wanted;
        BMatvalPtrT[index]  = it->second;
        int row = ((it->first) - (it->first)%size_wanted)/size_wanted;

        if ( BMatrowPtrT[row] == 0 && prev_row != row)
        {
            BMatrowPtrT[row] = index;
            prev_row = row;
        }

        index++;
    }

    index = 0; prev_row=-1;
    for(it = Blurmatindex_matval.begin(); it != Blurmatindex_matval.end(); it++ )
    {
        BMatvalPtr[index] = (it->second);
        BMatcolPtr[index] = (it->first)%size_wanted;

        int row = ((it->first) - (it->first)%size_wanted)/size_wanted;

        if ( BMatrowPtr[row] == 0 && prev_row != row)
        {
            BMatrowPtr[row] = index;
            prev_row = row;
        }

        index++;
    }
    cout << endl;


   //##########################################################################################



    cout << "Going to initialise the sparse matrix thing!"<<endl;
    cusparseHandle_t handle = 0;
    cusparseStatus_t status;
    status = cusparseCreate(&handle);

    if ( status == CUSPARSE_STATUS_SUCCESS )
    {
        cout<<"Hooray! Success, Success, Success!" <<endl;
    }
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

    cout<< "cu sparse initialised!"<<endl;


    float* d_cscWMatvalPtr;
    int* d_cscWMatcolPtr;
    int* d_cscWMatrowPtr;

    float* d_cscBMatvalPtr;
    int* d_cscBMatcolPtr;
    int* d_cscBMatrowPtr;



    // Remember this is csc so col and rows are swapped!
    cutilSafeCall(cudaMalloc((void**)&d_cscWMatvalPtr, total_nonzeros*sizeof (float)));
    cutilSafeCall(cudaMalloc((void**)&d_cscWMatrowPtr, (total_nonzeros)*sizeof(int)));
    cutilSafeCall(cudaMalloc((void**)&d_cscWMatcolPtr, (size_wanted+1)*sizeof (int)));




    {
        ScopedCuTimer cuTime("csr2csc conversion time");
        cusparseScsr2csc(handle,size_wanted*N_imgs, size_wanted, d_csrWMatStackedval, d_csrWMatStackedrow, d_csrWMatStackedcol, d_cscWMatvalPtr,
                     d_cscWMatrowPtr, d_cscWMatcolPtr, 1, CUSPARSE_INDEX_BASE_ZERO);
    }





//    {
//        ScopedCuTimer cuTime("csr2csc conversion time");
//        cusparseScsr2csc(handle, size_wanted, size_wanted*N_imgs, d_cscWMatvalPtr, d_cscWMatcolPtr, d_cscWMatrowPtr, d_csrWMatStackedval,
//                     d_csrWMatStackedcol, d_csrWMatStackedrow, 1, CUSPARSE_INDEX_BASE_ZERO);

//        if (status != CUSPARSE_STATUS_SUCCESS) {
//            fprintf( stderr, "!!!! CSC2CSR Conversion error\n" );
//            return EXIT_FAILURE;
//        }
//    }




    float *d_horizontal_velocity_all;
    float *d_vertical_velocity_all;

    float *d_DMatvalPtr;
    int *d_DMatcolPtr;
    int *d_DMatrowPtr;

    float *d_BMatvalPtr;
    int *d_BMatcolPtr;
    int *d_BMatrowPtr;

    float *d_BMatvalPtrT;
    int *d_BMatcolPtrT;
    int *d_BMatrowPtrT;

    float *d_DMatvalPtrT;
    int *d_DMatcolPtrT;
    int *d_DMatrowPtrT;


    float *d_img;
    float *d_imgT;

    float *d_Ax;
    float *d_Bx;

    float *d_AxT;

    float *d_A_copy;

    float *h_Ax;
    float *h_Bx = new float[size_wanted];

    float *h_A;
    float *h_A_copy = new float[size_have*size_wanted];
    float *h_AxT;

    size_t upImageFloatPitch;


    int output_vector_size = size_have;
    size_t velFloatPitch;


    cutilSafeCall(cudaMalloc((void**)&d_DMatvalPtr, NnzDMat*sizeof (float)));
    cutilSafeCall(cudaMalloc((void**)&d_DMatcolPtr, NnzDMat*sizeof (int)));
    cutilSafeCall(cudaMalloc((void**)&d_DMatrowPtr, (size_have+1)*sizeof(int)));

    cutilSafeCall(cudaMalloc((void**)&d_DMatvalPtrT, NnzDMatT*sizeof (float)));
    cutilSafeCall(cudaMalloc((void**)&d_DMatcolPtrT, NnzDMatT*sizeof (int)));
    cutilSafeCall(cudaMalloc((void**)&d_DMatrowPtrT, (size_wanted+1)*sizeof(int)));


    cutilSafeCall(cudaMalloc((void**)&d_BMatvalPtr, NnzBlurMat*sizeof (float)));
    cutilSafeCall(cudaMalloc((void**)&d_BMatcolPtr, NnzBlurMat*sizeof (int)));
    cutilSafeCall(cudaMalloc((void**)&d_BMatrowPtr, (size_wanted+1)*sizeof(int)));


    cutilSafeCall(cudaMalloc((void**)&d_Bx, (size_wanted)*sizeof(float)));
    cutilSafeCall(cudaMalloc((void**)&d_Ax, (output_vector_size)*sizeof(float)));
    cutilSafeCall(cudaMalloc((void**)&d_AxT, (size_wanted)*sizeof(float)));



    cutilSafeCall(cudaMalloc((void**)&d_A_copy, (size_have)*sizeof(float)*size_wanted));
//    cutilSafeCall(cudaMalloc((void**)&d_img, sizeof(float)*size_wanted));
    cutilSafeCall(cudaMallocPitch(&d_img,&upImageFloatPitch,sizeof(float)*N_cols_upimg,N_rows_upimg));




    cutilSafeCall(cudaMallocPitch(&d_horizontal_velocity_all,&velFloatPitch,sizeof(float)*size_wanted,N_imgs));
    cutilSafeCall(cudaMallocPitch(&d_vertical_velocity_all,&velFloatPitch,sizeof(float)*size_wanted,N_imgs));


    cutilSafeCall(cudaMalloc((void**)&d_imgT, sizeof(float)*size_have));




    cudaMemcpy(d_DMatvalPtr, DMatvalPtr, NnzDMat*sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_DMatcolPtr, DMatcolPtr, NnzDMat*sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_DMatrowPtr, DMatrowPtr, (size_have+1)*sizeof(int), cudaMemcpyHostToDevice);

    cudaMemcpy(d_BMatvalPtr, BMatvalPtr, NnzBlurMat*sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_BMatcolPtr, BMatcolPtr, NnzBlurMat*sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_BMatrowPtr, BMatrowPtr, (size_wanted+1)*sizeof(int), cudaMemcpyHostToDevice);

    cudaMemcpy(d_BMatvalPtrT, BMatvalPtrT, NnzBlurMatT*sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_BMatcolPtrT, BMatcolPtrT, NnzBlurMatT*sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_BMatrowPtrT, BMatrowPtrT, (size_wanted+1)*sizeof(int), cudaMemcpyHostToDevice);


    cudaMemcpy(d_DMatvalPtrT, DMatvalPtrT, NnzDMatT*sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_DMatcolPtrT, DMatcolPtrT, NnzDMatT*sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_DMatrowPtrT, DMatrowPtrT, (size_wanted+1)*sizeof(int), cudaMemcpyHostToDevice);


    cudaMemcpy(d_img, input_image_data_up, (size_wanted)*sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_imgT, input_image_data_down, (size_have)*sizeof(float), cudaMemcpyHostToDevice);



    cutilSafeCall(cudaMalloc((void**)&d_cscBMatvalPtr, NnzBlurMat*sizeof (float)));
    cutilSafeCall(cudaMalloc((void**)&d_cscBMatrowPtr, (NnzBlurMat)*sizeof(int)));
    cutilSafeCall(cudaMalloc((void**)&d_cscBMatcolPtr, (size_wanted+1)*sizeof (int)));


    // Check if the Blur is working...

    {
        ScopedCuTimer cuTime("blur multiplication time");
        status = cusparseScsrmv(handle,CUSPARSE_OPERATION_NON_TRANSPOSE, size_wanted, size_wanted, 1.0, descr, d_BMatvalPtr, d_BMatrowPtr, d_BMatcolPtr, d_img, 0.0, d_Bx);

    }
    cudaMemcpy(h_Bx,d_Bx,sizeof(float)*size_wanted,cudaMemcpyDeviceToHost);

    CVD::Image<CVD::byte> blurredImage = CVD::Image<CVD::byte>(ImageRef(N_cols_upimg,N_rows_upimg));

    for(int row = 0 ; row < N_rows_upimg ; row++)
    {
        for(int col = 0 ; col < N_cols_upimg ; col++)
        {
           blurredImage[ImageRef(col,row)] = (unsigned char)(h_Bx[row*N_cols_upimg+col]*255.0f);
        }
    }

    img_save(blurredImage,"blurredImage.png");


    {
        ScopedCuTimer cuTime("csr2csc conversion time for blur");
        cusparseScsr2csc(handle,size_wanted, size_wanted, d_BMatvalPtr, d_BMatrowPtr, d_BMatcolPtr, d_cscBMatvalPtr,
                     d_cscBMatrowPtr, d_cscBMatcolPtr, 1, CUSPARSE_INDEX_BASE_ZERO);
    }




    // Checked!



    // Check for matrix multiplication which is [W1; W2; W3; ... ;Wn]*u

    float* h_Wis_u_ = new float[size_wanted*N_imgs];
    float* d_Wis_u_;
    cutilSafeCall(cudaMalloc((void**)&d_Wis_u_, (size_wanted*N_imgs)*sizeof(float)));


    {

        ScopedCuTimer cuTime("warping multiplication time");
        status = cusparseScsrmv(handle,CUSPARSE_OPERATION_NON_TRANSPOSE, size_wanted*N_imgs, size_wanted, 1.0, descr, d_csrWMatStackedval,
                                                        d_csrWMatStackedrow, d_csrWMatStackedcol, d_img, 0.0, d_Wis_u_);

    }

    {
        ScopedCuTimer cuTime("Memcpy time");
        cudaMemcpy(h_Wis_u_,d_Wis_u_,sizeof(float)*size_wanted*N_imgs,cudaMemcpyDeviceToHost);
    }





    cout << "N_rows_low_img = " << N_rows_low_img << endl;

    CVD::Image<CVD::byte> WarpedImage = CVD::Image<CVD::byte>(ImageRef(N_cols_upimg,N_rows_upimg));

    for(int i = 0 ; i < N_imgs ; i++)
    {

        for(int row = 0 ; row < N_rows_upimg ; row++)
        {
            for(int col = 0 ; col < N_cols_upimg ; col++)
            {
                WarpedImage[ImageRef(col,row)] = (unsigned char)(h_Wis_u_[row*N_cols_upimg+col + i*(size_wanted)]*255.0f);
            }
        }

        char fileName[40];
        sprintf(fileName,"WarpedImage_%02d.png",i);
        img_save(WarpedImage,fileName);
    }


    cout<< "After initialising the image!"<<endl;


    h_Ax          = (float*)malloc(sizeof(float)*size_have);
    h_AxT         = (float*)malloc(sizeof(float)*size_wanted);


    {
        ScopedCuTimer cuTime("multiplication time");
        status = cusparseScsrmv(handle,CUSPARSE_OPERATION_NON_TRANSPOSE, size_have, size_wanted, 1.0, descr, d_DMatvalPtr, d_DMatrowPtr, d_DMatcolPtr, d_Bx, 0.0, d_Ax);
    }

    {
        ScopedCuTimer cuTime("transpose multiplication time");
        status = cusparseScsrmv(handle,CUSPARSE_OPERATION_NON_TRANSPOSE, size_wanted, size_have, 1.0, descr, d_DMatvalPtrT, d_DMatrowPtrT, d_DMatcolPtrT, d_imgT, 0.0, d_AxT);
    }



    cudaMemcpy(h_Ax,d_Ax,sizeof(float)*output_vector_size,cudaMemcpyDeviceToHost);


    cout<< endl<<"cusparse multiplication result!"<<endl;


    cudaMemcpy(h_AxT,d_AxT,sizeof(float)*size_wanted,cudaMemcpyDeviceToHost);

    cout<< endl<<"cusparse multiplication transpose result!"<<endl;



    cout << "N_rows_low_img = " << N_rows_low_img << endl;

    CVD::Image<CVD::byte> dsampledImage = CVD::Image<CVD::byte>(ImageRef(N_cols_low_img,N_rows_low_img));

    for(int row = 0 ; row < N_rows_low_img ; row++)
    {
        for(int col = 0 ; col < N_cols_low_img ; col++)
        {
            dsampledImage[ImageRef(col,row)] = (unsigned char)(h_Ax[row*N_cols_low_img+col]*255.0f);
        }
    }

    img_save(dsampledImage,"dsampledImage.png");


    cout << "Image is downsampled and saved!" << endl;
//    exit(1);
// ######################### Uncomment from here #########################



//    cudaMemset2D(zero, zerop, 0.f, sizeof(float)*(M+2), (N+2));

    //Copy horizontal_velocities and vertical velocities

//    float *d_u_;
//    float *d_u_;
//    float *d_u_;


    size_t downImageFloatPitch;
    size_t imgVectorsFloatPitch;
    size_t WTBTDTqFloatPitch;
    size_t qVectorsFloatPitch;

    float *d_px;
    float *d_py;

    float *d_ux_;
    float *d_uy_;

    float *d_u_;
    float *d_u;

    float *d_ydcopyqi;
    float *d_Wiu_;
    float *d_Wiu_copy;

    float *d_DTqi_copy;
    float *d_BTDTqi;
    float *d_blur_result;
    float *d_res;
    float *d_dual_save_WTBTDTq;
    float *d_dual_save_BTDTq;

    float *d_fi; // All Input Images

    float *d_qi;
    float *d_res_stacked;



    cutilSafeCall(cudaMalloc((void**)&d_px, size_wanted*sizeof (float)));
    cutilSafeCall(cudaMalloc((void**)&d_py, size_wanted*sizeof (float)));




    cutilSafeCall(cudaMalloc((void**)&d_ux_, size_wanted*sizeof (float)));
    cutilSafeCall(cudaMalloc((void**)&d_uy_, size_wanted*sizeof (float)));

    cutilSafeCall(cudaMalloc((void**)&d_u_, size_wanted*sizeof (float)));
    cutilSafeCall(cudaMalloc((void**)&d_u, size_wanted*sizeof (float)));




    int upImageStrideFloat    = upImageFloatPitch/sizeof(float);



    cutilSafeCall(cudaMalloc((void**)&d_ydcopyqi, size_have*sizeof (float)));




    cutilSafeCall(cudaMalloc((void**)&d_DTqi_copy, size_wanted*sizeof (float)));
    cutilSafeCall(cudaMalloc((void**)&d_blur_result, size_wanted*sizeof (float)));
    cutilSafeCall(cudaMalloc((void**)&d_BTDTqi, size_wanted*sizeof (float)));





    cutilSafeCall(cudaMalloc((void**)&d_Wiu_, size_wanted*sizeof (float)));
    cutilSafeCall(cudaMalloc((void**)&d_Wiu_copy, size_wanted*sizeof (float)));



    cutilSafeCall(cudaMalloc((void**)&d_res, size_have*sizeof (float)));


    cutilSafeCall(cudaMalloc((void**)&d_fi, size_have*N_imgs*sizeof (float)));
    cutilSafeCall(cudaMalloc((void**)&d_dual_save_WTBTDTq, size_wanted*sizeof (float)));





    cutilSafeCall(cudaMalloc((void**)&d_dual_save_BTDTq, (size_wanted)*sizeof(float)*N_imgs));



    cutilSafeCall(cudaMalloc((void**)&d_qi, (size_have)*sizeof(float)*N_imgs));
    cutilSafeCall(cudaMemset(d_qi,0,(size_have)*sizeof(float)*N_imgs));
//    cutilSafeCall(cudaMemset(d_qi,1,(size_have)*sizeof(float)*N_imgs));


    cutilSafeCall(cudaMalloc((void**)&d_res_stacked, (size_have)*sizeof(float)*N_imgs));

//    float *h_res_stacked = new float[size_have*N_imgs];
//    for(int i = 0 ; i < size_have*N_imgs ; i++)
//    {
//        h_res_stacked[i]=i;
//    }

//    cudaMemcpy(d_res_stacked,h_res_stacked,sizeof(float)*size_have*N_imgs,cudaMemcpyHostToDevice);
//    cudaMemcpy(d_qi,h_res_stacked,sizeof(float)*size_have*N_imgs,cudaMemcpyHostToDevice);



    cutilSafeCall(cudaMemset(d_res_stacked,0,sizeof(float)*size_have*N_imgs));



    cout << "Memory Initialisation already!" <<endl;




    //Read Input Images

    for(int i = 0 ; i < N_imgs ; i++)
    {
        CVD::Image<float> inputImage;// = CVD::Image<float>(ImageRef(N_cols_low_img,N_rows_low_img));

        char imgName[100];
        sprintf(imgName,"../data/images/car_%03d.pgm",i+1);

        img_load(inputImage,imgName);
        // Image Loaded!

        cudaMemcpy(d_fi+(size_have)*i,inputImage.data(),sizeof(float)*size_have,cudaMemcpyHostToDevice);

    }
    cout << "Images have been loaded!" <<endl;


    ifstream tau_file("tau.txt");
    float* h_tau = new float[size_wanted];
    float* d_tau;

    char readlinedata[300];
    int taupos= 0;


    while ( !tau_file.eof() ) { // keep reading until end-of-file
        float tauval;
        tau_file >> tauval; // sets EOF flag if no value found
        h_tau[taupos++] = tauval;

    }
    tau_file.close();


//    while(1)
//    {
////        tau_file.getline(readlinedata, 300);
//        if ( tau_file.eof())
//            break;
//        tau_file >> val;
//        h_tau[taupos++] = val;
//    }


    ifstream dT_file("btranspose.txt");
    float* h_dT = new float[size_wanted];

//    char readlinedata[300];
//    pos = 0;
    while(1)
    {
        dT_file.getline(readlinedata, 300);
        if ( dT_file.eof())
            break;

        istringstream iss(readlinedata);

        float val;
        iss >> val;

        static int pos = 0;

        h_dT[pos] = val;
//        cout<< "h_dT = "<< h_dT[pos] << endl;
        pos++;
    }

    dT_file.close();


    cutilSafeCall(cudaMallocPitch(&d_tau,&upImageFloatPitch,sizeof(float)*N_cols_upimg,N_rows_upimg));
    cudaMemcpy(d_tau,h_tau,sizeof(float)*size_wanted,cudaMemcpyHostToDevice);

//    cout << "Here after reading the file contents!" << endl;




//    cutilSafeCall(cudaMemset(d_qi,1,(size_have)*sizeof(float)*N_imgs));


//    float* h_Wiu_copy = new float[size_wanted];

//    for(int i = 0 ; i < N_imgs ; i++)
//    {

//        for(int row = 0 ; row < N_rows_upimg ; row++)
//        {
//            for(int col = 0 ; col < N_cols_upimg ; col++)
//            {
//                cudaMemcpy(h_Wiu_copy,d_Wis_u_+(size_wanted)*i,sizeof(float)*size_wanted,cudaMemcpyDeviceToHost);
////                cudaMemcpy(d_Wiu_copy,d_Wis_u_+(size_wanted)*i,sizeof(float)*size_wanted,cudaMemcpyDeviceToDevice);


//                WarpedImage[ImageRef(col,row)] = (unsigned char)(h_Wiu_copy[row*N_cols_upimg+col]*255.0f);
//            }
//        }

//        char fileName[40];
//        sprintf(fileName,"WarpedImageMemcpyone_%02d.png",i);
//        img_save(WarpedImage,fileName);
//    }





    float *d_low_img;
    cutilSafeCall(cudaMallocPitch(&d_low_img,&downImageFloatPitch,sizeof(float)*N_cols_low_img,N_rows_low_img));
    cudaMemcpy(d_low_img,input_image_low.data(),sizeof(float)*size_have,cudaMemcpyHostToDevice);

//    float *h_low_img =;



    // Add images into d_fi;


    int downImageStrideFloat  = downImageFloatPitch/sizeof(float);
    int imgVectorsStrideFloat = imgVectorsFloatPitch/sizeof(float);
    int WTBTDTqStrideFloat    = WTBTDTqFloatPitch/sizeof(float);
    int qVectorsStrideFloat   = qVectorsFloatPitch/sizeof(float);


    cout << "upImageStrideFloat = " << upImageStrideFloat << endl;

    int velStrideFloat   = velFloatPitch/sizeof(float);

    int width_up   = N_cols_upimg;
    int height_up  = N_rows_upimg;

    int width_down   = N_cols_low_img;
    int height_down  = N_rows_low_img;

    double xisqr = scale*scale;




    cutilSafeCall(cudaMalloc((void**)&blur_kernel_d, (kernel_size)*sizeof(float)*kernel_size));
    cudaMemcpy(blur_kernel_d,blur_kernel_h,sizeof(float)*kernel_size*kernel_size,cudaMemcpyHostToDevice);






    cout <<" Blurred the kernel" << endl;



//    int width = width_window;
//    int height = height_window;



    int imgWidth = input_image_up.size().x;
    int imgHeight = input_image_up.size().y;

    int width = imgWidth;
    int height = imgHeight;

    GlTexture greyTexture(width,height,GL_LUMINANCE32F_ARB);
    GlBufferCudaPtr greypbo( GlPixelUnpackBuffer, size_wanted*sizeof(float), cudaGraphicsMapFlagsNone, GL_STREAM_DRAW );

//    int imgWidth = input_image_up.size().x;
//    int imgHeight = input_image_up.size().y;

    float aspect = 72.0f/121.0f;

    View& view_image0 = Display("image0").SetAspect(aspect);
    View& view_image1 = Display("image1").SetAspect(aspect);
    View& view_image2 = Display("image2").SetAspect(aspect);
    View& view_image3 = Display("image3").SetAspect(aspect);


    View& d_panel = pangolin::CreatePanel("ui")
                    .SetBounds(1.0, 0.0, 0, 150);


    
    View& d_imgs = pangolin::Display("images")
                 .SetBounds(1.0, 0.5, 150, 1.0, true)
                   .SetLayout(LayoutEqual)
                   .AddDisplay(view_image0)
                   .AddDisplay(view_image1)
                   .AddDisplay(view_image2)
                   .AddDisplay(view_image3)
                   ;


//    int imageStrideFloat=imagePitchFloat/sizeof(float);

    cout <<" Pangolin initialised!"<<endl;

    float lambda    = 0.1;
    float epsilon_u = 0.0;
    float epsilon_d = 0.0;


//    float L = sqrt(43);
//    float tau = scale/sqrt(L*L*lambda);

//    float sigma_p = 1.0f/sqrt(L*L*tau);
    float sigma_q   = 1.0f;

    float sigma_p   = 1/(2*lambda);

//    float sigma_q = 1.0f/L;




//    cusparseScsrmv(handle,CUSPARSE_OPERATION_NON_TRANSPOSE, size_wanted, size_have, 1.0, descr, d_DMatvalPtrT, d_DMatrowPtrT,
//                                                        d_DMatcolPtrT, d_low_img, 0.0, d_DTqi_copy);

//    cusparseScsrmv(handle,CUSPARSE_OPERATION_NON_TRANSPOSE, size_wanted, size_wanted, 1.0, descr, d_cscBMatvalPtr, d_cscBMatcolPtr,
//                   d_cscBMatrowPtr, d_DTqi_copy, 0.0, d_BTDTqi);


//    cudaMemcpy(h_AxT,d_BTDTqi,sizeof(float)*size_wanted,cudaMemcpyDeviceToHost);


//    for(int row = 0 ; row < N_rows_upimg ; row++)
//    {
//        for(int col = 0 ; col < N_cols_upimg ; col++)
//        {
//            cout<<"("<< h_dT[col*N_rows_upimg+row]<<", "<< h_AxT[row*N_cols_upimg+col]<<") ";
//        }
//        cout<<endl;
//    }


    cutilSafeCall(cudaMemset(d_px,0,sizeof(float)*size_wanted));
    cutilSafeCall(cudaMemset(d_py,0,sizeof(float)*size_wanted));

    cutilSafeCall(cudaMemset(d_ux_,0,sizeof(float)*size_wanted));
    cutilSafeCall(cudaMemset(d_uy_,0,sizeof(float)*size_wanted));



    ifstream indata;
    indata.open("u_stored.txt");

    float val;

//    float array[size_wanted];

    int i = 0;
    while ( !indata.eof() ) { // keep reading until end-of-file
        indata >> val; // sets EOF flag if no value found
        input_image_data_up[i++] = val;

    }
    indata.close();

    for(int i = 0 ; i < 100 ; i++)
        cout<< input_image_data_up[i] << " ";





    cudaMemcpy(d_u_,input_image_data_up,sizeof(float)*size_wanted,cudaMemcpyHostToDevice);
    cudaMemcpy(d_u,input_image_data_up,sizeof(float)*size_wanted,cudaMemcpyHostToDevice);


//    cutilSafeCall(cudaMemcpy2D(d_u, upImageFloatPitch, input_image_up.data(), sizeof(float)*N_cols_upimg, sizeof(float)*N_cols_upimg, N_rows_upimg, cudaMemcpyHostToDevice));
//    cutilSafeCall(cudaMemcpy2D(d_u_, upImageFloatPitch, input_image_up.data(), sizeof(float)*N_cols_upimg, sizeof(float)*N_cols_upimg, N_rows_upimg, cudaMemcpyHostToDevice));


//    cusparseScsr2dense(handle,test_size,test_size)

//    cusparseScsrmv(handle,CUSPARSE_OPERATION_NON_TRANSPOSE, size_wanted, size_wanted, 1.0, descr, d_WMatvalPtr,
//                                                    d_WMatrowPtr, d_WMatcolPtr, d_u_, 0.0, d_Wiu_copy);
//    exit(1);





    CVD::Image<float>bicubicsampledImage;
    img_load(bicubicsampledImage,"car_003_up.pgm");


    float *d_bicubic;
    cutilSafeCall(cudaMalloc((void**)&d_bicubic, (size_wanted)*sizeof(float)));
    cudaMemcpy(d_bicubic,bicubicsampledImage.data(),sizeof(float)*size_wanted,cudaMemcpyHostToDevice);



    float* h_dual_save_WTBTDTq = new float [size_wanted];

    ifstream Atqdata("Atq_it_1.txt");

    int Atqpos = 0;


    while ( !Atqdata.eof() ) {
        Atqdata >> val;
        h_dual_save_WTBTDTq[Atqpos]=val;
        Atqpos++;
    }
    Atqdata.close();

//    for(int row = 0 ; row < N_rows_upimg ; row++)
//    {
//        cout<<"row ="<<row<<endl;
//        for( int col = 0 ; col < N_cols_upimg ; col++)
//        {
////            cout<<h_dual_save_WTBTDTq[row*N_cols_upimg+col]<<" ";
//            cout<<h_tau[row*N_cols_upimg+col]<<" ";
//        }
//        cout<<endl;
//    }

//    cudaMemcpy(d_dual_save_WTBTDTq,h_dual_save_WTBTDTq,sizeof(float)*size_wanted,cudaMemcpyHostToDevice);
    cutilSafeCall(cudaMemset(d_dual_save_WTBTDTq,0,sizeof(float)*size_wanted));







    float* h_res = new float [size_wanted];
    ifstream pxfile("px_it_1.txt");

    int pxpos = 0;
    while ( !pxfile.eof() ) { // keep reading until end-of-file
        pxfile >> val; // sets EOF flag if no value found
        h_res[pxpos++] = val;

    }
    pxfile.close();


    float *h_qi  = new float[size_have];

//    exit(1);
    long doIt =0;

    while(!pangolin::ShouldQuit())
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//        cout << "Iteration = "<< doIt << endl;

        if( doIt%100 == 0)
        {
            ScopedCuTimer cuTime("TOTAL TIME PER ITERATION ");
            cout<<"width up = " << width_up <<endl;
            cout<<"height up = " << height_up <<endl;

            int stride = upImageFloatPitch/sizeof(float);
            cout<<"stride = "<<stride <<endl;
            cout<< "sigma_p = "<<sigma_p <<endl;
            cout<<"lambda = "<<lambda<<endl;

            cout<<"Launching Kernel derivatives!"<<endl;
            launch_kernel_derivative_u(d_ux_,d_uy_,d_u_,stride,width_up, height_up);


            cout<<"Launching Primal variable p"<<endl;
            launch_kernel_dual_variable_p(d_px,d_py,d_ux_,d_uy_,epsilon_u, sigma_p, lambda, upImageStrideFloat,width_up,height_up);

//            // What is that we want to try out in this image?
//            // We want to do the optimisation steps with respect to q
//            // That is:
//            // q^{n+1} = \frac{q^n + \sigma \xi^{2} (DBWu_ - f)}{ 1 + epsilon_d*sigma_q/xisqr}
//            // q^{n+1} =  max(-xisqr, min(xisqr, q^{n+1}))

            cusparseScsrmv(handle,CUSPARSE_OPERATION_NON_TRANSPOSE, size_wanted*N_imgs, size_wanted, 1.0, descr, d_csrWMatStackedval,
                                                            d_csrWMatStackedrow, d_csrWMatStackedcol, d_u_, 0.0, d_Wis_u_);

            cout<<"Going to do DBW thing!"<<endl;
            for (int i = 0 ; i < N_imgs ; i++)
            {
                // copy
                cudaMemcpy(d_Wiu_copy,d_Wis_u_+(size_wanted)*i,sizeof(float)*size_wanted,cudaMemcpyDeviceToDevice);

                // Do B*(d_Wis_u_)
                cusparseScsrmv(handle,CUSPARSE_OPERATION_NON_TRANSPOSE, size_wanted, size_wanted, 1.0, descr, d_BMatvalPtr, d_BMatrowPtr, d_BMatcolPtr, d_Wiu_copy, 0.0, d_Bx);

                // Do D*(B*(d_Wis_u_))
                cusparseScsrmv(handle,CUSPARSE_OPERATION_NON_TRANSPOSE, size_have, size_wanted, 1.0, descr, d_DMatvalPtr, d_DMatrowPtr, d_DMatcolPtr, d_Bx, 0.0, d_res);

                //copy to d_res_stacked_vector
                cudaMemcpy(d_res_stacked +(size_have)*i,d_res,sizeof(float)*size_have,cudaMemcpyDeviceToDevice);
            }



            // d_res_stacked is set to 1...!!!

            cout<<"Going to do subtration!"<<endl;

            launch_kernel_subtract(d_fi, imgVectorsStrideFloat, d_res_stacked, qVectorsStrideFloat, size_have*N_imgs, N_cols_low_img, N_rows_low_img*N_imgs);
            launch_kernel_q_SubtractDBWiu_fAdd_yAndReproject(d_qi, qVectorsStrideFloat,
                                                             d_res_stacked,qVectorsStrideFloat,
                                                             sigma_q,xisqr,epsilon_d,
                                                             N_cols_low_img, N_rows_low_img,N_imgs);


//            CVD::Image<CVD::byte> DBWImage = CVD::Image<CVD::byte>(ImageRef(N_cols_low_img,N_rows_low_img));
//            for(int i = 0 ; i < N_imgs ; i++ )
//            {

//                cudaMemcpy(h_qi,d_res_stacked+(size_have)*i,sizeof(float)*size_have,cudaMemcpyDeviceToHost);

//                for(int row = 0 ; row < N_rows_low_img ; row++)
//                {
//                    cout<<"row = "<<row<<endl;
//                    for(int col = 0 ; col < N_cols_low_img ; col++)
//                    {
////                        cout<< h_qi[row*N_cols_low_img+col]<< " ";
//                        DBWImage[ImageRef(col,row)] = (unsigned char)(h_qi[row*N_cols_low_img+col]*255.0f);
//                    }
//                    cout<<endl;
//                }

//                char filename[40];
//                sprintf(filename,"DBWImage_%03d.png",i+1);
//                img_save(DBWImage,filename);
//            }
//            exit(1);


            for(int i = 0 ; i < N_imgs ; i++)
            {
                //copy_qi_to_yu;
                cudaMemcpy(d_ydcopyqi,d_qi+(size_have)*i,sizeof(float)*size_have,cudaMemcpyDeviceToDevice);

                //do D^{T}*yu;
                cusparseScsrmv(handle,CUSPARSE_OPERATION_NON_TRANSPOSE, size_wanted, size_have, 1.0, descr, d_DMatvalPtrT, d_DMatrowPtrT,
                                                    d_DMatcolPtrT, d_ydcopyqi, 0.0, d_DTqi_copy);

                //do B^{T}*(D^{T}*yu);
                cusparseScsrmv(handle,CUSPARSE_OPERATION_NON_TRANSPOSE, size_wanted, size_wanted, 1.0, descr, d_cscBMatvalPtr, d_cscBMatcolPtr,
                                                    d_cscBMatrowPtr, d_DTqi_copy, 0.0, d_BTDTqi);

                //copy the contents to d_dual_save_BTDT_q
                cudaMemcpy(d_dual_save_BTDTq +(size_wanted)*i,d_BTDTqi,sizeof(float)*size_wanted,cudaMemcpyDeviceToDevice);

            }

//            float *h_BTDTq = new float[size_wanted];

//            for(int i = 0 ; i < N_imgs; i++ )
//            {

//                cout<<"############################################ qi = "<<i<<"############################################"<<endl;


//                cudaMemcpy(h_BTDTq,d_dual_save_BTDTq+(size_wanted)*i,sizeof(float)*size_wanted,cudaMemcpyDeviceToHost);

//                for(int row = 0 ; row < N_rows_upimg; row++)
//                {
//                    cout<<"row = "<<row<<endl;
//                    for(int col = 0 ; col < N_cols_upimg; col++)
//                    {
//                        cout<<h_BTDTq[row*N_cols_upimg+col]<<" ";
////                        imgqi[ImageRef(col,row)] = (unsigned char)(h_qi[row*N_cols_low_img+col]*255.0f);
//                    }
//                    cout<<endl;
//                }


//                 char qifilename[34];
//                 sprintf(qifilename,"qiimg_%03d.png",i);
//                 img_save(imgqi,qifilename);

//            }





            // do batch Wi^{T}yu;

            cusparseScsrmv(handle,CUSPARSE_OPERATION_NON_TRANSPOSE, size_wanted, N_imgs*size_wanted, 1.0, descr, d_cscWMatvalPtr, d_cscWMatcolPtr, d_cscWMatrowPtr,
                           d_dual_save_BTDTq, 0.0, d_dual_save_WTBTDTq);

            //launch kernel u ;
            // Remeber to remove this WTBTDTqStrideFloat thing!



            launch_kernel_primal_u(d_px,d_py,d_u_,d_u, upImageStrideFloat, epsilon_u,d_tau,xisqr, d_dual_save_WTBTDTq, WTBTDTqStrideFloat,width_up,height_up,N_imgs);
            cudaMemcpy(h_AxT,d_u,sizeof(float)*size_wanted,cudaMemcpyDeviceToHost);

            CVD::Image<CVD::byte>img2store = CVD::Image<CVD::byte>(ImageRef(N_cols_upimg,N_rows_upimg));

            float maxval = -99;
            float minval =  99;

            for(int row = 0 ; row < N_rows_upimg; row++)
            {
//                cout<<"row = "<<row<<endl;
                for(int col = 0 ; col < N_cols_upimg; col++)
                {
//                    img2store[ImageRef(col,row)] = (unsigned char)(h_AxT[row*N_cols_upimg+col]*255.0f);

                    if( maxval < h_AxT[row*N_cols_upimg+col])
                    {
                        maxval = h_AxT[row*N_cols_upimg+col];
                    }

                    if( minval > h_AxT[row*N_cols_upimg+col])
                    {
                        minval = h_AxT[row*N_cols_low_img+col];
                    }
//                    cout<<h_AxT[row*N_cols_upimg+col]<<" ";
                }
//                cout<<endl;
            }




            for(int row = 0 ; row < N_rows_upimg; row++)
            {
//                cout<<"row = "<<row<<endl;
                for(int col = 0 ; col < N_cols_upimg; col++)
                {
                    img2store[ImageRef(col,row)] = (unsigned char)((h_AxT[row*N_cols_upimg+col]-minval)*255.0f/(maxval - minval));

//                    cout<<h_AxT[row*N_cols_upimg+col]<<" ";
                }
//                cout<<endl;
            }








            static int imgno=0;
            char superfileName[34];
            sprintf(superfileName,"super_resolution_%03d.png",imgno++);
            img_save(img2store,superfileName);
            cout<<"d_u is printed!"<<endl;
//            exit(1);





////            char iteration_filename[20];
////            sprintf(iteration_filename,"u_it_%ld.txt",doIt+1);
////            ifstream u_it_file(iteration_filename);
////            float* u_it = new float[size_wanted];

////            while(1)
////            {
////                u_it_file.getline(readlinedata, 300);
////                if ( u_it_file.eof())
////                    break;

////                istringstream iss(readlinedata);

////                float val;
////                iss >> val;

////                static int pos = 0;

////                u_it[pos] = val;
////                pos++;
////            }



//            CVD::Image<CVD::byte>DTImage = CVD::Image<CVD::byte>(ImageRef(N_cols_upimg,N_rows_upimg));


//            for(int row = 0 ; row < N_rows_upimg ; row++)
//            {
//                for(int col = 0 ; col < N_cols_upimg ; col++)
//                {
////                    cout<< "(" << u_it[col*N_rows_upimg+row]<< ", "<< h_AxT[row*N_cols_upimg+col]<<")";
//                    DTImage[ImageRef(col,row)] = (unsigned char)(h_AxT[row*N_cols_upimg+col]*255.0f);
//                }
////                cout<<endl;
//            }

//            static long slimage =0;
//            char fileName[30];

//            sprintf(fileName,"SuperResolutionImage_%d.png",slimage++);
//            img_save(DTImage,fileName);


        }
        doIt++;

        {
            //do some display stuff
            {

//                view_image1.ActivateScissorAndClear();
//                view_image1.Activate();
//                DisplayFloatDeviceMem(&view_image1, d_img,upImageFloatPitch, greypbo,greyTexture);

////                view_image2.ActivateScissorAndClear();
//                view_image2.Activate();
//                DisplayFloatDeviceMem(&view_image2, d_img,upImageFloatPitch, greypbo,greyTexture);

            }
        }



        glutSwapBuffers();
        glutMainLoopEvent();
    }


    return 0;
}

