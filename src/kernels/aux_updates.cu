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


__global__ void kernel_Mult_Wi_u(float *u, float *horizontal_flow, float* vertical_flow, int imgNo,
                                 unsigned int stride, unsigned int mesh_width, unsigned int mesh_height)
{


    //p^{n+1} = \frac{p^n + \sigma \nabla u^{n}}{1 + sigma*epsilon_u/ lambda}
    //p^{n+1} = p^{n+1} / max ( 1, |p^{n+1}|/lambda )

//    unsigned int x = blockIdx.x*blockDim.x + threadIdx.x;
//    unsigned int y = blockIdx.y*blockDim.y + threadIdx.y;

//    // write output vertex
//    px[y*stride+x] = (px[y*stride+x] + sigma* ux_[y*stride+x])/(1+sigma*epsilon_u/lambda);
//    py[y*stride+x] = (py[y*stride+x] + sigma* uy_[y*stride+x])/(1+sigma*epsilon_u/lambda);

//    float pxval = px[y*stride+x];
//    float pyval = py[y*stride+x];

//    float reprojection = 0;
//    reprojection   = sqrt(pxval*pxval + pyval*pyval);
//    reprojection   = max(1,reprojection/lambda);

//    px[y*stride+x] = px[y*stride+x]/reprojection;
//    py[y*stride+x] = py[y*stride+x]/reprojection;


}



// Wrapper for the __global__ call that sets up the kernel call
extern "C" void launch_kernel_Mult_Wi_u(float *u, float *horizontal_flow, float* vertical_flow, int imgNo,
                                              unsigned int stride, unsigned int mesh_width, unsigned int mesh_height)
{
    // execute the kernel
    dim3 block(8, 8, 1);
    dim3 grid(mesh_width / block.x, mesh_height / block.y, 1);
    kernel_Mult_Wi_u<<< grid, block>>>(u, horizontal_flow, vertical_flow, imgNo, stride, mesh_width, mesh_height);
    cutilCheckMsg("execution failed\n");
}

#endif // #ifndef _SIMPLEGL_KERNEL_H_
