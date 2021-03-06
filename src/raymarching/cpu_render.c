/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 12:01:02 by hcabel            #+#    #+#             */
/*   Updated: 2021/02/04 11:26:50 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int			is_one_ray_viewmode(int vm)
{
	if (vm == UNLIT_VIEWMODE || vm == NORMAL_VIEWMODE
		|| vm == ITERATION_VIEWMODE || vm == DISTANCE_FOG_VIEWMODE)
		return (GOOD);
	return (FAILED);
}

static int			check_for_hidden_obj(t_scene *scene, t_vector dir,
						float prec)
{
	t_vector		tmp;
	unsigned int	i;

	i = 0;
	while (i < scene->light_amount)
	{
		tmp = vector_normalize(vector_subtract(scene->lights[i].location,
			scene->cam.location));
		if (tmp.x + prec >= dir.x && tmp.x - prec <= dir.x
			&& tmp.y + prec >= dir.y && tmp.y - prec <= dir.y
			&& tmp.z + prec >= dir.z && tmp.z - prec <= dir.z)
			return (1);
		i++;
	}
	return (0);
}

static unsigned int	get_color_from_one_ray_viewmode(t_scene *scene,
						t_ray_hit *ray)
{
	t_vector		color;

	if (!ray->hit && scene->cam.viewmode != ITERATION_VIEWMODE)
	{
		return (scene->cam.viewmode == DISTANCE_FOG_VIEWMODE ?
			0x0 : DISTANCE_FOG_COLOR);
	}
	if (scene->cam.viewmode == DISTANCE_FOG_VIEWMODE)
		color = new_vector_uniform(fabs(fmaxf(ray->distance / VIEW_DISTANCE,
			FOG_START) - 1) * (1 / fmaxf(0.0001, 1 - FOG_START)) * 255);
	else if (scene->cam.viewmode == UNLIT_VIEWMODE)
		color = new_vector(ray->hit_object->color.x, ray->hit_object->color.y,
			ray->hit_object->color.z);
	else if (scene->cam.viewmode == NORMAL_VIEWMODE)
		color = normal_map_to_rgb(get_normal_map(ray->location, scene));
	else if (scene->cam.viewmode == ITERATION_VIEWMODE)
		color = new_vector(ray->recursion / (float)RAY_LOOP * (float)255,
			ray->recursion / (float)RAY_LOOP * (float)255,
			ray->recursion / (float)RAY_LOOP * (float)255);
	return (((int)color.x << 24) + ((int)color.y << 16)
		+ ((int)color.z << 8) + 0xFF);
}

static unsigned int	raymarching_light_steps(t_scene *scene, t_vector oldir,
						t_ray_hit *ray)
{
	t_vector		color;
	float			intensity;
	unsigned int	i;

	intensity = 0.1;
	i = 0;
	while (i < scene->light_amount)
		intensity += fmaxf(0, phong_lighting(scene, oldir, ray, i++));
	intensity = fminf(1, intensity);
	intensity *= fabs(fmaxf(ray->distance / VIEW_DISTANCE, FOG_START)
		- 1) * (1 / fmaxf(0.0001, 1 - FOG_START));
	if (scene->cam.viewmode == DIRECT_ILLUMINATION_VIEWMODE)
	{
		return (((int)(intensity * 255) << 24) + ((int)(intensity * 255) << 16)
			+ (int)(intensity * 0xFF00) + 0xFF);
	}
	color.x = ray->hit_object->color.x * intensity;
	color.y = ray->hit_object->color.y * intensity;
	color.z = ray->hit_object->color.z * intensity;
	return (((int)color.x << 24) + ((int)color.y << 16)
		+ ((int)color.z << 8) + 0xFF);
}

unsigned int		raymarching(t_scene *scene, t_vector dir)
{
	t_ray_hit	ray;

	if (scene->cam.viewmode != GAME_VIEWMODE
		&& scene->cam.viewmode != ITERATION_VIEWMODE
		&& check_for_hidden_obj(scene, dir, .025))
		return (0xFF0000FF);
	ray = trace_ray(scene, scene->cam.location, dir, VIEW_DISTANCE);
	ray.distance = fminf(VIEW_DISTANCE, fmaxf(0, ray.distance));
	if (is_one_ray_viewmode(scene->cam.viewmode) == GOOD)
		return (get_color_from_one_ray_viewmode(scene, &ray));
	if (!ray.hit)
		return (DISTANCE_FOG_COLOR);
	return (raymarching_light_steps(scene, dir, &ray));
}
