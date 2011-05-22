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




extern "C" void launch_kernel_primal_u(float *px, float *py, float* u_, float *u, float epsilon_u, float tau, float xisqr, float *WiT_BiT_DiT_qi,
                                       unsigned int stride, unsigned int width_up, unsigned int height_up, int N_imgs);

extern "C" void launch_kernel_q_SubtractDBWiu_fAdd_yAndReproject(float *result, int resultStride,
                                                                 float *d_DBWiu,int DBWiuStride,
                                                                 float *d_fi,   int imgStride,
                                                                 float sigma_q,float xisqr,float epsilon_d,
                                                                 int width_down, int height_down);

extern "C" void launch_kernel_dual_variable_p(float *px, float *py, float* ux_, float *uy_, float epsilon_u, float sigma, float lambda,
                                              unsigned int stride, unsigned int mesh_width, unsigned int mesh_height);

extern "C" void launch_kernel_blur(float *out, int outStride, float *in, int inStride, float* blur_kernel, int blurWidth, int width, int height);

extern "C" void launch_kernel_Mult_Wi_u(float *out, int outStride, float *d_u_, int u_Stride, float *horizontal_flow, float* vertical_flow, int velStride,
                                         int imgNo, int width, int height);

extern "C" void launch_kernel_derivative_u(float* ux_, float *uy_, float* u_, unsigned int stride, unsigned int mesh_width, unsigned int mesh_height);



int width_window = 512;
int height_window = 512;


















