/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 15:01:19 by hcabel            #+#    #+#             */
/*   Updated: 2021/02/03 12:38:13 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_vector	get_r_vector(t_vector l, t_vector n)
{
	t_vector	r;

	r.x = l.x - 2 * vector_dot(l, n) * n.x;
	r.y = l.y - 2 * vector_dot(l, n) * n.y;
	r.z = l.z - 2 * vector_dot(l, n) * n.z;
	return (r);
}

float			phong_lighting(t_scene *scene, t_vector oldir,
					t_ray_hit *ray, int index)
{
	t_vector	n;
	t_vector	l;
	float		dot_ln;
	float		dot_rv;
	float		intensity;

	n = get_normal_map(ray->location, scene, ray->hit_object);
	l = vector_subtract(scene->lights[index].location, ray->location);
	if (vector_length(l) >= 100)
		return (0);
	intensity = fabs((vector_length(l) - 100) / (float)100);
	l = vector_normalize(l);
	dot_ln = vector_dot(l, n);
	dot_rv = vector_dot(get_r_vector(vector_mult(l, -1), n),
		vector_mult(oldir, -1));
	if (dot_ln < 0 || trace_ray(scene, vector_add(ray->location, n), l,
		vector_length(vector_subtract(scene->lights[index].location,
		ray->location))).hit)
		return (0);
	if (dot_rv < 0)
		return (intensity * (KD * dot_ln));
	return (intensity * (KD * dot_ln + KS * pow(dot_rv, 250)));
}
