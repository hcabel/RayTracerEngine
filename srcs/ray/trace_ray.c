/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 11:42:28 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/10 13:05:25 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static double	get_nearest_surface_distance(t_scene *scene, t_vector p,
					t_object **nearest_obj)
{
	double			distance;
	double			tmp;
	unsigned int	i;

	distance = -1;
	i = 0;
	while (i < scene->shapes_amount)
	{
		tmp = scene->shapes[i].sdf(vector_subtract(p, scene->shapes[i].location),
			scene->shapes[i].scale);
		if (distance == -1 || distance > tmp)
		{
			*nearest_obj = &scene->shapes[i];
			distance = tmp;
		}
		i++;
	}
	return (distance);
}

t_ray_hit	trace_ray(t_scene *scene, t_vector start_location,
					t_vector dir, float max_distance)
{
	t_ray_hit		hitinfos;
	unsigned int	loop_index;
	double			depth;
	double			nearest_surface;

	loop_index = 0;
	depth = 0;
	hitinfos.hit_object = &scene->shapes[0];
	while (loop_index < RAY_LOOP && depth < max_distance)
	{
		nearest_surface = get_nearest_surface_distance(scene,
			vector_add(start_location, vector_mult(dir, depth)),
			&hitinfos.hit_object);
		if (nearest_surface <= RAY_PRECIS)
		{
			hitinfos.hit.bool = 1;
			hitinfos.distance = depth;
			hitinfos.recursion = loop_index;
			hitinfos.location = vector_add(start_location,
				vector_mult(dir, depth));
			return (hitinfos);
		}
		depth += nearest_surface;
		loop_index++;
	}
	hitinfos.hit.bool = (depth < max_distance ? 1 : 0);
	hitinfos.distance = depth;
	hitinfos.recursion = loop_index;
	hitinfos.location = vector_add(start_location, vector_mult(dir, depth));
	return (hitinfos);
}
