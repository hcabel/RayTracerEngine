/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 13:50:59 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/04 14:21:28 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vector	vectormult(t_vector v, float mult)
{
	v.x *= mult;
	v.y *= mult;
	v.z *= mult;
	return (v);
}

t_vector	vectorcrossproduct(t_vector a, t_vector b)
{
	t_vector	r;

	r.x = (a.y - b.z) * (a.z - b.y);
	r.y = (a.z - b.x) * (a.x - b.z);
	r.z = (a.x - b.y) * (a.y - b.x);
	return (r);
}
