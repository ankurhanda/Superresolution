#ifndef _KERNEL_UPDATE_Q_
#define _KERNEL_UPDATE_Q_

#include <stdio.h>
#include <cutil_inline.h>
#ifndef max
#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )
#endif

#ifndef min
#define min( a, b ) ( ((a) < (b)) ? (a) : (b) )
#endif


__global__ void kernel_q_SubtractDBWiu_fAdd_yAndReproject(float *result, int resultStride,
                                                          float *d_DBWiu,int DBWiuStride,
                                                          float *d_fi,   int imgStride,
                                                          float sigma_q,float xisqr,float epsilon_d,
                                                          int width_down, int height_down)
{


    //q^{n+1} = \frac{q^n + \sigma \xi^{2} (DBWu_ - f)}{ 1 + epsilon_d*sigma_q/xisqr}
    //q^{n+1} =  max(-1.0f, min(1.0f, q^{n+1}))

    unsigned int x = blockIdx.x*blockDim.x + threadIdx.x;
    unsigned int y = blockIdx.y*blockDim.y + threadIdx.y;

    // write output vertex
    if ( y*resultStride + x < width_down*height_down)
    {

       float result_val = result[y*resultStride+x] + sigma_q*xisqr*(d_DBWiu[y*DBWiuStride+x]-d_fi[y*imgStride+x]);
       result_val = result_val/(1 + sigma_q*epsilon_d/xisqr);

       result_val = max(-xisqr*1.0f, min(xisqr, result_val)); // clamped reprojection

       result[y*resultStride+x] = result_val;
    }

}


extern "C" void launch_kernel_q_SubtractDBWiu_fAdd_yAndReproject(float *result, int resultStride,
                                                                 float *d_DBWiu,int DBWiuStride,
                                                                 float *d_fi,   int imgStride,
                                                                 float sigma_q,float xisqr,float epsilon_d,
                                                                 int width_down, int height_down)
{
    dim3 block(8, 8, 1);
    dim3 grid(width_down / block.x, height_down / block.y, 1);
    kernel_q_SubtractDBWiu_fAdd_yAndReproject<<< grid, block>>>(result, resultStride,
                                                                d_DBWiu, DBWiuStride,
                                                                d_fi, imgStride,
                                                                sigma_q, xisqr, epsilon_d, width_down, height_down);//N_imgs, q, DBWu_, epsilon_d, sigma, f, xisqr, stride);
    cutilCheckMsg("execution failed\n");
}


#endif // #ifndef _SIMPLEGL_KERNEL_H_
