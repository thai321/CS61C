/*
 * Proj 3-2 SKELETON
 */

#include <float.h>
#include <stdlib.h>
#include <stdio.h>
#include <cuda_runtime.h>
#include <cutil.h>
#include "utils.h"



__global__ void transKernel(float *array1, float *array2, int width) {

    int current_index = (blockIdx.y*blockDim.y + threadIdx.y)* width +(blockIdx.x*blockDim.x + threadIdx.x);
    int replace = (blockIdx.x*blockDim.x + threadIdx.x)*width + blockIdx.y*blockDim.y + threadIdx.y;
    if (current_index< width*width) {
       array2[replace] = array1[current_index]; 
    }
}

void transpose(float *array1, float *array2, int width) {
    dim3 dim_blocks_per_grid(width/4, width/4);
    dim3 dim_threads_per_block(4, 4, 1);
    transKernel<<<dim_blocks_per_grid, dim_threads_per_block>>>(array1, array2, width);
    cudaThreadSynchronize();
    CUT_CHECK_ERROR("");
}

__global__ void flipKernel(float *array1, int width) {
    int current_index = blockIdx.x*blockDim.x + threadIdx.x;
    int replace = (width - 1 - current_index/width) * width + current_index % width;
    if (current_index < width * width / 2) {
        float temp = array1[current_index];
        array1[current_index] = array1[replace];
        array1[replace] = temp;
    }
}

void flip_vertical(float *array1, int width) {
    int threads_per_block = 512;
    int blocks_per_grid = width * width/2 / threads_per_block + 1;

    dim3 dim_blocks_per_grid(blocks_per_grid, 1);
    dim3 dim_threads_per_block(threads_per_block, 1, 1);
    flipKernel<<<dim_blocks_per_grid, dim_threads_per_block>>>(array1, width);
    cudaThreadSynchronize();
    CUT_CHECK_ERROR("");
}

__global__ void distanceKernel(float *image, int i_width, float *temp, int t_width, float *blank) {
    int calc_index = (blockIdx.y*blockDim.y + threadIdx.y)*t_width + blockIdx.x*blockDim.x + threadIdx.x;
    float i = image[(blockIdx.y*blockDim.y + threadIdx.y)*i_width + blockIdx.x*blockDim.x + threadIdx.x];
    float j = temp[calc_index];
    blank[calc_index] = (i - j) * (i - j);
}

__global__ void reduceKernel(float *blank, int level, int width) {
    int current_index = (blockIdx.x * blockDim.x + threadIdx.x);
    current_index *=  2 * level;
    int valid = current_index + level;
    if (valid < width*width) {
        blank[current_index] += blank[valid];
    }
    
}

void findDistance(float *image, int i_width, float *temp, int t_width, float *blank) {

    dim3 dim_blocks_per_grid(t_width/16, t_width/16);
    dim3 dim_threads_per_block(16, 16, 1);
    distanceKernel<<<dim_blocks_per_grid, dim_threads_per_block>>>(image, i_width, temp, t_width, blank);

    int threads = 512;
    int blocks = (t_width * t_width /threads) + 1;
    int level = 1;

    cudaThreadSynchronize();
    CUT_CHECK_ERROR("");
    while (level != t_width * t_width) { 
       
        dim3 dim_blocks_per_grid(blocks, 1);
        dim3 dim_threads_per_block(threads, 1, 1);

        reduceKernel<<<dim_blocks_per_grid, dim_threads_per_block>>>(blank, level, t_width);
        level *= 2;
        cudaThreadSynchronize();
        CUT_CHECK_ERROR("");

        if(blocks > 1) {
            blocks /= 2;
        } else {
            threads /= 2;
        }
    }
}

