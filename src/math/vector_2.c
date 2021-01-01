/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 13:50:59 by hcabel            #+#    #+#             */
/*   Updated: 2020/12/24 12:41:57 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vector	vector_mult(t_vector v, float mult)
{
	v.x *= mult;
	v.y *= mult;
	v.z *= mult;
	return (v);
}

t_vector	vector_crossproduct(t_vector a, t_vector b)
{
	t_vector	r;

	r.x = (a.y - b.z) * (a.z - b.y);
	r.y = (a.z - b.x) * (a.x - b.z);
	r.z = (a.x - b.y) * (a.y - b.x);
	return (r);
}
