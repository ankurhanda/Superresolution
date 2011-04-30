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

    srand ( time(NULL) );

    /*cudaGLSetGLDevice(cutGetMaxGflopsDeviceId());
    CreateGlutWindowAndBind("Main",width_window*2,height_window*2);
    glewInit();*/


//    int N_cols_upimgT = 7;
//    int N_rows_upimgT = 7;
//    int size_wantedW = N_cols_upimgT*N_rows_upimgT;


//    int N_imgs = 1;
//    std::vector< std::map <int, float> > h_vectorofMaps(N_imgs);


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








    CVD::Image<float> input_image;

    img_load(input_image,"../data/images/car_001_up.pgm");

    int N_cols_low_img = 4;
    int N_rows_low_img = 4;

    int size_have  = N_rows_low_img*N_cols_low_img;
    float scale = 2;

    int N_rows_upimg = (int)(scale*N_rows_low_img);
    int N_cols_upimg = (int)(scale*N_cols_low_img);

    int size_wanted  = N_rows_upimg*N_cols_upimg;

    int NnzDMat = 4*size_have;
    int NnzDMatT = 1*size_wanted;


    float *DMatvalPtr = new float[NnzDMat];
    int *DMatcolPtr = new int[NnzDMat];
    int *DMatrowPtr = new int[size_have+1];
    int *DMatrowPtrT = new int[size_wanted+1];


    float *DMatvalPtrT = new float[NnzDMatT];
    int *DMatcolPtrT = new int[NnzDMatT];

    int index = 0, prev_row = -1;


    TooN::Matrix<>A(size_have,size_wanted);
    A = TooN::Zeros(size_have,size_wanted);

    std::map<int,float>matindex_matval;
    std::map<int,float>matindex_matvalT;


    //DMatvalPtr, DMatrowPtr, DMatcolPtr,
    buildDMatrixLebesgueMeasure(NnzDMat, size_have,size_wanted, N_rows_upimg, N_cols_upimg, scale, A, matindex_matval,matindex_matvalT);
    cout << "In here" << endl;


    std::map<int,float>::iterator it;
    cout << "Map begins " << endl;

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
    index = 0;
    for(it = matindex_matvalT.begin(); it != matindex_matvalT.end(); it++ )
    {
        cout << (it->first)%size_have << " " ;//<< it->second << endl;
        DMatcolPtrT[index] = (it->first)%size_have;
        index++;
    }

    cout << "Values ="<<endl;
    index = 0;
    for(it = matindex_matvalT.begin(); it != matindex_matvalT.end(); it++ )
    {

        DMatvalPtrT[index]  = it->second;
        cout << it->second << " ";
        index++;

    }

    index = 0; prev_row = -1;
    for(it = matindex_matval.begin(); it != matindex_matval.end(); it++ )
    {
        int row = ((it->first) - (it->first)%size_have)/size_have;

        if ( DMatrowPtrT[row] == 0 && prev_row != row)
        {
            DMatrowPtrT[row] = index;
            prev_row = row;
        }

        index++;
    }

    cout <<"DrowPTrT"<<endl;
    for(int i = 0; i < size_wanted+1 ; i++)
    {
        cout << DMatrowPtrT[i] << " ";
    }
    cout << endl;

    cout << "Transpose Data ends " << endl;



    index = 0; prev_row=-1;
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

    float *d_DMatvalPtrT;
    int *d_DMatcolPtrT;
    int *d_DMatrowPtrT;


    float *d_img;
    float *d_A;
    float *d_AT;

    float *d_A_copy;
    float *d_A_copyT;

    float *h_A;
    float *h_AT;


    cutilSafeCall(cudaMalloc((void**)&d_DMatvalPtr, NnzDMat*sizeof (float)));

    cutilSafeCall(cudaMalloc((void**)&d_DMatcolPtr, NnzDMat*sizeof (int)));

    cutilSafeCall(cudaMalloc((void**)&d_DMatrowPtr, (size_have+1)*sizeof(int)));


    cutilSafeCall(cudaMalloc((void**)&d_DMatvalPtrT, NnzDMatT*sizeof (float)));

    cutilSafeCall(cudaMalloc((void**)&d_DMatcolPtrT, NnzDMatT*sizeof (int)));

    cutilSafeCall(cudaMalloc((void**)&d_DMatrowPtrT, (size_wanted+1)*sizeof(int)));


    cutilSafeCall(cudaMalloc((void**)&d_A, (size_have)*sizeof(float)*size_wanted));
    cutilSafeCall(cudaMalloc((void**)&d_AT, (size_have)*sizeof(float)*size_wanted));




    cutilSafeCall(cudaMalloc((void**)&d_A_copy, (size_have)*sizeof(float)*size_wanted));
    cutilSafeCall(cudaMalloc((void**)&d_A_copyT, (size_have)*sizeof(float)*size_wanted));

    cutilSafeCall(cudaMallocPitch(&(d_img ), &(imagePitchFloat), N_cols_upimg* sizeof (float), N_rows_upimg));

    cudaMemcpy(d_DMatvalPtr, DMatvalPtr, NnzDMat*sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_DMatcolPtr, DMatcolPtr, NnzDMat*sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_DMatrowPtr, DMatrowPtr, (size_have+1)*sizeof(int), cudaMemcpyHostToDevice);

    cudaMemcpy(d_DMatvalPtrT, DMatvalPtrT, NnzDMatT*sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_DMatcolPtrT, DMatcolPtrT, NnzDMatT*sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_DMatrowPtrT, DMatrowPtrT, (size_wanted+1)*sizeof(int), cudaMemcpyHostToDevice);




    int* h_nnzPerRow;
    int* d_nnzPerRow;

    float* d_csrValA;
    float* h_csrValA;

    int* d_csrRowPtrA;
    int* h_csrRowPtrA;

    int* d_csrColIndA;
    int* h_csrColIndA;


    int* h_nnzPerRowT;
    int* d_nnzPerRowT;

    float* d_csrValAT;
    float* h_csrValAT;

    int* d_csrRowPtrAT;
    int* h_csrRowPtrAT;

    int* d_csrColIndAT;
    int* h_csrColIndAT;





    cutilSafeCall(cudaMalloc((void**)&d_nnzPerRow, size_have*sizeof (int)));
    cutilSafeCall(cudaMalloc((void**)&d_csrRowPtrA, (size_have+1)*sizeof (int)));
    cutilSafeCall(cudaMalloc((void**)&d_csrColIndA, NnzDMat*sizeof (int)));
    cutilSafeCall(cudaMalloc((void**)&d_csrValA, NnzDMat*sizeof (float)));


    cutilSafeCall(cudaMalloc((void**)&d_nnzPerRowT, size_wanted*sizeof (int)));
    cutilSafeCall(cudaMalloc((void**)&d_csrRowPtrAT, (size_wanted+1)*sizeof (int)));
    cutilSafeCall(cudaMalloc((void**)&d_csrColIndAT, NnzDMatT*sizeof (int)));
    cutilSafeCall(cudaMalloc((void**)&d_csrValAT, NnzDMatT*sizeof (float)));



    h_nnzPerRow  = (int*)malloc(sizeof(int)*size_have);
    h_csrValA    = (float*)malloc(sizeof(float)*NnzDMat);
    h_csrRowPtrA = (int*)malloc(sizeof(int)*(size_have+1));
    h_csrColIndA = (int*)malloc(sizeof(int)*size_have);
    h_A          = (float*)malloc(sizeof(float)*size_have*size_wanted);


    h_nnzPerRowT  = (int*)malloc(sizeof(int)*size_wanted);
    h_csrValAT    = (float*)malloc(sizeof(float)*NnzDMatT);
    h_csrRowPtrAT = (int*)malloc(sizeof(int)*(size_wanted+1));
    h_csrColIndAT = (int*)malloc(sizeof(int)*size_wanted);
    h_AT          = (float*)malloc(sizeof(float)*size_have*size_wanted);






    for (int i  = 0 ; i < size_have;i++)
        h_nnzPerRow[i] = 4;

    for (int i  = 0 ; i < size_wanted;i++)
        h_nnzPerRowT[i] = 1;



    cout << endl;
    index = 0;
    int indexT = 0;
    for(int i = 0 ; i < size_have ; i++)
    {
        for(int j = 0 ; j < size_wanted; j++)
        {
            index = i*size_wanted+j;
            h_A[index] = A(i,j);

            indexT = j*size_have +i;
            h_AT[indexT] = A(i,j);

        }
    }



    cudaMemcpy(d_A,h_A,sizeof(float)*size_have*size_wanted,cudaMemcpyHostToDevice );
    cudaMemcpy(d_nnzPerRow,h_nnzPerRow,sizeof(int)*size_have,cudaMemcpyHostToDevice );


    cudaMemcpy(d_AT,h_AT,sizeof(float)*size_have*size_wanted,cudaMemcpyHostToDevice );
    cudaMemcpy(d_nnzPerRowT,h_nnzPerRowT,sizeof(int)*size_wanted,cudaMemcpyHostToDevice );


   cusparseSdense2csr(handle,size_have,size_wanted,descr,d_A,size_have,d_nnzPerRow,d_csrValA,d_csrRowPtrA,d_csrColIndA);

   cusparseSdense2csr(handle,size_wanted,size_have,descr,d_AT,size_wanted,d_nnzPerRowT,d_csrValAT,d_csrRowPtrAT,d_csrColIndAT);




   cudaMemcpy(h_csrValA,d_csrValA,sizeof(float)*NnzDMat,cudaMemcpyDeviceToHost );
   cudaMemcpy(h_csrRowPtrA,d_csrRowPtrA,sizeof(int)*(size_have+1),cudaMemcpyDeviceToHost );
   cudaMemcpy(h_csrColIndA,d_csrColIndA,sizeof(int)*NnzDMat,cudaMemcpyDeviceToHost );


   cudaMemcpy(h_csrValAT,d_csrValAT,sizeof(float)*NnzDMatT,cudaMemcpyDeviceToHost );
   cudaMemcpy(h_csrRowPtrAT,d_csrRowPtrAT,sizeof(int)*(size_wanted+1),cudaMemcpyDeviceToHost );
   cudaMemcpy(h_csrColIndAT,d_csrColIndAT,sizeof(int)*NnzDMatT,cudaMemcpyDeviceToHost );


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


   cout <<"\n Here is the csrRowPtrT at Host" << endl;
   for(int i = 0 ; i < size_wanted+1; i++)
   {
       cout << h_csrRowPtrAT[i]<<" ";
   }
   cout << endl;

   cout << "csrcolIndAT " << endl;
   for(int i = 0 ; i < NnzDMatT ; i++)
   {
       cout << h_csrColIndAT[i] << " ";
   }
   cout << endl;

   for(int i = 0 ; i < NnzDMatT ; i++)
   {
       cout << h_csrValAT[i]<< " ";
   }
   cout << endl;


    cusparseStatus_t status_t;

    status_t = cusparseScsr2dense(handle,size_have,size_wanted,descr,d_DMatvalPtr,d_DMatrowPtr,d_DMatcolPtr,d_A_copy,size_have);



    if ( status_t == CUSPARSE_STATUS_SUCCESS)
    {
        cout << "Bingo!" << endl;
    }

    status_t = cusparseScsr2dense(handle,size_wanted,size_have,descr,d_DMatvalPtrT,d_DMatrowPtrT,d_DMatcolPtrT,d_A_copyT,size_wanted);



    float *hh_A;

    hh_A = (float*)malloc(sizeof(float)*size_wanted*size_have);
    cudaMemcpy(hh_A,d_A_copy,sizeof(float)*size_wanted*size_have,cudaMemcpyDeviceToHost);
    cout << "hh_A copied here" << endl;

//    for(int i = 0 ; i < size_wanted*size_have;i++)
//    {
//        cout << hh_A[i] << " ";
//    }
//    cout << endl;
//    cout << "Copied Data!" << endl;
    for(int i = 0 ; i < size_have;i++)
    {
        for(int j = 0 ; j < size_wanted ; j++ )
        {
            cout << hh_A[i*size_wanted+j] << " ";
        }
        cout << endl;
    }

    cudaMemcpy(hh_A,d_A_copyT,sizeof(float)*size_wanted*size_have,cudaMemcpyDeviceToHost);

    for(int i = 0 ; i < size_wanted;i++)
    {
        for(int j = 0 ; j < size_have ; j++ )
        {
            cout << hh_A[i*size_have+j] << " ";
        }
        cout << endl;
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
