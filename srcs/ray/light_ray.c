/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 11:03:26 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/11 16:32:48 by hcabel           ###   ########.fr       */
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
			if (nearest_obj != NULL && *nearest_obj != NULL)
				*nearest_obj = &scene->shapes[i];
			distance = tmp;
		}
		i++;
	}
	return (distance);
}

float			calcSoftshadow( t_vector p, t_vector dir, float mint,
					float tmax, t_scene *scene )
{

	float			result;
	float			depth;
	float			closest_surface;
	float			s;
	unsigned int	i;

	result = 1.0;
	depth = mint;
	i = 0;
	while (i < 24)
	{
		closest_surface = get_nearest_surface_distance(scene, vector_add(p,
			vector_mult(dir, depth)), NULL);
		s = fmaxf(0, fminf(1, 8.0 * closest_surface / depth));
		result = fminf(result, s * s * (3.0 - 2.0 * s));
		depth += fmaxf(0.02, fminf(0.2, closest_surface));
		if (result < 0.004 || depth > tmax)
			break;
		i++;
	}
	return (fmaxf(0, fminf(1, result)));
}

float	get_light_intensity(t_scene *scene, t_vector hit_location,
			t_object *hit_obj, t_vector olddir)
{
	float		intensity;
	float		diffuse;
	float		specular;

	t_vector	hal;

	t_vector	dir;
	t_ray_hit	ray;
	t_vector	normal;
	t_vector	lightstart;
	t_vector	light_local_location;

	normal = get_normal_map(hit_location, scene, hit_obj);

	dir = vector_normalize(vector_subtract(scene->lights[0].location,
		hit_location));
	hal = vector_normalize(vector_subtract(dir, olddir));
	diffuse = fmaxf(0, fminf(1, vector_dot(normal, dir)));
		diffuse *= calcSoftshadow(hit_location, dir, 0.02, VIEW_DISTANCE, scene);
	specular = powf(fmaxf(0, fminf(1, vector_dot(normal, hal))), 16);
	specular *= diffuse;
	specular *= 0.04 + 0.96 * powf(fmaxf(0, fminf(1, 1 - vector_dot(hal, dir))), 5);
	intensity = 10 * specular + diffuse / 1.6;
	return (fmaxf(0, fminf(1, intensity)));
}
