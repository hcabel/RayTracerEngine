/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gpu.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 12:27:10 by hcabel            #+#    #+#             */
/*   Updated: 2021/01/29 17:11:31 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	put_args_into_kernel_function(t_kernel_gpu *kernel,
	t_kernel_args *kernel_args)
{
	clSetKernelArg(kernel->kernel, 0, sizeof(cl_mem),
		(void*)&kernel->pxl_color);
	clSetKernelArg(kernel->kernel, 1, sizeof(cl_mem),
		(void*)&kernel->shapes);
	clSetKernelArg(kernel->kernel, 2, sizeof(cl_mem),
		(void*)&kernel->lights);
	clSetKernelArg(kernel->kernel, 3, sizeof(kernel_args->scene),
		(void*)&kernel_args->scene);
}

static int	create_kernel(t_kernel_gpu *kernel, unsigned int numpixel,
				t_kernel_args *kernel_args)
{
	cl_int	ret;

	kernel->pxl_color = clCreateBuffer(kernel->context,
		CL_MEM_WRITE_ONLY, sizeof(unsigned int) * numpixel, NULL, &ret);
	kernel->shapes = clCreateBuffer(kernel->context,
		CL_MEM_READ_ONLY, sizeof(t_kernel_shape)
		* kernel_args->scene.shapes_num, NULL, &ret);
	ret = clEnqueueWriteBuffer(kernel->command_queue, kernel->shapes,
		CL_TRUE, 0, sizeof(t_kernel_shape) * kernel_args->scene.shapes_num,
		kernel_args->shapes, 0, NULL, NULL);
	kernel->lights = clCreateBuffer(kernel->context,
		CL_MEM_READ_ONLY, sizeof(t_kernel_light)
		* kernel_args->scene.lights_num, NULL, &ret);
	ret = clEnqueueWriteBuffer(kernel->command_queue, kernel->lights,
		CL_TRUE, 0, sizeof(t_kernel_light) * kernel_args->scene.lights_num,
		kernel_args->lights, 0, NULL, NULL);
	kernel->kernel = clCreateKernel(kernel->program,
		"gpu_raymarching", &ret);
	put_args_into_kernel_function(kernel, kernel_args);
	return (GOOD);
}

static int	execute_kernel(t_kernel_gpu *gpu, unsigned int numpixel)
{
	cl_int	ret;
	size_t	global_item_size;
	int		i;

	global_item_size = numpixel;
	if (clEnqueueNDRangeKernel(gpu->command_queue, gpu->kernel, 1, NULL,
			&global_item_size, NULL, 0, NULL, NULL) != CL_SUCCESS)
		return (KERNEL_ITEM_SIZE_ERROR);
	if (!(gpu->result = malloc(sizeof(unsigned int) * numpixel)))
		return (MALLOC_ERROR);
	ret = clEnqueueReadBuffer(gpu->command_queue, gpu->pxl_color, CL_TRUE, 0,
		sizeof(unsigned int) * numpixel, gpu->result, 0, NULL, NULL);
	if (ret != CL_SUCCESS)
		return (KERNEL_ENQUEUE_ERROR);
	return (GOOD);
}

static void	put_pixel_into_texture(unsigned int numpixel, t_info *info)
{
	unsigned int	index;
	t_vector2d		coordinates;

	index = 0;
	while (index < numpixel)
	{
		coordinates = get_pixel_coordinates(index,
			info->screen.viewport.image.w);
		((unsigned int*)info->screen.viewport.pixels)[(int)coordinates.x +
			((int)coordinates.y * info->screen.area.w)] =
			info->kernel.result[index];
		index++;
	}
}

int			calculate_image_with_cg(t_info *info)
{
	t_kernel_args	kernel_arg;
	unsigned int	numpixel;
	int				code_error;

	numpixel = info->screen.viewport.image.w * info->screen.viewport.image.h;
	if (convert_scene_to_kernel_scene(&kernel_arg, info, numpixel) != GOOD)
		return (MALLOC_ERROR);
	create_kernel(&info->kernel, numpixel, &kernel_arg);
	if ((code_error = execute_kernel(&info->kernel, numpixel)) != GOOD)
		return (code_error);
	put_pixel_into_texture(numpixel, info);
	clReleaseMemObject(info->kernel.pxl_color);
	clReleaseKernel(info->kernel.kernel);
	ft_memdel((void**)&info->kernel.result);
	ft_memdel((void**)&kernel_arg.shapes);
	ft_memdel((void**)&kernel_arg.lights);
	return (GOOD);
}
