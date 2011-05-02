///*
// * Copyright 1993-2010 NVIDIA Corporation.  All rights reserved.
// *
// * Please refer to the NVIDIA end user license agreement (EULA) associated
// * with this source code for terms and conditions that govern your use of
// * this software. Any use, reproduction, disclosure, or distribution of
// * this software and related documentation outside the terms of the EULA
// * is strictly prohibited.
// *
// */

// /* This example demonstrates how to use the Cuda OpenGL bindings with the
//  * runtime API.
//  * Device code.
//  */

//#ifndef _SIMPLEGL_KERNEL_H_
//#define _SIMPLEGL_KERNEL_H_

//#include <stdio.h>
//#include <cutil_inline.h>
//#ifndef max
//#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )
//#endif

//#ifndef min
//#define min( a, b ) ( ((a) < (b)) ? (a) : (b) )
//#endif


///////////////////////////////////////////////////////////////////////////////////
//////! Simple kernel to modify vertex positions in sine wave pattern
//////! @param data  data in global memory
///////////////////////////////////////////////////////////////////////////////////

////__global__ void kernel(int *d_Darray, int size)
////{
//////    unsigned int x = blockIdx.x*blockDim.x + threadIdx.x;
//////    unsigned int y = blockIdx.y*blockDim.y + threadIdx.y;

////    // write output vertex

//////    printf("d_Darray[%d]= %d",threadIdx.x,d_Darray[threadIdx.x]);
////}


//__global__ void kernel_dualp(float *px, float *py, float *ux_, float *uy_, float sigma, unsigned int stride, unsigned int width, unsigned int height)
//{


//    unsigned int x = blockIdx.x*blockDim.x + threadIdx.x;
//    unsigned int y = blockIdx.y*blockDim.y + threadIdx.y;

//    // write output vertex
//    px[y*stride+x] = px[y*stride+x] + sigma* ux_[y*stride+x];
//    py[y*stride+x] = py[y*stride+x] + sigma* uy_[y*stride+x];

//    float pxval = px[y*stride+x];
//    float pyval = py[y*stride+x];

//    float reprojection = 0;
//    reprojection   = sqrt(pxval*pxval + pyval*pyval);
//    reprojection   = max(1,reprojection);

//    px[y*stride+x] = px[y*stride+x]/reprojection;
//    py[y*stride+x] = py[y*stride+x]/reprojection;


//}


//__global__ void kernel_update_u(float *px, float *py, float *u, float *u_, float* g ,unsigned int stride, unsigned int width, unsigned int height, float tau, float lambda)
//{

//    unsigned int x = blockIdx.x*blockDim.x + threadIdx.x;
//    unsigned int y = blockIdx.y*blockDim.y + threadIdx.y;

//    float dxp = 0 , dyp = 0;

//    if ( x >= 1 && x < width )  dxp = px[y*stride+x] - px[y*stride+(x-1)];

//    if ( y >= 1 && y < height ) dyp = py[y*stride+x] - py[(y-1)*stride+x];

//    float divp = dxp + dyp;

//    float u_prev = u[y*stride+x];

//    u[y*stride+x] = (u_prev + tau*divp+ tau*lambda*g[y*stride+x])/(1+tau*lambda);

//    u_[y*stride+x] = 2*u[y*stride+x] - u_prev;
//   //  u_[y*stride+x] = u[y*stride+x];// - u_prev;


//}


////extern "C" void launch_kernel(int *d_Darray, int size)
////{
////    dim3 block(size,1,1);
////    dim3 grid(1,1);
////    kernel<<< grid, block>>>(d_Darray,size);
////    cutilCheckMsg("execution failed\n");
////}




//#endif // #ifndef _SIMPLEGL_KERNEL_H_
