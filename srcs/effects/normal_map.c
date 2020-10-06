/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 23:04:19 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/06 13:53:43 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vector	normal_map_to_rgb(t_vector normal)
{
	normal.x = (normal.x + 1) * 127.5;
	normal.y = (normal.y + 1) * 127.5;
	normal.z = (normal.z + 1) * 127.5;
	return (normal);
}

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

t_vector	get_normal_map(t_vector p, t_scene *scene, t_object *hit_obj)
{
	t_object	*objhitindex;
	float		d;
	t_vector	step;
	t_vector	grd;

	step.x = RAY_PRECIS;
	step.y = 0;
	step.z = 0;
	d = get_nearest_surface_distance(scene, p, &objhitindex);
	grd.x = d - get_nearest_surface_distance(scene, vector_add(p, step), &objhitindex);
	step.x = 0;
	step.y = RAY_PRECIS;
	grd.y = d - get_nearest_surface_distance(scene, vector_add(p, step), &objhitindex);
	step.y = 0;
	step.z = RAY_PRECIS;
	grd.z = d - get_nearest_surface_distance(scene, vector_add(p, step), &objhitindex);
	return (vector_normalize(grd));
	/*float		tab[4];
	t_vector	normal;
	t_vector2d	eps;

	eps.x = 1.0 * 0.5773 * 0.0005;
	eps.y = -1.0 * 0.5773 * 0.0005;
	p = vector_subtract(p, hit_obj->location);
	tab[0] = hit_obj->sdf(vector_subtract(p, new_vector(eps.x, eps.y, eps.y)), hit_obj->location);
	tab[1] = hit_obj->sdf(vector_subtract(p, new_vector(eps.y, eps.y, eps.x)), hit_obj->location);
	tab[2] = hit_obj->sdf(vector_subtract(p, new_vector(eps.y, eps.x, eps.y)), hit_obj->location);
	tab[3] = hit_obj->sdf(vector_subtract(p, new_vector(eps.x, eps.x, eps.x)), hit_obj->location);
	normal.x =	eps.x * tab[0] -
				eps.y * tab[1] -
				eps.y * tab[2] -
				eps.x * tab[3];
	normal.y =	eps.y * tab[0] -
				eps.y * tab[1] -
				eps.x * tab[2] -
				eps.x * tab[3];
	normal.z =	eps.y * tab[0] -
				eps.x * tab[1] -
				eps.y * tab[2] -
				eps.x * tab[3];
	return (vector_normalize(normal));*/
}
