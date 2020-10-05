/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix44.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 14:02:50 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/05 14:14:56 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_matrix44f	newmatrix44f(t_vector4d a, t_vector4d b, t_vector4d c, t_vector4d d)
{
	t_matrix44f	result;

	result.m[0][0] = a.x;
	result.m[0][1] = a.y;
	result.m[0][2] = a.z;
	result.m[0][3] = a.w;
	result.m[1][0] = b.x;
	result.m[1][1] = b.y;
	result.m[1][2] = b.z;
	result.m[1][3] = b.w;
	result.m[2][0] = c.x;
	result.m[2][1] = c.y;
	result.m[2][2] = c.z;
	result.m[2][3] = c.w;
	result.m[3][0] = d.x;
	result.m[3][1] = d.y;
	result.m[3][2] = d.z;
	result.m[3][3] = d.w;
	return (result);
}

t_matrix44f	matrix_mult(t_matrix44f a, t_matrix44f b)
{
	t_matrix44f r;

	r.m[0][0] = vector4ddot(newvector4d(a.m[0][0], a.m[0][1], a.m[0][2], a.m[0][3]), newvector4d(a.m[0][0], a.m[1][0], a.m[2][0], a.m[3][0]));
	r.m[0][1] = vector4ddot(newvector4d(a.m[0][0], a.m[0][1], a.m[0][2], a.m[0][3]), newvector4d(a.m[0][1], a.m[1][1], a.m[2][1], a.m[3][1]));
	r.m[0][2] = vector4ddot(newvector4d(a.m[0][0], a.m[0][1], a.m[0][2], a.m[0][3]), newvector4d(a.m[0][2], a.m[1][2], a.m[2][2], a.m[3][2]));
	r.m[0][3] = vector4ddot(newvector4d(a.m[0][0], a.m[0][1], a.m[0][2], a.m[0][3]), newvector4d(a.m[0][3], a.m[1][3], a.m[2][3], a.m[3][3]));
	r.m[1][0] = vector4ddot(newvector4d(a.m[1][0], a.m[1][1], a.m[1][2], a.m[1][3]), newvector4d(a.m[0][0], a.m[1][0], a.m[2][0], a.m[3][0]));
	r.m[1][1] = vector4ddot(newvector4d(a.m[1][0], a.m[1][1], a.m[1][2], a.m[1][3]), newvector4d(a.m[0][1], a.m[1][1], a.m[2][1], a.m[3][1]));
	r.m[1][2] = vector4ddot(newvector4d(a.m[1][0], a.m[1][1], a.m[1][2], a.m[1][3]), newvector4d(a.m[0][2], a.m[1][2], a.m[2][2], a.m[3][2]));
	r.m[1][3] = vector4ddot(newvector4d(a.m[1][0], a.m[1][1], a.m[1][2], a.m[1][3]), newvector4d(a.m[0][3], a.m[1][3], a.m[2][3], a.m[3][3]));
	r.m[2][0] = vector4ddot(newvector4d(a.m[2][0], a.m[2][1], a.m[2][2], a.m[2][3]), newvector4d(a.m[0][0], a.m[1][0], a.m[2][0], a.m[3][0]));
	r.m[2][1] = vector4ddot(newvector4d(a.m[2][0], a.m[2][1], a.m[2][2], a.m[2][3]), newvector4d(a.m[0][1], a.m[1][1], a.m[2][1], a.m[3][1]));
	r.m[2][2] = vector4ddot(newvector4d(a.m[2][0], a.m[2][1], a.m[2][2], a.m[2][3]), newvector4d(a.m[0][2], a.m[1][2], a.m[2][2], a.m[3][2]));
	r.m[2][3] = vector4ddot(newvector4d(a.m[2][0], a.m[2][1], a.m[2][2], a.m[2][3]), newvector4d(a.m[0][3], a.m[1][3], a.m[2][3], a.m[3][3]));
	r.m[3][0] = vector4ddot(newvector4d(a.m[3][0], a.m[3][1], a.m[3][2], a.m[3][3]), newvector4d(a.m[0][0], a.m[1][0], a.m[2][0], a.m[3][0]));
	r.m[3][1] = vector4ddot(newvector4d(a.m[3][0], a.m[3][1], a.m[3][2], a.m[3][3]), newvector4d(a.m[0][1], a.m[1][1], a.m[2][1], a.m[3][1]));
	r.m[3][2] = vector4ddot(newvector4d(a.m[3][0], a.m[3][1], a.m[3][2], a.m[3][3]), newvector4d(a.m[0][2], a.m[1][2], a.m[2][2], a.m[3][2]));
	r.m[3][3] = vector4ddot(newvector4d(a.m[3][0], a.m[3][1], a.m[3][2], a.m[3][3]), newvector4d(a.m[0][3], a.m[1][3], a.m[2][3], a.m[3][3]));
	return (r);
}
