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
    float *input_image_data_up = new float[input_vector_size];

//    for(int i = 0 ; i < input_vector_size ; i++)
//    {
//        input_image_data_up[i] = i;
//    }

    float *input_image_data_down = new float[size_have];

//    for(int i = 0 ; i < size_have ; i++)
//    {
//        input_image_data_down[i] = i;
//    }

    //input_image_data_up = input_image_up.data();




    //############################### Computing the W^{T}'s for all the flow vectors ###########################

    int N_imgs = 9;
    std::vector< std::map <int, float> > h_vectorofMaps(N_imgs);

    buildWMatrixBilinearInterpolation(N_imgs, size_wanted, N_rows_upimg, N_cols_upimg, h_vectorofMaps);//,WMatT );



    float **WMatvalPtrT;
    WMatvalPtrT = (float**)malloc(sizeof(float*)*N_imgs);

    int **WMatcolPtrT;
    WMatcolPtrT = (int**)malloc(sizeof(int*)*N_imgs);

    int **WMatrowPtrT;
    WMatrowPtrT = (int**)malloc(sizeof(int*)*N_imgs);

    int **h_nnzPerRow;
    h_nnzPerRow = (int**)malloc(sizeof(int*)*N_imgs);


    float *d_WMatvalPtrT;
    int *d_WMatcolPtrT;
    int *d_WMatrowPtrT;


//    int *d_nnzPerRowT;

//    cutilSafeCall(cudaMalloc((void**)d_WMatvalPtrT, N_imgs*sizeof(float*)));
//    cutilSafeCall(cudaMalloc((void**)d_WMatcolPtrT, N_imgs*sizeof(int*)));
//    cutilSafeCall(cudaMalloc((void**)d_WMatrowPtrT, N_imgs*sizeof(int*)));
//    cutilSafeCall(cudaMalloc((void**)d_nnzPerRowT,  N_imgs*sizeof(int*)));


    int total_nonzeros=0;

    for(int i = 0 ; i < N_imgs ; i++)
    {
        std::map<int, float>::iterator it;
        std::map<int, float> mapW = h_vectorofMaps[i];

        int NnzWMatT = (int)mapW.size();

        WMatvalPtrT[i] = new float[NnzWMatT];
        WMatcolPtrT[i] = new int[NnzWMatT];
        WMatrowPtrT[i] = new int[size_wanted+1];
        h_nnzPerRow[i] = new int[size_wanted];

        total_nonzeros += NnzWMatT;


        int index = 0, prev_row=-1;

        cout<< "NnzWMatT = "<<NnzWMatT <<endl;

        WMatrowPtrT[i][0] = 0;
        h_nnzPerRow[i][0] = 0;

        for(int j = 1 ; j < size_wanted; j++)
        {
            WMatrowPtrT[i][j] =-1;
            h_nnzPerRow[i][j] = 0;
        }
        WMatrowPtrT[i][size_wanted] = NnzWMatT;

        cout<<"have initialised the matrices"<<endl;

        index = 0;
        for(it = mapW.begin(); it != mapW.end() ; it++)
        {

            WMatcolPtrT[i][index] = (it->first)%size_wanted;
            WMatvalPtrT[i][index] = (it->second);

            int row = ((it->first) - (it->first)%size_wanted)/size_wanted;
            h_nnzPerRow[i][row]++;

            if ( WMatrowPtrT[i][row] == -1 && prev_row != row)
            {
                WMatrowPtrT[i][row] = index;
                prev_row = row;
            }
            index++;

        }

//        cout<<"i ="<<i<<" WMat Row Ptr before" <<endl;
//        for(int j = 0 ; j < size_wanted+1; j++)
//        {
//            cout << WMatrowPtrT[i][j] << " ";
//        }
//        cout << endl;

        index = 1;
        while(1)
        {
            if( index > size_wanted)
                break;

            int startindex = index;
            while( WMatrowPtrT[i][index] == -1)
            {
                index++;
            }
            for(int j = startindex; j <= index-1 ; j++)
            {
                WMatrowPtrT[i][j] = WMatrowPtrT[i][index];
            }
            index++;
        }


        WMatrowPtrT[i][0] = 0;
//        cout<<endl;
//        cout<<"i ="<<i<<" WMat Col Ptr before" <<endl;
//        for(int j = 0 ; j < NnzWMatT; j++)
//        {
//            cout << WMatcolPtrT[i][j] << " ";
//        }
//        cout << endl;

//        cout<< "i ="<<i<<" WMat Val Ptr before" <<endl;
//        for(int j = 0 ; j < NnzWMatT; j++)
//        {
//            cout << WMatvalPtrT[i][j] << " ";
//        }
//        cout << endl;

//        cout<<"i ="<<i<<" WMat Row Ptr after" <<endl;
//        for(int j = 0 ; j < size_wanted+1; j++)
//        {
//            cout << WMatrowPtrT[i][j] << " ";
//        }
//        cout << endl;
    }


