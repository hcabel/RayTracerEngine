/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raymarching.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 12:01:02 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/06 15:02:47 by hcabel           ###   ########.fr       */
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
	t_vector		light_local_location;

	normal = get_normal_map(hit_location, scene, hit_obj);

	lightstart = vector_add(hit_location, vector_mult(normal, -RAY_PRECIS));
	light_local_location = vector_subtract(scene->lights[0].location,
		lightstart);
	dir = vector_normalize(light_local_location);
	ray_outuput = trace_ray(scene, lightstart, dir,
		vector_length(light_local_location));
	intensity = vector_dot(vector_normalize(vector_subtract(
		scene->lights[0].location, hit_location)), normal);
	intensity = fminf(1, fmaxf(0, (intensity * -1 + 1) / 2 /
		(100 / scene->lights[0].intensity)));
	if (ray_outuput.hit.bool == 1)
		intensity *= 0.3;
	return (intensity);
}

static int		check_for_hidden_obj(t_scene *scene, t_vector dir, float prec)
{
	t_vector tmp;

	tmp = vector_normalize(vector_subtract(scene->lights[0].location,
		scene->cam.location));
	if (tmp.x + prec >= dir.x && tmp.x - prec <= dir.x
		&& tmp.y + prec >= dir.y && tmp.y - prec <= dir.y
		&& tmp.z + prec >= dir.z && tmp.z - prec <= dir.z)
		return (1);
	return (0);
}

unsigned int	raymarching(t_scene *scene, t_vector dir)
{
	double			depth;
	t_ray_result	ray_outuput;
	unsigned int	pixel_color;
	float			intensity;
	t_vector		color;

	if (check_for_hidden_obj(scene, dir, .01))
	{
		pixel_color = ((int)255 << 24) + ((int)0 << 16)
			+ ((int)0 << 8) + 0xFF;
		return (pixel_color);
	}
	pixel_color = 0;
	ray_outuput = trace_ray(scene, scene->cam.location, dir, VIEW_DISTANCE);
	ray_outuput.distance = fminf(VIEW_DISTANCE, fmaxf(0, ray_outuput.distance));
	color.x = 0;
	color.y = 0;
	color.z = 0;
	if (ray_outuput.hit.bool)
	{
		intensity = get_light_intensity(scene, ray_outuput.location,
			ray_outuput.hit_object);
		//intensity *= fabs(fmaxf(ray_outuput.distance / VIEW_DISTANCE, 0.25) - 1)
		//	* (1 / (1 - 0.25));
		color.x = (ray_outuput.hit_object->color.x * intensity);
		color.y = (ray_outuput.hit_object->color.y * intensity);
		color.z = (ray_outuput.hit_object->color.z * intensity);

		/*t_vector	normal = normal_map_to_rgb(get_normal_map(ray_outuput.location, scene, ray_outuput.hit_object));
		color.x = normal.x;
		color.y = normal.y;
		color.z = normal.z;*/
	}
	/*color.x = ray_outuput.recursion / (float)RAY_LOOP * (float)255;
	color.y = ray_outuput.recursion / (float)RAY_LOOP * (float)255;
	color.z = ray_outuput.recursion / (float)RAY_LOOP * (float)255;*/
	pixel_color = ((int)color.x << 24) + ((int)color.y << 16)
		+ ((int)color.z << 8) + 0xFF;
	return (pixel_color);
}
