/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raymarching_simplified.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 14:09:21 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/10 18:32:04 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_ray_hit	ray_return(float depth, unsigned int loop_index,
	t_object *obj, int b, t_vector loc)
{
	t_ray_hit	hitinfos;

	hitinfos.hit.bool = b;
	hitinfos.distance = depth;
	hitinfos.recursion = loop_index;
	hitinfos.location = loc;
	hitinfos.hit_object = obj;
	return (hitinfos);
}

t_ray_hit		trace_ray_simplified(t_vector start, t_vector dir, t_object *obj)
{
	unsigned int	iteration;
	float			depth;
	float			closest_surface;

	iteration = 0;
	depth = 0;
	while (iteration < 20 && depth < 10)
	{
		closest_surface = obj->sdf(vector_subtract(new_vector(0, 0, 0),
			vector_add(start, vector_mult(dir, depth))), new_vector(1, 1, 1)); // CAN BE NORMALIZE
		if (closest_surface < 0.001)
			return (ray_return(depth, iteration, obj, 1,
				vector_add(start, vector_mult(dir, depth))));
		depth += closest_surface;
		iteration++;
	}
	return (ray_return(depth, iteration, obj, (depth < 10 ? 1 : 0),
		vector_add(start, vector_mult(dir, depth))));
}
