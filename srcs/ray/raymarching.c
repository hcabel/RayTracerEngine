/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raymarching.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 12:01:02 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/11 12:33:12 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int			check_for_hidden_obj(t_scene *scene, t_vector dir,
						float prec)
{
	t_vector		tmp;
	unsigned int	i;

	i = 0;
	while (i < scene->light_amount)
	{
		tmp = vector_normalize(vector_subtract(scene->lights[0].location,
			scene->cam.location));
		if (tmp.x + prec >= dir.x && tmp.x - prec <= dir.x
			&& tmp.y + prec >= dir.y && tmp.y - prec <= dir.y
			&& tmp.z + prec >= dir.z && tmp.z - prec <= dir.z)
			return (1);
		i++;
	}
	return (0);
}

static unsigned int	get_color_from_viewmode(t_scene *scene, t_ray_hit *ray,
						t_vector olddir)
{
	t_vector		color;
	unsigned int	pixel_color;
	float			intensity;

	color.x = 0;
	color.y = 0;
	color.z = 0;
	if (ray->hit.bool == 1 && ray->hit_object->istarget.bool == 1)
		return (0xff5733ff);
	else if (scene->cam.viewmode == 1 && ray->hit.bool == 1)
	{
		color.x = (ray->hit_object->color.x);
		color.y = (ray->hit_object->color.y);
		color.z = (ray->hit_object->color.z);
	}
	else if (scene->cam.viewmode == 2 && ray->hit.bool == 1)
		color = normal_map_to_rgb(get_normal_map(ray->location, scene,
			ray->hit_object));
	else if (scene->cam.viewmode == 3)
	{
		color.x = ray->recursion / (float)RAY_LOOP * (float)255;
		color.y = ray->recursion / (float)RAY_LOOP * (float)255;
		color.z = ray->recursion / (float)RAY_LOOP * (float)255;
	}
	else if (ray->hit.bool == 1)
	{
		intensity = get_light_intensity(scene, ray->location,
			ray->hit_object, olddir);
		intensity *= fabs(fmaxf(ray->distance / VIEW_DISTANCE, 0.5)
			- 1) * (1 / (1 - 0.5));
		color.x = (ray->hit_object->color.x * intensity);
		color.y = (ray->hit_object->color.y * intensity);
		color.z = (ray->hit_object->color.z * intensity);
	}
	return (((int)color.x << 24) + ((int)color.y << 16)
		+ ((int)color.z << 8) + 0xFF);
}

unsigned int		raymarching(t_scene *scene, t_vector dir)
{
	double		depth;
	t_ray_hit	ray;

	if (check_for_hidden_obj(scene, dir, .01))
	{
		return (((int)255 << 24) + ((int)0 << 16)
			+ ((int)0 << 8) + 0xFF);
	}
	ray = trace_ray(scene, scene->cam.location, dir, VIEW_DISTANCE);
	ray.distance = fminf(VIEW_DISTANCE, fmaxf(0, ray.distance));
	return (get_color_from_viewmode(scene, &ray, dir));
}
