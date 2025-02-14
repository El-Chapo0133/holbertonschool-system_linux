/*
 * ===========================================================================
 *
 *       Filename:  multithreading.h
 *
 *    Description: multithreading header file
 *
 *        Version:  1.0
 *        Created:  10.01.2025 08:57:44
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Loris Lévêque (), 9601@holbertonstudents.com
 *   Organization:  Holberton
 *
 * ===========================================================================
 */

#ifndef H_MULTITHREADING
#define H_MULTITHREADING

#include "list.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

/**
 * struct pixel_s - RGB pixel
 *
 * @r: Red component
 * @g: Green component
 * @b: Blue component
 */
typedef struct pixel_s
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
} pixel_t;

/**
 * struct img_s - Image
 * @w: image width
 * @h: image height
 * @pixels: array of pixels
 */
typedef struct img_s
{
	size_t w;
	size_t h;
	pixel_t pixels;
} img_t;

/**
 * struct kernel_s - convolution kernel
 * @size: matrix size
 * @matrix: kernel matrix 
 */
typedef struct kernel_s
{
	size_t size;
	float **matrix;
} kernel_t;

/**
 * struct blur_porion_s - infos to blur an image
 * @img: source image
 * @img_blur: dest image
 * @x: x position of the image
 * @y: y position of the image
 * @w: width of the portion
 * @h: height of the portion
 * @kernel: kernel to use
 */
typedef struct blur_portion_s
{
	img_t const *img;
	img_t *img_blur;
	size_t x;
	size_t y;
	size_t w;
	size_t h;
	kernel_t const *kernel;
} blur_portion_t;

void *thread_entry(void *arg);
int tprintf(char const *format, ...);
void blur_portion(blur_portion_t const *portion);
pixel_t **convert_array(const img_t *img);
void blur_pixel(const blur_portion_t *portion, const pixel_t **pixels,
				const size_t x, const size_t y, const size_t px);
void blur_image(img_t *img_blur, img_t const *img, kernel_t const *kernel);
int tprintf(char const *format, ...);
list_t *prime_factors(char const *s);
task_t *create_task(task_entry_t entry, void *param);

#endif