int main( int argc, char* argv[] )
{

    //buildWMatrixBilinearInterpolation(N_imgs, N_rows_upimg, N_cols_upimg, WMatvalPtr, WMatrowPtr, WMatcolPtr);

    float L = sqrt(8);
    float tau = 1.0f/L;
    float sigma = 1.0f/L;
    float lambda = 10;

    srand ( time(NULL) );


//    thrust::device_vector< thrust::tuple<int, float> > d_vector(2);

//    d_vector[0] = thrust::tuple<int,float>(10,0.0);
//    d_vector[1] = thrust::tuple<int,float>(20,1.0);

//    for(int i = 0 ; i < d_vector.size(); i++)
//    {
//       thrust::tuple<int,float>t = d_vector[i];
//        std::cout<< thrust::get<0>(t)<<endl;
//    }

//    cudaGLSetGLDevice(cutGetMaxGflopsDeviceId());
//    CreateGlutWindowAndBind("Main",width_window*2,height_window*2);
//    glewInit();


//    int N_cols_upimgT = 7;
//    int N_rows_upimgT = 7;
//    int size_wantedW = N_cols_upimgT*N_rows_upimgT;





//    TooN::Matrix<> WMat(size_wantedW,size_wantedW);
//    WMat = TooN::Zeros(size_wantedW,size_wantedW);

//    buildWMatrixBilinearInterpolation(N_imgs, size_wantedW, N_rows_upimgT, N_cols_upimgT, h_vectorofMaps,WMat );

//    std::map<int, float>::iterator it;

//    std::map<int, float> mapW = h_vectorofMaps[0];

//    int index = 0, prev_row=-1;

//    int NnzWMatT = (int)mapW.size();
//    float *WMatvalPtrT = new float[NnzWMatT];
//    int *WMatcolPtrT = new   int[NnzWMatT];
//    int *WMatrowPtrT = new   int[size_wantedW+1];
////    int *WMatrowPtrT_copy = new   int[size_wantedW+1];
//    int *h_nnzPerRow    = new   int[size_wantedW];


//    cout<< "NnzWMatT = "<<NnzWMatT <<endl;
//    WMatrowPtrT[0] = 0;
//    h_nnzPerRow[0] = 0;
//    for(int i = 1 ; i < size_wantedW; i++)
//    {
//        WMatrowPtrT[i] =-1;
//        h_nnzPerRow[i] = 0;
//    }
//    WMatrowPtrT[size_wantedW] = NnzWMatT;

//    index = 0;
//    for(it = mapW.begin(); it != mapW.end() ; it++)
//    {

//        WMatcolPtrT[index] = (it->first)%size_wantedW;
//        WMatvalPtrT[index] = (it->second);

//        int row = ((it->first) - (it->first)%size_wantedW)/size_wantedW;


//        h_nnzPerRow[row]++;

////        cout<< "row = "<<row<<endl;

//        if ( WMatrowPtrT[row] == -1 && prev_row != row)
//        {
//            WMatrowPtrT[row] = index;
//            prev_row = row;
//        }
//        index++;

//    }

//    cout<< "WMat Row Ptr before" <<endl;
//    for(int i = 0 ; i < size_wantedW+1; i++)
//    {
//        cout << WMatrowPtrT[i] << " ";
//    }
//    cout << endl;

//    index = 1;
//    while(1)
//    {
//        if( index > size_wantedW)
//            break;

//        int startindex = index;
//        while( WMatrowPtrT[index] == -1)
//        {
//            index++;
//        }
//        for(int i = startindex; i <= index-1 ; i++)
//        {
//            WMatrowPtrT[i] = WMatrowPtrT[index];
//        }
//        index++;
//    }

//    cout<<endl;
//    cout<< "WMat Col Ptr before" <<endl;
//    for(int i = 0 ; i < NnzWMatT; i++)
//    {
//        cout << WMatcolPtrT[i] << " ";
//    }
//    cout << endl;

//    cout<< "WMat Val Ptr before" <<endl;
//    for(int i = 0 ; i < NnzWMatT; i++)
//    {
//        cout << WMatvalPtrT[i] << " ";
//    }
//    cout << endl;

//    cout<< "WMat Row Ptr after" <<endl;
//    for(int i = 0 ; i < size_wantedW+1; i++)
//    {
//        cout << WMatrowPtrT[i] << " ";
//    }
//    cout << endl;


//    float *d_WMatvalPtrT;
//    int *d_WMatcolPtrT;
//    int *d_WMatrowPtrT;
//    float *d_W;
//    int *d_nnzPerRow;

//    float *d_WMatvalPtrT_copy;
//    int *d_WMatcolPtrT_copy;
//    int *d_WMatrowPtrT_copy;
//    int *d_nnzPerRow_copy;



//    cutilSafeCall(cudaMalloc((void**)&d_WMatvalPtrT, NnzWMatT*sizeof (float)));
//    cutilSafeCall(cudaMalloc((void**)&d_WMatcolPtrT, NnzWMatT*sizeof (int)));
//    cutilSafeCall(cudaMalloc((void**)&d_WMatrowPtrT, (size_wantedW+1)*sizeof(int)));
//    cutilSafeCall(cudaMalloc((void**)&d_nnzPerRow, (size_wantedW)*sizeof(int)));
//    cutilSafeCall(cudaMalloc((void**)&d_W, size_wantedW*sizeof (float)*size_wantedW));

//    cutilSafeCall(cudaMalloc((void**)&d_WMatvalPtrT_copy, NnzWMatT*sizeof (float)));
//    cutilSafeCall(cudaMalloc((void**)&d_WMatcolPtrT_copy, NnzWMatT*sizeof (int)));
//    cutilSafeCall(cudaMalloc((void**)&d_WMatrowPtrT_copy, (size_wantedW+1)*sizeof(int)));
//    cutilSafeCall(cudaMalloc((void**)&d_nnzPerRow_copy, (size_wantedW)*sizeof(int)));


//    cusparseHandle_t handle = 0;
//    cusparseStatus_t status;
//    status = cusparseCreate(&handle);
//    if (status != CUSPARSE_STATUS_SUCCESS) {
//        fprintf( stderr, "!!!! CUSPARSE initialization error\n" );
//        return EXIT_FAILURE;
//    }


//    cusparseMatDescr_t descr = 0;
//    status = cusparseCreateMatDescr(&descr);
//    if (status != CUSPARSE_STATUS_SUCCESS) {
//        fprintf( stderr, "!!!! CUSPARSE cusparseCreateMatDescr error\n" );
//        return EXIT_FAILURE;
//    }
//    cusparseSetMatType(descr,CUSPARSE_MATRIX_TYPE_GENERAL);
//    cusparseSetMatIndexBase(descr,CUSPARSE_INDEX_BASE_ZERO);



//    cudaMemcpy(d_WMatvalPtrT, WMatvalPtrT, NnzWMatT*sizeof(float), cudaMemcpyHostToDevice);
//    cudaMemcpy(d_WMatcolPtrT, WMatcolPtrT, NnzWMatT*sizeof(int), cudaMemcpyHostToDevice);
//    cudaMemcpy(d_WMatrowPtrT, WMatrowPtrT, (size_wantedW+1)*sizeof(int), cudaMemcpyHostToDevice);
//    cudaMemcpy(d_nnzPerRow, h_nnzPerRow, size_wantedW*sizeof(int), cudaMemcpyHostToDevice);



//    cusparseStatus_t status_t;
//    status_t = cusparseScsr2dense(handle,size_wantedW,size_wantedW,descr,d_WMatvalPtrT,d_WMatrowPtrT,d_WMatcolPtrT,d_W,size_wantedW);

//    float *h_W = new float[size_wantedW*size_wantedW];
////    cudaMemcpy(h_W,d_W,sizeof(float)*size_wantedW*size_wantedW,cudaMemcpyDeviceToHost);



//    cout<< "WMat is "<<endl;
//    for(int i = 0; i < size_wantedW; i++)
//    {
//        for(int j = 0 ; j < size_wantedW; j++)
//        {
//            int index = i*size_wantedW + j;
//            h_W[index] = WMat(i,j);
//            cout<< h_W[index]<< " ";
//        }
//    }



//    cudaMemcpy(d_W,h_W,sizeof(float)*size_wantedW*size_wantedW,cudaMemcpyHostToDevice);

//    cusparseSdense2csr(handle,size_wantedW,size_wantedW,descr,d_W,size_wantedW,d_nnzPerRow,d_WMatvalPtrT_copy, d_WMatrowPtrT_copy,d_WMatcolPtrT_copy);


//    cudaMemcpy(WMatrowPtrT,d_WMatrowPtrT_copy,sizeof(int)*(size_wantedW+1),cudaMemcpyDeviceToHost);
////    cudaMemcpy(WMatrowPtrT_copy,d_WMatrowPtrT_copy,sizeof(int)*(size_wantedW+1),cudaMemcpyDeviceToHost);
//    cudaMemcpy(WMatcolPtrT,d_WMatcolPtrT_copy,sizeof(int)*NnzWMatT,cudaMemcpyDeviceToHost);
//    cudaMemcpy(WMatvalPtrT,d_WMatvalPtrT_copy,sizeof(float)*NnzWMatT,cudaMemcpyDeviceToHost);

////    cudaMemcpy(WMatrowPtrT_copy,d_WMatrowPtrT,sizeof(int)*(size_wantedW+1),cudaMemcpyDeviceToHost);
////    cudaMemcpy(WMatrowPtrT,d_WMatrowPtrT,sizeof(int)*(size_wantedW+1),cudaMemcpyDeviceToHost);
////    cudaMemcpy(WMatcolPtrT,d_WMatcolPtrT,sizeof(int)*NnzWMatT,cudaMemcpyDeviceToHost);
////    cudaMemcpy(WMatvalPtrT,d_WMatvalPtrT,sizeof(float)*NnzWMatT,cudaMemcpyDeviceToHost);

//    cout<<endl;
//    cout<<"WMatcolPtr = "<<endl;
//    for(int i = 0 ; i < NnzWMatT;i++)
//    {
//        cout<< WMatcolPtrT[i]<< " ";
//    }
//    cout<<endl;


//    cout<<"WMatvalPtr = "<<endl;
//    for(int i = 0 ; i < NnzWMatT;i++)
//    {
//        cout<< WMatvalPtrT[i]<< " ";
//    }
//    cout<<endl;
//    cout<<"WMatrowPtr = "<<endl;
//    for(int i = 0 ; i < size_wantedW+1;i++)
//    {
//        cout<< WMatrowPtrT[i]<< " ";
//    }
//    cout<<endl;

//    cout<<"WMatrowPtr_copy = "<<endl;
//    for(int i = 0 ; i < size_wantedW+1;i++)
//    {
//        cout<< WMatrowPtrT_copy[i]<< " ";
//    }
//    cout<<endl;








    CVD::Image<float> input_image_low;
    img_load(input_image_low,"../data/images/car_001.pgm");

    CVD::Image<float> input_image_up;
    img_load(input_image_up,"../data/images/car_001_up.pgm");

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

    buildWMatrixBilinearInterpolation(N_imgs, size_wanted, N_rows_upimg, N_cols_upimg, h_vectorofMaps);//,WMatT );



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

    for(int i = 0 ; i < kernel_size ; i++)
    {
        for(int j = 0 ; j < kernel_size ; j++)
        {
            blur_kernel_h[i*kernel_size+j] = blur_kernel_h[i*kernel_size+j]/sum_kernel_values;
            cout<< blur_kernel_h[i*kernel_size+j]<< " ";
        }
        cout<< endl;
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
    float* d_cscWMatcolPtr;
    float* d_cscWMatrowPtr;



    // Remember this is csc so col and rows are swapped!
    cutilSafeCall(cudaMalloc((void**)&d_cscWMatvalPtr, total_nonzeros*sizeof (float)));
    cutilSafeCall(cudaMalloc((void**)&d_cscWMatrowPtr, (total_nonzeros)*sizeof(int)));
    cutilSafeCall(cudaMalloc((void**)&d_cscWMatcolPtr, (size_wanted+1)*sizeof (int)));



//    cusparseScsr2csc(handle,size_wanted*N_img, size_wanted, d_WMatvalPtr, d_WMatrowPtr, d_WMatcolPtr, d_cscWMatValPtr,
//		     d_cscWMatRowPtr, d_cscWMatColPtr, 1, CUSPARSE_INDEX_BASE_ZERO);






    float *d_horizontal_velocity_all;
    float *d_vertical_velocity_all;

    float *d_DMatvalPtr;
    int *d_DMatcolPtr;
    int *d_DMatrowPtr;

    float *d_BMatvalPtr;
    int *d_BMatcolPtr;
    int *d_BMatrowPtr;

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
    cutilSafeCall(cudaMalloc((void**)&d_img, sizeof(float)*size_wanted));



    cutilSafeCall(cudaMallocPitch(&d_horizontal_velocity_all,&velFloatPitch,sizeof(float)*size_wanted,N_imgs));
    cutilSafeCall(cudaMallocPitch(&d_vertical_velocity_all,&velFloatPitch,sizeof(float)*size_wanted,N_imgs));


    cutilSafeCall(cudaMalloc((void**)&d_imgT, sizeof(float)*size_have));




    cudaMemcpy(d_DMatvalPtr, DMatvalPtr, NnzDMat*sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_DMatcolPtr, DMatcolPtr, NnzDMat*sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_DMatrowPtr, DMatrowPtr, (size_have+1)*sizeof(int), cudaMemcpyHostToDevice);

    cudaMemcpy(d_BMatvalPtr, BMatvalPtr, NnzBlurMat*sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_BMatcolPtr, BMatcolPtr, NnzBlurMat*sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_BMatrowPtr, BMatrowPtr, (size_wanted+1)*sizeof(int), cudaMemcpyHostToDevice);

    cudaMemcpy(d_DMatvalPtrT, DMatvalPtrT, NnzDMatT*sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_DMatcolPtrT, DMatcolPtrT, NnzDMatT*sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_DMatrowPtrT, DMatrowPtrT, (size_wanted+1)*sizeof(int), cudaMemcpyHostToDevice);


    cudaMemcpy(d_img, input_image_data_up, (size_wanted)*sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_imgT, input_image_data_down, (size_have)*sizeof(float), cudaMemcpyHostToDevice);





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

//            cout << h_Bx[row*N_cols_upimg+col] << " ";

            blurredImage[ImageRef(col,row)] = (unsigned char)(h_Bx[row*N_cols_upimg+col]*255.0f);
        }
    }

    img_save(blurredImage,"blurredImage.png");

    // Checked!



    // Check for matrix multiplication which is [W1; W2; W3; ... Wn]*u

    float* h_Wis_u_ = new float[size_wanted*N_imgs];
    float* d_Wis_u_;
    cutilSafeCall(cudaMalloc((void**)&d_Wis_u_, (size_wanted*N_imgs)*sizeof(float)));


    {

        ScopedCuTimer cuTime("warping multiplication time");
        status = cusparseScsrmv(handle,CUSPARSE_OPERATION_NON_TRANSPOSE, size_wanted*N_imgs, size_wanted, 1.0, descr, d_csrWMatStackedval,
                                                        d_csrWMatStackedrow, d_csrWMatStackedcol, d_img, 0.0, d_Wis_u_);

    }
    cudaMemcpy(h_Wis_u_,d_Wis_u_,sizeof(float)*size_wanted*N_imgs,cudaMemcpyDeviceToHost);



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


