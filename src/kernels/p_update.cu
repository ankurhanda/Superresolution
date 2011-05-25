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


__global__ void kernel_dualp(float *px, float *py, float *ux_, float *uy_, float epsilon_u, float sigma_p, float lambda,
                             unsigned int stride,unsigned int width)
{




    unsigned int x = blockIdx.x*blockDim.x + threadIdx.x;
    unsigned int y = blockIdx.y*blockDim.y + threadIdx.y;

    // write output vertex

    px[y*width+x] = (px[y*width+x] + sigma_p*lambda*ux_[y*width+x]);
    py[y*width+x] = (py[y*width+x] + sigma_p*lambda*uy_[y*width+x]);

    float pxval = px[y*width+x];
    float pyval = py[y*width+x];

    float reprojection = 0;
    reprojection   = sqrt(pxval*pxval + pyval*pyval);
    reprojection   = max(1.0f,reprojection);

    px[y*width+x] = px[y*width+x]/reprojection;
    py[y*width+x] = py[y*width+x]/reprojection;


//    px[y*stride+x] = (px[y*stride+x] + sigma_p*lambda*ux_[y*stride+x]);
//    py[y*stride+x] = (py[y*stride+x] + sigma_p*lambda*uy_[y*stride+x]);

//    float pxval = px[y*stride+x];
//    float pyval = py[y*stride+x];

//    float reprojection = 0;
//    reprojection   = sqrt(pxval*pxval + pyval*pyval);
//    reprojection   = max(1.0f,reprojection);

//    px[y*stride+x] = px[y*stride+x]/reprojection;
//    py[y*stride+x] = py[y*stride+x]/reprojection;


}



// Wrapper for the __global__ call that sets up the kernel call
extern "C" void launch_kernel_dual_variable_p(float *px, float *py, float* ux_, float *uy_, float epsilon_u, float sigma_p, float lambda,
                                              unsigned int stride, unsigned int mesh_width, unsigned int mesh_height)
{
    // execute the kernel
    dim3 block(1, 1, 1);
    dim3 grid(mesh_width / block.x, mesh_height / block.y, 1);
    kernel_dualp<<< grid, block>>>(px,py,ux_,uy_,epsilon_u, sigma_p, lambda, stride, mesh_width);
    cutilCheckMsg("execution failed\n");
}

#endif // #ifndef _SIMPLEGL_KERNEL_H_
