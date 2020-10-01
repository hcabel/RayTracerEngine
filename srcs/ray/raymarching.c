/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raymarching.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 12:01:02 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/01 17:11:43 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static double	get_nearest_surface_distance(t_scene *scene, t_vector p)
{
	double			distance;
	double			tmp;
	unsigned int	i;

	distance = -1;
	i = 0;
	while (i < scene->shapes_amount)
	{
		tmp = vectorlength(vectorsubtract(p, scene->shapes[i].location)) - 10;
		if (distance == -1 || distance > tmp)
			distance = tmp;
		i++;
	}
	return (distance);
}

static double	trace_ray(t_scene *scene, t_vector start_location, t_vector dir)
{
	unsigned int	loop_index;
	double			depth;
	double			nearest_surface;

	loop_index = 0;
	depth = 0;
	while (loop_index < RAY_LOOP)
	{
		nearest_surface = get_nearest_surface_distance(scene,
			vectoradd(start_location, vectormult(dir, depth)));
		if (nearest_surface <= 0.001)
			return (depth + nearest_surface);
		depth += nearest_surface;
		loop_index++;
	}
	return (depth);
}

unsigned int	raymarching(t_scene *scene, t_vector dir)
{
	double	depth;
	int		r;
	int		g;
	int		b;
	int		a;

	r = 0;
	g = 0;
	b = 0;
	a = 255;
	depth = trace_ray(scene, scene->cam.location, dir);
	depth = fminf(VIEW_DISTANCE, fmaxf(0, depth));
	r = (double)depth / VIEW_DISTANCE * -255;
	g = (double)depth / VIEW_DISTANCE * -255;
	b = (double)depth / VIEW_DISTANCE * -255;
	a = 255;
	return ((r << 24) + (g << 16) + (b << 8) + a);
}