//// ######################### Uncomment from here #########################



////    cudaMemset2D(zero, zerop, 0.f, sizeof(float)*(M+2), (N+2));

//    //Copy horizontal_velocities and vertical velocities

////    float *d_u_;
////    float *d_u_;
////    float *d_u_;


//    size_t upImageFloatPitch;
//    size_t downImageFloatPitch;
//    size_t imgVectorsFloatPitch;
//    size_t WTBTDTqFloatPitch;

//    float *d_px;
//    float *d_py;

//    float *d_ux_;
//    float *d_uy_;

//    float *d_u_;
//    float *d_u;

//    float *d_ydcopyqi;
//    float *d_Wiu_;
//    float *d_DTqi_copy;
//    float *d_BTDTqi;
//    float *d_blur_result;
//    float *d_res;
//    float *d_dual_save_WTBTDTq;
//    float *d_dual_save_BTDTq;
//    float *d_fi;
//    float *d_qi;

//    cutilSafeCall(cudaMallocPitch(&d_px,&upImageFloatPitch,sizeof(float)*N_cols_upimg,N_rows_upimg));
//    cutilSafeCall(cudaMallocPitch(&d_py,&upImageFloatPitch,sizeof(float)*N_cols_upimg,N_rows_upimg));

//    cutilSafeCall(cudaMallocPitch(&d_ux_,&upImageFloatPitch,sizeof(float)*N_cols_upimg,N_rows_upimg));
//    cutilSafeCall(cudaMallocPitch(&d_uy_,&upImageFloatPitch,sizeof(float)*N_cols_upimg,N_rows_upimg));

