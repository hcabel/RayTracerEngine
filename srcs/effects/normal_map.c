/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 23:04:19 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/02 23:19:41 by hcabel           ###   ########.fr       */
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

t_vector	get_normal_map(t_vector p, t_scene *scene, t_object *hit_obj)
{
	float		tab[4];
	t_vector	normal;
	t_vector2d	eps;

	eps.x = 1.0 * 0.5773 * 0.0005;
	eps.y = -1.0 * 0.5773 * 0.0005;
	tab[0] = hit_obj->sdf(vectorsubtract(p, newvector(eps.x, eps.y, eps.y)), hit_obj->location);
	tab[1] = hit_obj->sdf(vectorsubtract(p, newvector(eps.y, eps.y, eps.x)), hit_obj->location);
	tab[2] = hit_obj->sdf(vectorsubtract(p, newvector(eps.y, eps.x, eps.y)), hit_obj->location);
	tab[3] = hit_obj->sdf(vectorsubtract(p, newvector(eps.x, eps.x, eps.x)), hit_obj->location);
	normal.x =	eps.x * tab[0] +
				eps.y * tab[1] +
				eps.y * tab[2] +
				eps.x * tab[3];
	normal.y =	eps.y * tab[0] +
				eps.y * tab[1] +
				eps.x * tab[2] +
				eps.x * tab[3];
	normal.z =	eps.y * tab[0] +
				eps.x * tab[1] +
				eps.y * tab[2] +
				eps.x * tab[3];
	return (vectornormalize(normal));
	/*float		d;
	t_vector	step;
	t_vector	normal;

	p = vectorsubtract(p, hit_obj->location);
	step.x = RAY_PRECIS;
	step.y = 0;
	step.z = 0;
	d = hit_obj->sdf(p, hit_obj->location);
	normal.x = d - hit_obj->sdf(vectorsubtract(step, p), hit_obj->location);
	step.x = 0;
	step.y = RAY_PRECIS;
	normal.y = d - hit_obj->sdf(vectorsubtract(step, p), hit_obj->location);
	step.y = 0;
	step.z = RAY_PRECIS;
	normal.z = d - hit_obj->sdf(vectorsubtract(step, p), hit_obj->location);
	return (vectornormalize(normal));*/
}
