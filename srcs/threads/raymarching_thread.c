/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raymarching_thread.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 18:12:01 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/03 12:59:29 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static double	deg2rad(double degrees)
{
	return (degrees * 4.0 * atan (1.0) / 180.0);
}

static t_vector	rotate(t_vector p, t_cam *cam)
{
	t_vector	v;
	double		x;
	double		y;
	double		z;

	x = p.x;
	z = p.z;
	v.x = cos(cam->rotation.y) * x + sin(cam->rotation.y) * z;
	v.z = -sin(cam->rotation.y) * x + cos(cam->rotation.y) * z;
	y = p.y;
	z = v.z;
	v.y = cos(cam->rotation.x) * y - sin(cam->rotation.x) * z;
	v.z = sin(cam->rotation.x) * y + cos(cam->rotation.x) * z;
	return (v);
}

static t_vector		get_ray_direction_from_coordinate(t_vector2d coordinates,
						t_cam *cam, unsigned int wid, unsigned int height)
{
	t_vector	dir;

	float scale = tan(deg2rad(90 * 0.5));
	float	imageAspectRatio = wid / (float)height;

	float x = (2 * (coordinates.x + 0.5) / (float)wid - 1) * imageAspectRatio * scale;
	float y = (1 - 2 * (coordinates.y + 0.5) / (float)height) * scale;

	t_vector t = newvector(x, y, 1);

	/*dir.x = t.x * mat[0][0] + t.y * mat[1][0] + t.z * mat[2][0] + mat[3][0];
	dir.y = t.x * mat[0][1] + t.y * mat[1][1] + t.z * mat[2][1] + mat[3][1];
	dir.z = t.x * mat[0][2] + t.y * mat[1][2] + t.z * mat[2][2] + mat[3][2];*/

	dir = rotate(t, cam);
	dir = vectornormalize(dir);

	return (dir);
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