//    cutilSafeCall(cudaMallocPitch(&d_u_,&upImageFloatPitch,sizeof(float)*N_cols_upimg,N_rows_upimg));
//    cutilSafeCall(cudaMallocPitch(&d_u,&upImageFloatPitch,sizeof(float)*N_cols_upimg,N_rows_upimg));


//    cutilSafeCall(cudaMallocPitch(&d_ydcopyqi,&downImageFloatPitch,sizeof(float)*N_cols_low_img,N_rows_low_img));


//    cutilSafeCall(cudaMallocPitch(&d_DTqi_copy,&upImageFloatPitch,sizeof(float)*N_cols_upimg,N_rows_upimg));
//    cutilSafeCall(cudaMallocPitch(&d_blur_result,&upImageFloatPitch,sizeof(float)*N_cols_upimg,N_rows_upimg));
//    cutilSafeCall(cudaMallocPitch(&d_BTDTqi,&upImageFloatPitch,sizeof(float)*N_cols_upimg,N_rows_upimg));

//    // Wi*u - should be the same size as the original size of the vector u
//    cutilSafeCall(cudaMallocPitch(&d_Wiu_,&upImageFloatPitch,sizeof(float)*N_cols_upimg,N_rows_upimg));

//    cutilSafeCall(cudaMallocPitch(&d_res,&downImageFloatPitch,sizeof(float)*N_cols_low_img,N_rows_low_img));