//    cudaExtent extentNnz = make_cudaExtent(total_nonzeros*sizeof(float),1);

    size_t WMatcol_pitchT;
    cutilSafeCall(cudaMallocPitch(&d_WMatcolPtrT,&WMatcol_pitchT,total_nonzeros*sizeof(int),1));

    size_t WMatval_pitchT;
    cutilSafeCall(cudaMallocPitch(&d_WMatvalPtrT,&WMatval_pitchT,total_nonzeros*sizeof(float),1));

    size_t WMatrow_pitchT;
    cutilSafeCall(cudaMallocPitch(&d_WMatrowPtrT,&WMatrow_pitchT,(size_wanted+1)*sizeof(int),N_imgs));


    //can avoid this by using 2D malloc I think!
//    N_imgs = 700;

    float *d_dual_q;
    size_t d_dual_q_pitch;
    cutilSafeCall(cudaMallocPitch(&d_dual_q,&d_dual_q_pitch,(size_have)*sizeof(float),N_imgs));
    cutilSafeCall(cudaMemset2D(d_dual_q,d_dual_q_pitch,0,(size_have)*sizeof(float),N_imgs));

    float *d_dual_save_qT;
    size_t d_dual_save_qT_pitch;
    cutilSafeCall(cudaMallocPitch(&d_dual_save_qT,&d_dual_save_qT_pitch,(size_wanted)*sizeof(float),N_imgs));
    cutilSafeCall(cudaMemset2D(d_dual_save_qT,d_dual_save_qT_pitch,0,(size_wanted)*sizeof(float),N_imgs));


    cout<<"everything looks okay!"<<endl;

//   {





//   for(int i = 0 ; i < N_imgs ; i++)
//   {

//   }


//   cutilSafeCall(cudaMalloc((void**)&d_W, size_wantedW*sizeof (float)*size_wantedW));



//   }



//   exit(1);


   //###########################################################################################################








//    float *input_image_data_low = new float[size_have];
//    input_image_data_low = input_image_low.data();




    TooN::Matrix<>A(size_have,size_wanted);
    A = TooN::Zeros(size_have,size_wanted);

    std::map<int,float>matindex_matval;
    std::map<int,float>matindex_matvalT;


//    //DMatvalPtr, DMatrowPtr, DMatcolPtr,
    buildDMatrixLebesgueMeasure(size_have,size_wanted, N_rows_upimg, N_cols_upimg, scale, A, matindex_matval,matindex_matvalT);

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

    cout <<"DMatrowptrT"<<endl;
    for(int i = 0; i < size_wanted+1 ; i++)
    {
        cout << DMatrowPtrT[i] << " ";
    }
    cout << endl;

    cout <<"DMatcolptrT"<<endl;
    for(int i = 0; i < NnzDMatT ; i++)
    {
        cout << DMatcolPtrT[i] << " ";
    }
    cout << endl;


////    cout << "Transpose Data ends " << endl;



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

    cout << "DMatcolPtr" << endl;
