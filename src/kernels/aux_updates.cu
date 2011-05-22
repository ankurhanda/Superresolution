#ifndef _KERNEL_UPDATE_P_
#define _KERNEL_UPDATE_P_

#include <stdio.h>
#include <cutil_inline.h>
#ifndef max
#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )
#endif

#ifndef min
#define min( a, b ) ( ((a) < (b)) ? (a) : (b) )
#endif


__global__ void kernel_Mult_Wi_u(float *out, int outStride, float *d_u_, int u_Stride, float *horizontal_flow, float* vertical_flow, int velStride,
                                 int imgNo, int width, int height)
{


    unsigned int x = blockIdx.x*blockDim.x + threadIdx.x;
    unsigned int y = blockIdx.y*blockDim.y + threadIdx.y;

    float x_ = x;
    float y_ = y;

    x_ = min(width-1,max(0.0f,x_ + horizontal_flow[y*velStride+x]));
    y_ = min(height-1,max(0.0f,y_ + vertical_flow[y*velStride+x]));

    int flr_x = floor(x_);
    int flr_y = floor(y_);

    float x_ratio = x_ - flr_x;
    float y_ratio = y_ - flr_y;

    float val = ((1-x_ratio)*(1-y_ratio))*d_u_[flr_y*u_Stride+flr_x];

    if ( flr_x + 1 < width )
        val +=  (x_ratio*(1-y_ratio))*d_u_[flr_y*u_Stride + (flr_x+1)];

    if ( flr_y + 1 < height )
    {
        val +=  ((1-x_ratio)*y_ratio)*d_u_[(flr_y+1)*u_Stride + (flr_x)];

        if ( flr_x+1 < width )
            val +=  (x_ratio*y_ratio)*d_u_[(flr_y+1)*u_Stride + (flr_x+1)];
    }

    out[y*outStride+x] = val;
}



// Wrapper for the __global__ call that sets up the kernel call
extern "C" void launch_kernel_Mult_Wi_u(float *out, int outStride, float *d_u_, int u_Stride, float *horizontal_flow, float* vertical_flow, int velStride,
                                         int imgNo, int width, int height)
{
    // execute the kernel
    dim3 block(8, 8, 1);
    dim3 grid(width / block.x, height / block.y, 1);
    kernel_Mult_Wi_u<<< grid, block>>>(out, outStride, d_u_, u_Stride,  horizontal_flow, vertical_flow, velStride, imgNo, width, height);
    cutilCheckMsg("execution failed\n");
}


__global__ void kernel_blur(float *out, int outStride, float *in, int inStride, float* blur_kernel, int blurWidth, int width, int height)
{

    unsigned int x = blockIdx.x*blockDim.x + threadIdx.x;
    unsigned int y = blockIdx.y*blockDim.y + threadIdx.y;

    float val = 0;

    float sum_kernel = 0;


    for(int i = -blurWidth/2 ; i <= blurWidth/2 ; i++ )
    {
        for(int j = -blurWidth/2 ; j <= blurWidth/2 ; j++ )
        {
            if ( y+i < height && x+j < width )
            {
                val += blur_kernel[i*blurWidth+j]*in[(y+i)*inStride+(x+j)];
                sum_kernel += blur_kernel[i*blurWidth+j];
            }
        }
    }

    out[y*outStride+x] = (val/sum_kernel);

}


__global__ void kernel_subtract(float* d_fi, int imgVectorsStrideFloat, float* d_res_stacked, int qVectorsStrideFloat, int size)
{

    unsigned int x = blockIdx.x*blockDim.x + threadIdx.x;
    unsigned int y = blockIdx.y*blockDim.y + threadIdx.y;

    if ( y*qVectorsStrideFloat+x < size)
    {
        d_res_stacked[y*qVectorsStrideFloat+x] = d_res_stacked[y*qVectorsStrideFloat+x]-d_fi[y*qVectorsStrideFloat+x];
    }

}



extern "C" void launch_kernel_blur(float *out, int outStride, float *in, int inStride, float* blur_kernel, int blurWidth, int width, int height)
{
    // execute the kernel
    dim3 block(8, 8, 1);
    dim3 grid(width / block.x, height / block.y, 1);
    kernel_blur<<< grid, block>>>(out, outStride, in, inStride, blur_kernel, blurWidth, width, height);
    cutilCheckMsg("execution failed\n");
}

extern "C" void  launch_kernel_subtract(float* d_fi, int imgVectorsStrideFloat, float* d_res_stacked, int qVectorsStrideFloat, int size, int width, int height)
{

    // execute the kernel
    dim3 block(8, 8, 1);
    dim3 grid(width / block.x, height / block.y, 1);
    kernel_subtract<<< grid, block>>>(d_fi, imgVectorsStrideFloat, d_res_stacked, qVectorsStrideFloat, size);
    cutilCheckMsg("execution failed\n");

}


//__global__ void launch_kernel_blurTranspose(float *out, int outStride, float *in, int inStride, float* blur_kernelT, int blurWidth)
//{

//    unsigned int x = blockIdx.x*blockDim.x + threadIdx.x;
//    unsigned int y = blockIdx.y*blockDim.y + threadIdx.y;

//    float val = 0;



//    for(int i = -blurWidth/2 ; i <= blurWidth/2 ; i++ )
//    {
//        for(int j = -blurWidth/2 ; j <= blurWidth/2 ; j++ )
//        {
//            if ( y+i < Ny && x+j < Nx )
//            {
//                val += blur_kernel[i*blurWidth+j]*in[(y+i)*inStride+(x+j)];
//            }
//        }
//    }

//    out[y*outStride+x] = val;

//}

//extern "C" void launch_kernel_blurTranspose(float *out, int outStride, float *in, int inStride, float* blur_kernel, int blurWidth)
//{
//    // execute the kernel
//    dim3 block(8, 8, 1);
//    dim3 grid(mesh_width / block.x, mesh_height / block.y, 1);
//    kernel_blur_Wi_u<<< grid, block>>>(out, outStide, in, inStride, blur_kernel, blurWidth);
//    cutilCheckMsg("execution failed\n");
//}



#endif // #ifndef _SIMPLEGL_KERNEL_H_
