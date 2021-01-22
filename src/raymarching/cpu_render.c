/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 12:01:02 by hcabel            #+#    #+#             */
/*   Updated: 2021/01/22 20:17:36 by hcabel           ###   ########.fr       */
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
	unsigned int	tmp;

	if (!ray->hit)
		return (scene->cam.viewmode == DISTANCE_FOG_VIEWMODE ?
			0x0 : DISTANCE_FOG_COLOR);
	if (scene->cam.viewmode == DISTANCE_FOG_VIEWMODE)
	{
		tmp = (fabs(fmaxf(ray->distance / VIEW_DISTANCE, 0.5)
			- 1) * (1 / (1 - 0.5))) * 255;
		color.x = tmp;
		color.y = tmp;
		color.z = tmp;
	}
	else if (scene->cam.viewmode == UNLIT_VIEWMODE)
	{
		color.x = (ray->hit_object->color.x);
		color.y = (ray->hit_object->color.y);
		color.z = (ray->hit_object->color.z);
	}
	else if (scene->cam.viewmode == NORMAL_VIEWMODE)
		color = normal_map_to_rgb(get_normal_map(ray->location, scene,
			ray->hit_object));
	else if (scene->cam.viewmode == ITERATION_VIEWMODE)
	{
		color.x = ray->recursion / (float)RAY_LOOP * (float)255;
		color.y = ray->recursion / (float)RAY_LOOP * (float)255;
		color.z = ray->recursion / (float)RAY_LOOP * (float)255;
	}
	else
		return (0xFF0000FF);
	return (((int)color.x << 24) + ((int)color.y << 16)
		+ ((int)color.z << 8) + 0xFF);
}

/*
**	DISTANCE FOG
**
**	intensity *= fabs(fmaxf(ray->distance / VIEW_DISTANCE, 0.5)
**		- 1) * (1 / (1 - 0.5));
*/

static float	get_diffuse(t_scene *scene, t_ray_hit *ray)
{
	t_vector	normal;
	float		result;
	int			i;

	normal = get_normal_map(ray->location, scene, ray->hit_object);
	result = 0;
	i = 0;
	while (i < scene->light_amount)
	{
		result += fmaxf(0, vector_dot(normal, vector_normalize(vector_subtract(
				scene->lights[i].location, ray->location))));
		i++;
	}
	return (result);
}

static float	get_specular(t_scene *scene, t_ray_hit *ray)
{
	t_vector	normal;
	t_vector	l;
	t_vector	r;
	float		tmp;
	float		result;
	int			i;

	normal = get_normal_map(ray->location, scene, ray->hit_object);
	result = 0;
	i = 0;
	while (i < scene->light_amount)
	{
		l = vector_normalize(vector_subtract(scene->lights[i].location, ray->location));
		r.x = (2 * vector_dot(normal, l) * normal.x) - l.x;
		r.y = (2 * vector_dot(normal, l) * normal.y) - l.y;
		r.z = (2 * vector_dot(normal, l) * normal.x) - l.z;
		tmp = vector_dot(r, vector_subtract(scene->cam.location, ray->location));
		if (tmp > 0)
			result = tmp;
		i++;
	}
	return (result);
}

#define KS 1.0
#define KD 0.7
#define KA 0.2

static float	phong_lighting(t_scene *scene, t_vector oldir, t_ray_hit *ray, int index)
{
	t_vector	N;
	t_vector	L;
	t_vector	R;
	float		dotLN;
	float		dotRV;

	N = get_normal_map(ray->location, scene, ray->hit_object);
	L = vector_normalize(vector_subtract(scene->lights[index].location, ray->location));
	L = vector_mult(L, -1);
	R.x = L.x - 2 * vector_dot(L, N) * N.x;
	R.y = L.y - 2 * vector_dot(L, N) * N.y;
	R.z = L.z - 2 * vector_dot(L, N) * N.z;
	L = vector_mult(L, -1);

	dotLN = vector_dot(L, N);
	dotRV = vector_dot(R, vector_mult(oldir, -1));
	if (dotLN < 0)
		return (0);
	if (dotRV < 0)
		return (1 * (KD * dotLN));
	return (1 * (KD * dotLN + KS * pow(dotRV, 250)));
}

static unsigned int	raymarching_light_steps(t_scene *scene, t_vector oldir,
						t_ray_hit *ray)
{
	t_vector	color;
	float		intensity;

	intensity = 0.1;
	for (int i = 0; i < scene->light_amount; i++)
		intensity += phong_lighting(scene, oldir, ray, i);
	intensity = fminf(1, intensity);
	intensity *= fabs(fmaxf(ray->distance / VIEW_DISTANCE, 0.5)
		- 1) * (1 / (1 - 0.5));

	if (scene->cam.viewmode == DIRECT_ILLUMINATION_VIEWMODE)
		return (((int)(intensity * 255) << 24) + ((int)(intensity * 255) << 16)
			+ (int)(intensity * 0xFF00) + 0xFF);

	color.x = ray->hit_object->color.x * intensity;
	color.y = ray->hit_object->color.y * intensity;
	color.z = ray->hit_object->color.z * intensity;
	return (((int)color.x << 24) + ((int)color.y << 16)
		+ ((int)color.z << 8) + 0xFF);
}

unsigned int		raymarching(t_scene *scene, t_vector dir)
{
	double		depth;
	t_ray_hit	ray;

	if (scene->cam.viewmode != GAME_VIEWMODE
		&& check_for_hidden_obj(scene, dir, .025))
			return (((int)255 << 24) + ((int)0 << 16)
				+ ((int)0 << 8) + 0xFF);
	ray = trace_ray(scene, scene->cam.location, dir, VIEW_DISTANCE);
	ray.distance = fminf(VIEW_DISTANCE, fmaxf(0, ray.distance));
	if (scene->cam.viewmode != GAME_VIEWMODE && ray.hit // working on
		&& ray.hit_object->istarget)
		return (0xff5733ff);
	if (is_one_ray_viewmode(scene->cam.viewmode) == GOOD)
		return (get_color_from_one_ray_viewmode(scene, &ray));
	if (!ray.hit)
		return (DISTANCE_FOG_COLOR);
	return (raymarching_light_steps(scene, dir, &ray));
}