float calc_min_dist(float *image, int i_width, int i_height, float *temp, int t_width) {

    float min_dist = FLT_MAX;
    float current;
    float current_min = FLT_MAX;

    float *image2 = image;

    float *template_copy;
    CUDA_SAFE_CALL(cudaMalloc(&template_copy, t_width * t_width * sizeof(float)));

    float *blank;
    CUDA_SAFE_CALL(cudaMalloc(&blank, t_width * t_width * sizeof(float)));

    for(int y = 0; y <= i_height - t_width; y++) {
        for(int x = 0; x <= i_width - t_width; x++) {
            findDistance(image2 + x, i_width, temp, t_width, blank);
            CUDA_SAFE_CALL(cudaMemcpy(&current, blank, sizeof(float), cudaMemcpyDeviceToHost));
            if(current < current_min)
                current_min = current;
        }
        image2 += i_width;
    }
    image2 = image;

    if(current_min < min_dist)
    	min_dist = current_min;

    flip_vertical(temp, t_width); 
   
    current_min = FLT_MAX;
    for(int y = 0; y <= i_height - t_width; y++) {
        for(int x = 0; x <= i_width - t_width; x++) {
            findDistance(image2 + x, i_width, temp, t_width, blank);
            CUDA_SAFE_CALL(cudaMemcpy(&current, blank, sizeof(float), cudaMemcpyDeviceToHost));
            if(current < current_min)
                current_min = current;
        }
        image2 += i_width;
    }
    image2 = image;
    if(current_min < min_dist)
        min_dist = current_min;

    transpose(temp, template_copy, t_width); 

    current_min = FLT_MAX;
    for(int y = 0; y <= i_height - t_width; y++) {
        for(int x = 0; x <= i_width - t_width; x++) {
            findDistance(image2 + x, i_width, template_copy, t_width, blank);
            CUDA_SAFE_CALL(cudaMemcpy(&current, blank, sizeof(float), cudaMemcpyDeviceToHost));
            if(current < current_min)
                current_min = current;
        }
        image2 += i_width;
        
    }
    image2 = image;

    if(current_min < min_dist)
        min_dist = current_min;

    flip_vertical(template_copy, t_width);

    current_min = FLT_MAX;
    for(int y = 0; y <= i_height - t_width; y++) {
        for(int x = 0; x <= i_width - t_width; x++) {
            findDistance(image2 + x, i_width, template_copy, t_width, blank);
            CUDA_SAFE_CALL(cudaMemcpy(&current, blank, sizeof(float), cudaMemcpyDeviceToHost));
            if(current < current_min)
                current_min = current;
        }
        image2 += i_width;
        
    }
    image2 = image;
    if(current_min < min_dist)
        min_dist = current_min;

    transpose(template_copy, temp, t_width);

    current_min = FLT_MAX;
    for(int y = 0; y <= i_height - t_width; y++) {
        for(int x = 0; x <= i_width - t_width; x++) {
            findDistance(image2 + x, i_width, temp, t_width, blank);
            CUDA_SAFE_CALL(cudaMemcpy(&current, blank, sizeof(float), cudaMemcpyDeviceToHost));
            if(current < current_min)
                current_min = current;
        }
        image2 += i_width;
    }
    image2 = image;

    if(current_min < min_dist)
        min_dist = current_min;

    flip_vertical(temp, t_width);

    current_min = FLT_MAX;
    for(int y = 0; y <= i_height - t_width; y++) {
        for(int x = 0; x <= i_width - t_width; x++) {
            findDistance(image2 + x, i_width, temp, t_width, blank);
            CUDA_SAFE_CALL(cudaMemcpy(&current, blank, sizeof(float), cudaMemcpyDeviceToHost));
            if(current < current_min)
                current_min = current;
        }
        image2 += i_width;
        
    }
    image2 = image;
    if(current_min < min_dist)
        min_dist = current_min;

    transpose(temp, template_copy, t_width);

    current_min = FLT_MAX;
    for(int y = 0; y <= i_height - t_width; y++) {
        for(int x = 0; x <= i_width - t_width; x++) {
            findDistance(image2 + x, i_width, template_copy, t_width, blank);
            CUDA_SAFE_CALL(cudaMemcpy(&current, blank, sizeof(float), cudaMemcpyDeviceToHost));
            if(current < current_min)
                current_min = current;
        }
        image2 += i_width;
    }
    image2 = image;
    if(current_min < min_dist)
        min_dist = current_min;

    flip_vertical(template_copy, t_width); 
    current_min = FLT_MAX;
    for(int y = 0; y <= i_height - t_width; y++) {
        for(int x = 0; x <= i_width - t_width; x++) {
            findDistance(image2 + x, i_width, template_copy, t_width, blank);
            CUDA_SAFE_CALL(cudaMemcpy(&current, blank, sizeof(float), cudaMemcpyDeviceToHost));
            if(current < current_min)
                current_min = current;
        }
        image2 += i_width;
        
    }
    if(current_min < min_dist)
        min_dist = current_min;

    transpose(template_copy, temp, t_width);
    CUDA_SAFE_CALL(cudaFree(template_copy));
    CUDA_SAFE_CALL(cudaFree(blank));
    return min_dist;
}