//    cout << "index = " << index << endl;
//    cout << "NnzDMat = " << NnzDMat << endl;
    for(int i = 0 ; i < NnzDMat ; i++ )
    {
        cout << DMatcolPtr[i] << " ";
    }
    cout << endl;


////    cout <<"A Matrix" << endl;
////    cout << A << endl;


    cout << "DMatrowPtr = " << endl;
    for(int i = 0; i < size_have+1 ; i++)
    {
        cout << DMatrowPtr[i] << " ";
    }
    cout << endl;


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


////    size_t imagePitchFloat;

    float *d_horizontal_velocity_all;
    float *d_vertical_velocity_all;

    float *d_DMatvalPtr;
    int *d_DMatcolPtr;
    int *d_DMatrowPtr;

    float *d_DMatvalPtrT;
    int *d_DMatcolPtrT;
    int *d_DMatrowPtrT;


    float *d_img;
    float *d_imgT;

    float *d_Ax;
    float *d_AxT;

    float *d_A_copy;

    float *h_Ax;
    float *h_A;
    float *h_A_copy = new float[size_have*size_wanted];
    float *h_AxT;



    float *d_ydcopyqi;
    float *d_DTqi_copy;
    float *d_BTDTqi;


    int output_vector_size = size_have;


    size_t velFloatPitch;
//    size_t vertical_velocity_pitch;


    cutilSafeCall(cudaMalloc((void**)&d_DMatvalPtr, NnzDMat*sizeof (float)));
    cutilSafeCall(cudaMalloc((void**)&d_DMatcolPtr, NnzDMat*sizeof (int)));
    cutilSafeCall(cudaMalloc((void**)&d_DMatrowPtr, (size_have+1)*sizeof(int)));

    cutilSafeCall(cudaMalloc((void**)&d_DMatvalPtrT, NnzDMatT*sizeof (float)));
    cutilSafeCall(cudaMalloc((void**)&d_DMatcolPtrT, NnzDMatT*sizeof (int)));
    cutilSafeCall(cudaMalloc((void**)&d_DMatrowPtrT, (size_wanted+1)*sizeof(int)));


    cutilSafeCall(cudaMalloc((void**)&d_Ax, (output_vector_size)*sizeof(float)));
    cutilSafeCall(cudaMalloc((void**)&d_AxT, (size_wanted)*sizeof(float)));



    cutilSafeCall(cudaMalloc((void**)&d_A_copy, (size_have)*sizeof(float)*size_wanted));
    cutilSafeCall(cudaMalloc((void**)&d_img, sizeof(float)*size_wanted));
    cutilSafeCall(cudaMalloc((void**)&d_ydcopyqi, (size_have)*sizeof(float)));
    cutilSafeCall(cudaMalloc((void**)&d_DTqi_copy, (size_wanted)*sizeof(float)));



    cutilSafeCall(cudaMallocPitch(&d_horizontal_velocity_all,&velFloatPitch,sizeof(float)*size_wanted,N_imgs));
    cutilSafeCall(cudaMallocPitch(&d_vertical_velocity_all,&velFloatPitch,sizeof(float)*size_wanted,N_imgs));


    cutilSafeCall(cudaMalloc((void**)&d_imgT, sizeof(float)*size_have));




    cudaMemcpy(d_DMatvalPtr, DMatvalPtr, NnzDMat*sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_DMatcolPtr, DMatcolPtr, NnzDMat*sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_DMatrowPtr, DMatrowPtr, (size_have+1)*sizeof(int), cudaMemcpyHostToDevice);

    cudaMemcpy(d_DMatvalPtrT, DMatvalPtrT, NnzDMatT*sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_DMatcolPtrT, DMatcolPtrT, NnzDMatT*sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_DMatrowPtrT, DMatrowPtrT, (size_wanted+1)*sizeof(int), cudaMemcpyHostToDevice);


    cudaMemcpy(d_img, input_image_data_up, (size_wanted)*sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_imgT, input_image_data_down, (size_have)*sizeof(float), cudaMemcpyHostToDevice);



