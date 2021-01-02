/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gpu.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 12:27:10 by hcabel            #+#    #+#             */
/*   Updated: 2021/01/02 16:36:27 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	convert_shapes_to_kernel_list(t_object *list, unsigned int amount,
				t_kernel_shape **newlist)
{
	unsigned int	index;

	if (!(*newlist = (t_kernel_shape*)malloc(sizeof(t_kernel_shape) * amount)))
		return (MALLOC_ERROR);
	index = 0;
	while (index < amount)
	{
		(*newlist)[index].location = list[index].location;
		(*newlist)[index].rotation = list[index].rotation;
		(*newlist)[index].scale = list[index].scale;
		(*newlist)[index].color = list[index].color;
		(*newlist)[index].sdf_index = list[index].sdf_index;
		(*newlist)[index].istarget = list[index].istarget;
		index++;
	}
	return (GOOD);
}

static int	convert_scene_to_kernel_scene(t_kernel_args *kernel_args,
				t_info *info, unsigned int numpixel)
{
	kernel_args->scene.cam_location = info->scene.cam.location;
	kernel_args->scene.cam_rotation = info->scene.cam.rotation;
	kernel_args->scene.viewmode = info->scene.cam.viewmode;
	kernel_args->scene.shapes_num = info->scene.shapes_amount;
	kernel_args->scene.img_x = info->screen.viewport.image.x;
	kernel_args->scene.img_y = info->screen.viewport.image.y;
	kernel_args->scene.img_w = info->screen.viewport.image.w;
	kernel_args->scene.img_h = info->screen.viewport.image.h;
	if (convert_shapes_to_kernel_list(info->scene.shapes,
		info->scene.shapes_amount, &kernel_args->shapes) != GOOD)
		return (MALLOC_ERROR);
	return (GOOD);
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

	kernel->kernel = clCreateKernel(kernel->program,
		"gpu_raymarching", &ret);

	clSetKernelArg(kernel->kernel, 0, sizeof(cl_mem),
		(void*)&kernel->pxl_color);
	clSetKernelArg(kernel->kernel, 1, sizeof(cl_mem),
		(void*)&kernel->shapes);
	clSetKernelArg(kernel->kernel, 2, sizeof(kernel_args->scene),
		(void*)&kernel_args->scene);

	return (GOOD);
}

static int	execute_kernel(t_kernel_gpu *gpu, unsigned int numpixel)
{
	cl_int	ret;
	size_t	global_item_size;
	//size_t	local_item_size;
	int		i;

	global_item_size = numpixel;
	/*local_item_size = 32;
	i = 2;
	while (i < numpixel)
	{
		if (numpixel % i == 0)		// TODO
		{
			local_item_size = i;
		}
		i++;
	}
	ft_printf("local_item_size = %u    %d\n", local_item_size, numpixel / local_item_size);
	if (local_item_size <= 0)
		return (KERNEL_ITEM_SIZE_ERROR);*/
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

int			calculate_image_with_cg(t_info *info)
{
	t_kernel_args	kernel_arg;
	unsigned int	numpixel;
	unsigned int	index;
	t_vector2d		coordinates;
	int				code_error;

	numpixel = info->screen.viewport.image.w * info->screen.viewport.image.h;
	if (convert_scene_to_kernel_scene(&kernel_arg, info, numpixel) != GOOD)
		return (MALLOC_ERROR);
	create_kernel(&info->kernel, numpixel, &kernel_arg);

	if ((code_error = execute_kernel(&info->kernel, numpixel)) != GOOD)
		return (code_error);

	info->kernel.result[numpixel - 1] = 0xFFFFFFFF;

	index = 0;
	while (index < numpixel)
	{
		coordinates = get_pixel_coordinates(index,
			info->screen.viewport.image.w);
		((unsigned int*)info->screen.viewport.pixels)[(int)coordinates.x +
			((int)coordinates.y * WIN_WIDTH)] = info->kernel.result[index];
		index++;
	}
	clReleaseMemObject(info->kernel.pxl_color);
	clReleaseKernel(info->kernel.kernel);
	ft_memdel((void**)&info->kernel.result);
	ft_memdel((void**)&kernel_arg.shapes);
	return (GOOD);
}
