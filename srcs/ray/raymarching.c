/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raymarching.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 12:01:02 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/05 18:43:37 by hcabel           ###   ########.fr       */
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

static float	get_light_intensity(t_scene *scene, t_vector hit_location,
					t_object *hit_obj)
{
	float			intensity;
	t_vector		dir;
	t_ray_result	ray_outuput;
	t_vector		normal;
	t_vector		lightstart;

	dir = vector_normalize(vector_subtract(scene->lights[0].location,
		hit_location));
	normal = get_normal_map(hit_location, scene, hit_obj);
	lightstart = vector_add(hit_location,
		vector_mult(vector_mult(normal, RAY_PRECIS), 4));
	ray_outuput = trace_ray(scene, lightstart, dir,
		vector_length(vector_subtract(lightstart, scene->lights[0].location)));
	intensity = vector_dot(vector_normalize(vector_subtract(
		scene->lights[0].location, hit_location)), normal);
	intensity = fminf(1, fmaxf(0, intensity));

	//intensity = fminf(1, fmaxf(0, (intensity * -1 + 1) / 2 /
	//	(100 / scene->lights[0].intensity)));
	if (ray_outuput.hit.bool == 1)
		intensity *= 0.3;
	return (intensity);
}

unsigned int	raymarching(t_scene *scene, t_vector dir)
{
	double			depth;
	t_ray_result	ray_outuput;
	unsigned int	pixel_color;
	float			intensity;
	t_vector		color;

	pixel_color = 0;
	ray_outuput = trace_ray(scene, scene->cam.location, dir, VIEW_DISTANCE);
	ray_outuput.distance = fminf(VIEW_DISTANCE, fmaxf(0, ray_outuput.distance));
	if (ray_outuput.hit.bool)
	{
		intensity = get_light_intensity(scene, ray_outuput.location,
			ray_outuput.hit_object);
		//intensity *= fabs(fmaxf(ray_outuput.distance / VIEW_DISTANCE, 0.25) - 1)
		//	* (1 / (1 - 0.25));
		color.x = (ray_outuput.hit_object->color.x * intensity);
		color.y = (ray_outuput.hit_object->color.x * intensity);
		color.z = (ray_outuput.hit_object->color.z * intensity);

		t_vector	normal = normal_map_to_rgb(get_normal_map(ray_outuput.location, scene, ray_outuput.hit_object));
		color.x = normal.x;
		color.y = normal.y;
		color.z = normal.z;

		pixel_color = ((int)color.x << 24) + ((int)color.y << 16)
			+ ((int)color.z << 8) + 0xFF;
	}
	return (pixel_color);
}