//    cout<< "After initialising the image!"<<endl;


    h_Ax          = (float*)malloc(sizeof(float)*size_have);
    h_AxT         = (float*)malloc(sizeof(float)*size_wanted);


//    cusparseStatus_t status_t;

//    status_t = cusparseScsr2dense(handle,size_have,size_wanted,descr,d_DMatvalPtr,d_DMatrowPtr,d_DMatcolPtr,d_A_copy,size_have);
//    cudaMemcpy(h_A_copy,d_A_copy,sizeof(float)*size_wanted*size_have,cudaMemcpyDeviceToHost);



//    for(int i = 0 ; i < size_have ; i++)
//    {
//        for(int j = 0 ; j < size_wanted; j++)
//        {
//            index = i*size_wanted+j;
//            h_A_copy[index] = A(i,j);
//        }
//    }

//    cout<<"A = "<<endl;
//    for(int i = 0 ; i < size_have ; i++)
//    {
//        for(int j = 0 ; j < size_wanted; j++)
//        {
//            int index = i*size_wanted+j;
//            cout<<h_A_copy[index] <<" ";
//        }
//        cout<<endl;
//    }





    {
        ScopedCuTimer cuTime("multiplication time");
        status = cusparseScsrmv(handle,CUSPARSE_OPERATION_NON_TRANSPOSE, size_have, size_wanted, 1.0, descr, d_DMatvalPtr, d_DMatrowPtr, d_DMatcolPtr, d_img, 0.0, d_Ax);
    }

    {
        ScopedCuTimer cuTime("transpose multiplication time");
        status = cusparseScsrmv(handle,CUSPARSE_OPERATION_NON_TRANSPOSE, size_wanted, size_have, 1.0, descr, d_DMatvalPtrT, d_DMatrowPtrT, d_DMatcolPtrT, d_imgT, 0.0, d_AxT);
    }




    cudaMemcpy(h_Ax,d_Ax,sizeof(float)*output_vector_size,cudaMemcpyDeviceToHost);

    cout<< endl<<"cusparse multiplication result!"<<endl;
    for(int i = 0 ; i < output_vector_size ;i++)
    {
        cout<<h_Ax[i]<<" ";
    }
    cout<<endl;

    cudaMemcpy(h_AxT,d_AxT,sizeof(float)*size_wanted,cudaMemcpyDeviceToHost);

    cout<< endl<<"cusparse multiplication transpose result!"<<endl;
    for(int i = 0 ; i < size_wanted ;i++)
    {
        cout<<h_AxT[i]<<" ";
    }
    cout<<endl;



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


// ######################### Un comment from here #########################



//    cudaMemset2D(zero, zerop, 0.f, sizeof(float)*(M+2), (N+2));

    //Copy horizontal_velocities and vertical velocities

