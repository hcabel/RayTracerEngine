/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 11:03:26 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/11 19:50:14 by hcabel           ###   ########.fr       */
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

float			calcSoftshadow(t_vector p, t_vector dir, t_scene *scene)
{
	float			result;
	float			depth;
	float			closest_surface;
	float			tmp;
	unsigned int	i;

	result = 1;
	depth = RAY_PRECIS;
	i = 0;
	while (i < RAY_LOOP && depth < VIEW_DISTANCE)
	{
		closest_surface = get_nearest_surface_distance(scene, vector_add(p,
			vector_mult(dir, depth)), NULL);
		tmp = fmaxf(0, fminf(1, 8 * closest_surface / depth));
		result = fminf( result, tmp * tmp * (3.0 - 2.0 * tmp) );
		depth += fmaxf(0.02, fminf(0.2, closest_surface));
		if (result < 0.0001)
			break ;
		i++;
	}
	return (fmaxf(0, fminf(1, result)));
}

float	get_light_intensity(t_scene *scene, t_vector hit_location,
			t_object *hit_obj, t_vector olddir, t_light *lights)
{
	float		intensity;
	float		diffuse;
	float		specular;
	t_vector	hal;
	t_vector	dir;
	t_vector	normal;

	int	i;
	i = 0;
	while (lights[i].intensity)
		i++;
	int j;
	j = 0;
	intensity = 0;
	while (j < i)
	{
		normal = get_normal_map(hit_location, scene, hit_obj);
		dir = vector_normalize(vector_subtract(lights[j].location,
			hit_location));
		hal = vector_normalize(vector_subtract(dir, olddir));
		diffuse = fmaxf(0, fminf(1, vector_dot(normal, dir)))
			* calcSoftshadow(hit_location, dir, scene);
		specular = (powf(fmaxf(0, fminf(1, vector_dot(normal, hal))), 16) * diffuse)
			* 0.04 + 0.96 * powf(fmaxf(0, fminf(1, 1 - vector_dot(hal, dir))), 5);
		intensity += (10 * specular + diffuse / 1.7) / i;
		j++;
	}
	return (fmaxf(0, fminf(1, intensity)));
}
