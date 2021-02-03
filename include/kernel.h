/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 11:16:00 by hcabel            #+#    #+#             */
/*   Updated: 2021/01/29 14:43:24 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KERNEL_H
# define KERNEL_H

# include "mathematical.h"
# include <CL/cl.h>

typedef struct			s_kernel_gpu
{
	cl_kernel			kernel;
	char				*kernel_str;
	size_t				kernel_size;
	cl_device_id		device_id;
	cl_context			context;
	cl_command_queue	command_queue;
	cl_mem				pxl_color;
	cl_mem				shapes;
	cl_mem				lights;
	cl_mem				scene;
	unsigned int		*result;
	cl_program			program;
}						t_kernel_gpu;

/*
**	Kernel structure
*/

typedef struct			s_kernel_shape
{
	t_vector			location;
	t_vector2d			rotation;
	t_vector			scale;
	t_vector			color;
	unsigned int		sdf_index;
	int					istarget;
}						t_kernel_shape;

typedef struct			s_kernel_light
{
	t_vector			location;
	t_vector2d			rotation;
	float				intensity;
}						t_kernel_light;

typedef struct			s_kernel_scene
{
	int					shapes_num;
	int					lights_num;
	t_vector			cam_location;
	t_vector2d			cam_rotation;
	int					viewmode;
	int					img_x;
	int					img_y;
	int					img_w;
	int					img_h;
}						t_kernel_scene;

typedef struct			s_kernel_args
{
	t_kernel_shape		*shapes;
	t_kernel_light		*lights;
	t_kernel_scene		scene;
}						t_kernel_args;

#endif