//    float *d_u_;
//    float *d_u_;
//    float *d_u_;


    size_t upImageFloatPitch;

    float *d_px;
    float *d_py;

    float *d_ux_;
    float *d_uy_;

    float *d_u_;
    float *d_u;

    cutilSafeCall(cudaMallocPitch(&d_px,&upImageFloatPitch,sizeof(float)*N_cols_upimg,N_rows_low_img));
    cutilSafeCall(cudaMallocPitch(&d_py,&upImageFloatPitch,sizeof(float)*N_cols_upimg,N_rows_low_img));

    cutilSafeCall(cudaMallocPitch(&d_ux_,&upImageFloatPitch,sizeof(float)*N_cols_upimg,N_rows_low_img));
    cutilSafeCall(cudaMallocPitch(&d_uy_,&upImageFloatPitch,sizeof(float)*N_cols_upimg,N_rows_low_img));

    cutilSafeCall(cudaMallocPitch(&d_u_,&upImageFloatPitch,sizeof(float)*N_cols_upimg,N_rows_low_img));
    cutilSafeCall(cudaMallocPitch(&d_u,&upImageFloatPitch,sizeof(float)*N_cols_upimg,N_rows_low_img));

    int upImageStrideFloat = upImageFloatPitch/sizeof(float);
    int velStrideFloat   = velFloatPitch/sizeof(float);

    int width_up   = N_cols_upimg;
    int height_up  = N_rows_upimg;

    int width_down   = N_cols_low_img;
    int height_down  = N_rows_low_img;

    {
        launch_kernel_derivative_u(d_ux_,d_uy_,d_u_,upImageStrideFloat,width_up, height_up);

        launch_kernel_dual_variable_p(d_px,d_py,d_ux_,d_uy_,sigma,upImageStrideFloat,width_up,height_up);

        for(int i = 0 ; i < N_imgs; i++)
        {
            //copy_qi_into_yd
//            cudaMemcpy(d_ydcopyqi,qi+(size_have)*i,sizeof(float)*size_have,cudaMemcpyDeviceToDevice);

            //do W_iu
            launch_kernel_Mult_Wi_u(d_ydcopyqi, d_ydcopyqiStride, d_u_, upImageStrideFloat, d_horizontal_velocity_all+size_wanted*i, d_vertical_velocity_all+size_wanted*i,
                                    velStrideFloat, i, width_up, height_up);

            //do B*(W_iu)
            //float *out, int outStride, float *in, int inStride, float* blur_kernel, int blurWidth, int width, int height
            launch_kernel_blur(d_blur_result,imageStrideFloat, d_ydcopyqi, upImageStrideFloat, blur_kernel, blurWidth, width_up, height_up);

            //do D*(B*(W_iu))
            cusparseScsrmv(handle,CUSPARSE_OPERATION_NON_TRANSPOSE, size_have, size_wanted, 1.0, descr, d_DMatvalPtr, d_DMatrowPtr, d_DMatcolPtr, d_blur_result, 0.0, d_res);

            //Subtract f_i and Add to y;
            launch_kernel_q_SubtractDBWiu_fAdd_yAndReproject(qi+(size_have)*i,
                                                             d_res, downImageStrideFloat,
                                                             d_fi, imgVectorStrideFloat,
                                                             sigma_q, xisqr, epsilon_d,
                                                             width_down, height_down);

            // copy y to qi;
            // cudaMemcpy(qi+(size_have)*i,d_ydcopyqi,sizeof(float)*size_have,cudaMemcpyDeviceToDevice);
        }

        for(int i = 0 ; i < N_imgs ; i++)
        {
            //copy_qi_to_yu;
            cudaMemcpy(qi+(size_have)*i,d_ydcopyqi,sizeof(float)*size_have,cudaMemcpyDeviceToDevice);

            //do D^{T}*yu;
            cusparseScsrmv(handle,CUSPARSE_OPERATION_NON_TRANSPOSE, size_have, size_wanted, 1.0, descr, d_DMatvalPtrT, d_DMatrowPtrT, d_DMatcolPtrT, d_ydcopyqi, 0.0, d_DTqi_copy);

            //do B^{T}*(D^{T}*yu);
            launch_kernel_blur(d_BTDTqi, upImageStrideFloat, d_DTqi_copy, upImageStrideFloat,blur_kernelT,blurWidth, width_up, height_up);

            //copy the contents back t
            cudaMemcpy(d_dual_save_qT+(size_wanted)*i,d_BTDTqi,sizeof(float)*size_wanted,cudaMemcpyDeviceToDevice);

        }

        // do batch Wi^{T}yu;
        cusparseScsrmv(handle,CUSPARSE_OPERATION_NON_TRANSPOSE, size_have, size_wanted, 1.0, descr, d_WMatvalPtrT, d_WMatrowPtrT, d_WMatcolPtrT, d_dual_save_qT, 0.0, d_dual_save_qT);

        //launch kernel u ;
        launch_kernel_update_u(d_px,d_py,d_u,d_u_,d_dual_save_qT,stride,width,height,tau,lambda);
    }



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