//    // All images stacked up in this vector in lexicographical order.
//    cutilSafeCall(cudaMallocPitch(&d_fi,&imgVectorsFloatPitch,sizeof(float)*size_have,N_imgs));

//    // cutilSafeCall(cudaMalloc((void**)&d_dual_save_WTBTDTq, (size_wanted)*sizeof(float)*N_imgs));
//    cutilSafeCall(cudaMallocPitch(&d_dual_save_WTBTDTq,&WTBTDTqFloatPitch,sizeof(float)*size_wanted,N_imgs));



//    cutilSafeCall(cudaMalloc((void**)&d_dual_save_BTDTq, (size_wanted)*sizeof(float)*N_imgs));
//    cutilSafeCall(cudaMalloc((void**)&d_qi, (size_have)*sizeof(float)*N_imgs));

//    // Add images into d_fi;


//    int upImageStrideFloat    = upImageFloatPitch/sizeof(float);
//    int downImageStrideFloat  = downImageFloatPitch/sizeof(float);
//    int imgVectorsStrideFloat = imgVectorsFloatPitch/sizeof(float);
//    int WTBTDTqStrideFloat    = WTBTDTqFloatPitch/sizeof(float);


//    int velStrideFloat   = velFloatPitch/sizeof(float);

//    int width_up   = N_cols_upimg;
//    int height_up  = N_rows_upimg;

//    int width_down   = N_cols_low_img;
//    int height_down  = N_rows_low_img;

