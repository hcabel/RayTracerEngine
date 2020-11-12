/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_kernel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 12:43:45 by hcabel            #+#    #+#             */
/*   Updated: 2020/11/11 10:58:17 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <stdio.h>

static int	load_kernel_file(t_kernel_gpu *gpu)
{
	FILE	*kernel_fd;

	kernel_fd = fopen("srcs/ray/kernel_raymarching.cl", "r");
	if (!kernel_fd)
		return (KERNEL_SOURCE_LOAD_ERROR);
	gpu->kernel_str = (char*)malloc(MAX_SOURCE_SIZE);
	gpu->kernel_size = fread(gpu->kernel_str, 1, MAX_SOURCE_SIZE, kernel_fd);
	fclose(kernel_fd);
	return (GOOD);
}

static int	get_gpu(t_kernel_gpu *gpu)
{
	cl_int			ret;
	cl_uint			ret_num_devices;
	cl_platform_id	platform_id;
	cl_uint			ret_num_platforms;

	ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
	if (ret != CL_SUCCESS || ret_num_platforms == 0)
		return (KERNEL_PLATFORM_ERROR);
	ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT, 1,
		&gpu->device_id, &ret_num_devices);
	if (ret != CL_SUCCESS || ret_num_devices == 0)
		return (KERNEL_PLATFORM_ERROR);
	gpu->context = clCreateContext(NULL, 1, &gpu->device_id, NULL, NULL, &ret);
	if (ret != CL_SUCCESS)
		return (KERNEL_CONTEXT_ERROR);
	gpu->command_queue = clCreateCommandQueue(gpu->context, gpu->device_id, 0,
		&ret);
	return (ret != CL_SUCCESS ? KERNEL_COMMANDQUEUE_ERROR : GOOD);
}

static int	build_kernel(t_kernel_gpu *gpu, cl_program *program)
{
	size_t	log_size;
	char	*log;
	cl_int	ret;

	*program = clCreateProgramWithSource(gpu->context, 1,
		(const char**)&gpu->kernel_str, (const size_t*)&gpu->kernel_size,
		&ret);
	ret = clBuildProgram(*program, 1, &gpu->device_id,
		"-I include -I /usr/include/x86_64-linux-gnu/ -I /usr/include/linux",
		NULL, NULL);
	if (ret != CL_SUCCESS)
	{
		clGetProgramBuildInfo(*program, gpu->device_id, CL_PROGRAM_BUILD_LOG,
			0, NULL, &log_size);
		if (!(log = (char *) malloc(log_size)))
			return (KERNEL_BUILD_ERROR);
		clGetProgramBuildInfo(*program, gpu->device_id, CL_PROGRAM_BUILD_LOG,
			log_size, log, NULL);
		ft_printf("{y}%s{/}", log);
		free(log);
		return (KERNEL_BUILD_ERROR);
	}
	return (GOOD);
}

static int	kernel_initialisation(t_info *info)
{
	int	code;

	if ((code = load_kernel_file(&info->kernel)) != GOOD)
		return (code);
	if ((code = get_gpu(&info->kernel)) != GOOD)
		return (code);
	if ((code = build_kernel(&info->kernel, &info->kernel.program)) != GOOD)
		return (code);
	return (GOOD);
}

int		init_kernel(t_info *info)
{
	int	ret;

	ret = kernel_initialisation(info);
	if (ret != GOOD)
	{
		if (ret == KERNEL_SOURCE_LOAD_ERROR)
			ft_printf("{r}Error GPU : source file not found\n{/}");
		else if (ret == KERNEL_PLATFORM_ERROR)
			ft_printf("{r}Error GPU : No plateform found\n{/}");
		else if (ret == KERNEL_CONTEXT_ERROR)
			ft_printf("{r}Error GPU : Context error\n{/}");
		else if (ret == KERNEL_COMMANDQUEUE_ERROR)
			ft_printf("{r}Error GPU : Commandequeue error\n{/}");
		else if (ret == KERNEL_BUFFER_ERROR)
			ft_printf("{r}Error GPU : Buffer creation failed\n{/}");
		else if (ret == KERNEL_BUILD_ERROR)
			ft_printf("{r}Error GPU : Kenel build failed\n{/}");
		else if (ret == KERNEL_CREATION_ERROR)
			ft_printf("{r}Error GPU : Kernel creation failed\n{/}");
		else if (ret == KERNER_ENQUEUE_ERROR)
			ft_printf("{r}Error GPU : Enqueue error\n{/}");
		return (ret);
	}
	else
		ft_printf("{g}Kernel : Gpu Initialised\n{/}");
	return (GOOD);
}
