/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raymarching_thread.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 18:12:01 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/05 18:44:30 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static double	deg2rad(double degrees)
{
	return (degrees * M_PI / 180);
}

static t_vector	multVecMatrix(t_vector src, t_vector2d f)
{
	t_matrix44f	rot_x;
	t_matrix44f	rot_y;
	t_matrix44f	r;
	t_vector	dst;
	float		a;
	float		b;
	float		c;
	float		w;

	rot_x = new_matrix44f(new_vector4d(1, 0, 0, 0),
		new_vector4d(0, cos(f.x), -sin(f.x), 0),
		new_vector4d(0, sin(f.x), cos(f.x), 0), new_vector4d(0, 0, 0, 1));
	rot_y = new_matrix44f(new_vector4d(cos(f.y), 0, -sin(f.y), 0),
		new_vector4d(0, 1, 0, 0),
		new_vector4d(sin(f.y), 0, cos(f.y), 0), new_vector4d(0, 0, 0, 1));
	r = matrix_mult(rot_x, rot_y);

	a = src.x * rot_y.m[0][0] + src.y * rot_y.m[1][0] + src.z * rot_y.m[2][0] + rot_y.m[3][0];
	b = src.x * rot_y.m[0][1] + src.y * rot_y.m[1][1] + src.z * rot_y.m[2][1] + rot_y.m[3][1];
	c = src.x * rot_y.m[0][2] + src.y * rot_y.m[1][2] + src.z * rot_y.m[2][2] + rot_y.m[3][2];
	w = src.x * rot_y.m[0][3] + src.y * rot_y.m[1][3] + src.z * rot_y.m[2][3] + rot_y.m[3][3];

	dst.x = a / w;
	dst.y = b / w;
	dst.z = c / w;

	a = dst.x * rot_x.m[0][0] + dst.y * rot_x.m[1][0] + dst.z * rot_x.m[2][0] + rot_x.m[3][0];
	b = dst.x * rot_x.m[0][1] + dst.y * rot_x.m[1][1] + dst.z * rot_x.m[2][1] + rot_x.m[3][1];
	c = dst.x * rot_x.m[0][2] + dst.y * rot_x.m[1][2] + dst.z * rot_x.m[2][2] + rot_x.m[3][2];
	w = dst.x * rot_x.m[0][3] + dst.y * rot_x.m[1][3] + dst.z * rot_x.m[2][3] + rot_x.m[3][3];

	dst.x = a / w;
	dst.y = b / w;
	dst.z = c / w;
	return (dst);
}

static t_vector		get_ray_direction_from_coordinate(t_vector2d coordinates,
						t_cam *cam, unsigned int wid, unsigned int height)
{
	t_vector	dir;
	t_vector2d	pixel;
	float		scale = tan(deg2rad(90 * 0.5));
	float		imageAspectRatio = wid / (float)height;

	pixel.x = (2 * ((coordinates.x + 0.5) / wid) - 1) * scale * imageAspectRatio;
	pixel.y = (1 - 2 * ((coordinates.y + 0.5) / height)) * scale;

	dir = multVecMatrix(new_vector(pixel.x, pixel.y, 1), cam->rotation);
	return (vector_normalize(dir));
}

static t_vector2d	get_pixel_coordinates(unsigned int i, unsigned int width)
{
	t_vector2d	result;

	result.x = i % width;
	result.y = i / width;
	return (result);
}

void				*thread_calculs_functions(void *p)
{
	t_thread		*thread_info;
	t_scene			*scene;
	t_screen		*screen;
	t_vector2d		co;
	unsigned int	i;

	thread_info = p;
	scene = thread_info->scene;
	screen = thread_info->screen;
	i = thread_info->start_index;
	while (i < (unsigned int)screen->viewport_image.w *
		(unsigned int)screen->viewport_image.h)
	{
		co = get_pixel_coordinates(i, screen->viewport_image.w);
		((unsigned int*)screen->pixels)[(int)co.x + ((int)co.y * WIN_WIDTH)] =
			raymarching(scene, get_ray_direction_from_coordinate(co, &scene->cam,
			screen->viewport_image.w, screen->viewport_image.h));
		i += RAYMARCHING_THREAD;
	}
	pthread_exit(NULL);
	return ((void*)0);
}
