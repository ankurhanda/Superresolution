#ifndef _KERNEL_UPDATE_Q_
#define _KERNEL_UPDATE_Q_

#include <stdio.h>
#include <cutil_inline.h>

#include "cuPrintf.cu"

#ifndef max
#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )
#endif

#ifndef min
#define min( a, b ) ( ((a) < (b)) ? (a) : (b) )
#endif


__global__ void kernel_q_SubtractDBWiu_fAdd_yAndReproject(float *d_qi, int qStride,
                                                          float *d_DBWiu_fi, int DBWiu_fiStride,
                                                          float sigma_q,float xisqr,float epsilon_d,
                                                          int N_cols_low_img, int N_rows_low_img, int N_imgs)
{


    //q^{n+1} = \frac{q^n + \sigma \xi^{2} (DBWu_ - f)}{ 1 + epsilon_d*sigma_q/xisqr}
    // q^{n+1} =  max(-xisqr, min(xisqr, q^{n+1}))

    //unsigned int x = blockIdx.x*blockDim.x + threadIdx.x;
    //unsigned int y = blockIdx.y*blockDim.y + threadIdx.y;
    unsigned int tid = blockIdx.x*blockDim.x + threadIdx.x;

    // write output vertex
    if ( tid < N_cols_low_img*N_rows_low_img*N_imgs)
    {
        if(tid == 0)
        {
            cuPrintf("d_DBWiu_fi[tid]=%f\n",d_DBWiu_fi[tid]);
            cuPrintf("d_qi[tid]=%f\n", d_qi[tid]);
        }
       float result_val = d_qi[tid] + sigma_q*(d_DBWiu_fi[tid]);
//       result_val = max(-1.0f, min(1.0f, result_val));
       d_qi[tid] = result_val;
    }


}


extern "C" void launch_kernel_q_SubtractDBWiu_fAdd_yAndReproject(float *d_qi, int qStride,
                                                                 float *d_DBWiu_fi, int DBWiu_fiStride,
                                                                 float sigma_q,float xisqr,float epsilon_d,
                                                                 int N_cols_low_img, int N_rows_low_img, int N_imgs)
{
    dim3 block(9, 1, 1);
    dim3 grid(N_cols_low_img*N_rows_low_img*N_imgs/9, 1);

    cudaPrintfInit();


    kernel_q_SubtractDBWiu_fAdd_yAndReproject<<< grid, block>>>(d_qi, qStride,
                                                                d_DBWiu_fi, DBWiu_fiStride,
                                                                sigma_q,xisqr, epsilon_d,
                                                                N_cols_low_img, N_rows_low_img, N_imgs);

    cudaPrintfDisplay(stdout, true);
    cudaPrintfEnd();

    cutilCheckMsg("execution failed\n");
}


#endif // #ifndef _SIMPLEGL_KERNEL_H_
