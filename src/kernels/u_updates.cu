#ifndef _KERNEL_UPDATE_U_
#define _KERNEL_UPDATE_U_

#include <stdio.h>
#include <cutil_inline.h>
#ifndef max
#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )
#endif

#ifndef min
#define min( a, b ) ( ((a) < (b)) ? (a) : (b) )
#endif


__global__ void kernel_dualu(float tau, float *px, float *py, float xisqr, float *sum_wiT_biT_diT_q, int width, int height,
                             unsigned int stride)
{

    //u^{n+1} = u^{n} - tau( -divp^{n+1} + \xi^{2} \sum_{i=1}^{N}(W^{T}B^{T}D^{T}q^{n+1} )

    unsigned int x = blockIdx.x*blockDim.x + threadIdx.x;
    unsigned int y = blockIdx.y*blockDim.y + threadIdx.y;

    // write output vertex

    float dxp = 0 , dyp = 0;

    if ( x >= 1 && x < width )  dxp = px[y*stride+x] - px[y*stride+(x-1)];

    if ( y >= 1 && y < height ) dyp = py[y*stride+x] - py[(y-1)*stride+x];

    float divp = dxp + dyp;

    float prev_u = u[y*stride+x];

    u[y*stride+x] = prev_u - tau*( -divp + xisqr*sum_wiT_biT_diT_q[y*stride+x]);

    u[y*stride+x] = 2*u[y*stride+x] - prev;

}


// Wrapper for the __global__ call that sets up the kernel call
extern "C" void launch_kernel_dual_variable_u(float *px, float *py, float* ux_, float *uy_, float epsilon_u, float sigma, float lambda,
                                              unsigned int stride, unsigned int mesh_width, unsigned int mesh_height)
{
    // execute the kernel
    dim3 block(8, 8, 1);
    dim3 grid(mesh_width / block.x, mesh_height / block.y, 1);
    kernel_dualp<<< grid, block>>>(tau, px, py, xisqr, sum_wiT_biT_diT_q, width, height, stride);
    cutilCheckMsg("execution failed\n");
}

#endif // #ifndef _SIMPLEGL_KERNEL_H_
