/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 18:45:27 by hcabel            #+#    #+#             */
/*   Updated: 2021/02/04 11:17:03 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

static int	load_kernel_file(t_kernel_gpu *gpu)
{
	int				fd;
	char			*line;
	unsigned int	size;

	if ((fd = open(KERNELSOURCEFILE, O_RDONLY)) == -1)
		return (KERNEL_SOURCE_LOAD_ERROR);
	line = 0;
	while (get_next_line(fd, &line) == 1)
	{
		size += ft_strlen(line) + 1;
		ft_memdel((void**)&line);
	}
	close(fd);
	if ((gpu->kernel_str = malloc(sizeof(char) * size)) == NULL)
		return (MALLOC_ERROR);
	if ((fd = open(KERNELSOURCEFILE, O_RDONLY)) == -1)
		return (KERNEL_SOURCE_LOAD_ERROR);
	while (get_next_line(fd, &line) == 1)
	{
		gpu->kernel_str = ft_strcat(gpu->kernel_str, line);
		gpu->kernel_str = ft_strcat(gpu->kernel_str, "\n");
		ft_memdel((void**)&line);
	}
	close(fd);
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
		if (!(log = (char*)malloc(log_size)))
			return (KERNEL_BUILD_ERROR);
		clGetProgramBuildInfo(*program, gpu->device_id, CL_PROGRAM_BUILD_LOG,
			log_size, log, NULL);
		ft_printf("{y}		%s{/}", log);
		ft_memdel((void**)&log);
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

int			init_kernel(t_info *info)
{
	int	code_error;

	if (info->gpuinitialised == 0 && ft_strlen(KERNELSOURCEFILE) > 0)
	{
		ft_printf("{g}	GPU\n{/}");
		code_error = kernel_initialisation(info);
		if (code_error != GOOD)
		{
			ft_memdel((void**)&info->kernel.kernel_str);
			ft_printf("{y}		%s\n{/}", error_to_str(code_error));
			if (is_fatal_error(code_error) == GOOD)
				return (code_error);
			ft_printf("{y}	CPU render mode only{/}\n");
			info->ongpu = 0;
			info->gpuinitialised = 0;
		}
		else
		{
			ft_printf("{g}	Ready\n{/}");
			info->gpuinitialised = 1;
		}
	}
	return (GOOD);
}
