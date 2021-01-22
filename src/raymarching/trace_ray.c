/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 11:42:28 by hcabel            #+#    #+#             */
/*   Updated: 2021/01/03 18:00:06 by hcabel           ###   ########.fr       */
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
		tmp = scene->sdf_list[scene->shapes[i].sdf_index]
			(vector_subtract(p, scene->shapes[i].location),
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

static t_ray_hit	ray_return(float depth, unsigned int loop_index,
	t_object *obj, int b, t_vector loc)
{
	t_ray_hit	hitinfos;

	hitinfos.hit = b;
	hitinfos.distance = depth;
	hitinfos.recursion = loop_index;
	hitinfos.location = loc;
	hitinfos.hit_object = obj;
	return (hitinfos);
}

t_ray_hit			trace_ray(t_scene *scene, t_vector start_location,
						t_vector dir, float max_distance)
{
	t_object		*obj;
	unsigned int	loop_index;
	double			depth;
	double			nearest_surface;

	loop_index = 0;
	depth = 0;
	while (loop_index < RAY_LOOP && depth < max_distance)
	{
		nearest_surface = get_nearest_surface_distance(scene,
			vector_add(start_location, vector_mult(dir, depth)), &obj);
		if (nearest_surface < RAY_PRECIS)
			return (ray_return(depth, loop_index, obj, 1,
				vector_add(start_location, vector_mult(dir, depth))));
		depth += nearest_surface;
		loop_index++;
	}
	return (ray_return(depth, loop_index, obj, (depth < max_distance ? 1 : 0),
		vector_add(start_location, vector_mult(dir, depth))));
}