//    double xisqr = scale*scale;

//    float epsilon_u=0.01;
//    float epsilon_d=0.01;
//    float sigma_q=0;
//    float sigma_p=0;



//    cutilSafeCall(cudaMalloc((void**)&blur_kernel_d, (kernel_size)*sizeof(float)*kernel_size));
//    cudaMemcpy(blur_kernel_d,blur_kernel_h,sizeof(float)*kernel_size*kernel_size,cudaMemcpyHostToDevice);




//    {
//        launch_kernel_derivative_u(d_ux_,d_uy_,d_u_,upImageStrideFloat,width_up, height_up);

//        launch_kernel_dual_variable_p(d_px,d_py,d_ux_,d_uy_,epsilon_u, sigma_p, lambda, upImageStrideFloat,width_up,height_up);

//        // What is that we want to try out in this image?
//        // We want to do the optimisation steps with respect to q
//        // That is:
//        // q^{n+1} = \frac{q^n + \sigma \xi^{2} (DBWu_ - f)}{ 1 + epsilon_d*sigma_q/xisqr}
//        // q^{n+1} =  max(-xisqr, min(xisqr, q^{n+1}))

//        for(int i = 0 ; i < N_imgs; i++)
//        {
//            //do Wiu_
//            launch_kernel_Mult_Wi_u(d_Wiu_, upImageStrideFloat, d_u_, upImageStrideFloat, d_horizontal_velocity_all+size_wanted*i, d_vertical_velocity_all+size_wanted*i,
//                                    velStrideFloat, i, width_up, height_up);

//            //do B*(W_iu)
//            launch_kernel_blur(d_blur_result,upImageStrideFloat, d_Wiu_, upImageStrideFloat, blur_kernel_d, kernel_size, width_up, height_up);

//            //do D*(B*(W_iu))
//            cusparseScsrmv(handle,CUSPARSE_OPERATION_NON_TRANSPOSE, size_have, size_wanted, 1.0, descr, d_DMatvalPtr, d_DMatrowPtr, d_DMatcolPtr, d_blur_result, 0.0, d_res);

//            //Subtract f_i and Add to y;
//            launch_kernel_q_SubtractDBWiu_fAdd_yAndReproject(d_res, downImageStrideFloat,
//                                                             d_qi+(size_have)*i,downImageStrideFloat,
//                                                             d_fi, imgVectorsStrideFloat,
//                                                             sigma_q, xisqr, epsilon_d,
//                                                             width_down, height_down);

//        }

//        for(int i = 0 ; i < N_imgs ; i++)
//        {
//            //copy_qi_to_yu;
//            cudaMemcpy(d_qi+(size_have)*i,d_ydcopyqi,sizeof(float)*size_have,cudaMemcpyDeviceToDevice);

//            //do D^{T}*yu;
//            cusparseScsrmv(handle,CUSPARSE_OPERATION_NON_TRANSPOSE, size_have, size_wanted, 1.0, descr, d_DMatvalPtrT, d_DMatrowPtrT, d_DMatcolPtrT, d_ydcopyqi, 0.0, d_DTqi_copy);

//            //do B^{T}*(D^{T}*yu);
////            cusparseScsrmv(handle,CUSPARSE_OPERATION_NON_TRANSPOSE, size_wanted, size_wanted, 1.0, descr, d_BMatvalPtrT, d_BMatrowPtrT, d_BMatcolPtrT, d_DTqi_copy, 0.0, d_BTDTqi);

//            //copy the contents to d_dual_save_BTDT_q
//            cudaMemcpy(d_dual_save_BTDTq +(size_wanted)*i,d_BTDTqi,sizeof(float)*size_wanted,cudaMemcpyDeviceToDevice);

//        }

//        // do batch Wi^{T}yu;
//        cusparseScsrmv(handle,CUSPARSE_OPERATION_NON_TRANSPOSE, size_have, size_wanted, 1.0, descr, d_WMatvalPtrT, d_WMatrowPtrT, d_WMatcolPtrT,
//                       d_dual_save_BTDTq, 0.0, d_dual_save_WTBTDTq);

//        //launch kernel u ;
//        launch_kernel_primal_u(d_px,d_py,d_u,d_u_,epsilon_u,tau,xisqr, d_dual_save_WTBTDTq,WTBTDTqStrideFloat,width_up,height_up,N_imgs);
//    }



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

