/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 23:04:19 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/05 18:45:58 by hcabel           ###   ########.fr       */
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
	p = vector_subtract(p, hit_obj->location);
	tab[0] = hit_obj->sdf(vector_subtract(p, new_vector(eps.x, eps.y, eps.y)), hit_obj->location);
	tab[1] = hit_obj->sdf(vector_subtract(p, new_vector(eps.y, eps.y, eps.x)), hit_obj->location);
	tab[2] = hit_obj->sdf(vector_subtract(p, new_vector(eps.y, eps.x, eps.y)), hit_obj->location);
	tab[3] = hit_obj->sdf(vector_subtract(p, new_vector(eps.x, eps.x, eps.x)), hit_obj->location);
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
	return (vector_normalize(normal));
}
