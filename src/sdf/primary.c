/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primary.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 12:10:49 by hcabel            #+#    #+#             */
/*   Updated: 2021/02/03 11:49:51 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float	sdf_primary_cube(t_vector p, t_vector obj_scale)
{
	t_vector	q;
	t_vector	y;
	float		diff;

	q.x = fabs(p.x) - obj_scale.x;
	q.y = fabs(p.y) - obj_scale.y;
	q.z = fabs(p.z) - obj_scale.z;
	y.x = (fmaxf((q.x), 0.0));
	y.y = (fmaxf((q.y), 0.0));
	y.z = (fmaxf((q.z), 0.0));
	diff = fminf(fmaxf(q.x, fmaxf(q.y, q.z)), 0.0);
	return (vector_length(y) + diff);
}

float	sdf_primary_plane(t_vector p, t_vector obj_scale)
{
	t_vector	q;
	t_vector	y;
	float		diff;

	q.x = fabs(p.x) - obj_scale.x;
	q.y = fabs(p.y) - RAY_PRECIS;
	q.z = fabs(p.z) - obj_scale.z;
	y.x = (fmaxf((q.x), 0.0));
	y.y = (fmaxf((q.y), 0.0));
	y.z = (fmaxf((q.z), 0.0));
	diff = fminf(fmaxf(q.x, fmaxf(q.y, q.z)), 0.0);
	return (vector_length(y) + diff);
}

float	sdf_primary_cylinder(t_vector p, t_vector obj_scale)
{
	float	a;
	float	b;
	float	c;
	float	d;
	float	e;

	a = sqrt(p.x * p.x + p.z * p.z) - obj_scale.x;
	b = fabs(p.y) - obj_scale.y;
	c = fmaxf(a, 0.0);
	d = fmaxf(b, 0.0);
	e = sqrt(c * c + d * d);
	return (fminf(fmaxf(a, b), 0.0) + e);
}

float	sdf_primary_sphere(t_vector p, t_vector obj_scale)
{
	return (vector_length(p) - obj_scale.x);
}

float	sdf_primary_cone(t_vector p, t_vector obj_scale)
{
	t_vector	q;
	t_vector	a;
	t_vector	b;
	float		d;
	float		s;

	q.x = obj_scale.x * obj_scale.x / obj_scale.x;
	q.y = obj_scale.x * -obj_scale.x / obj_scale.z;
	q.z = 0;
	p.x = sqrt(p.x * p.x + p.z * p.z);
	p.y = p.y;
	p.z = 0;
	a.x = p.x - q.x * fminf(1, fmaxf(0, vector_dot(p, q) / vector_dot(q, q)));
	a.y = p.y - q.y * fminf(1, fmaxf(0, vector_dot(p, q) / vector_dot(q, q)));
	a.z = 0;
	b.x = p.x - q.x * fminf(1, fmaxf(0, p.x / q.x));
	b.y = p.y - q.y * fminf(1, fmaxf(0, p.x / q.x));
	b.z = 0;
	s = (q.y < 0 ? -1.0 : 1.0);
	d = fminf(vector_dot(b, b), vector_dot(a, a));
	s = fmaxf(s * (p.x * q.y - p.y * q.x), s * (p.y - q.y));
	return (sqrt(d) * (s < 0 ? -1.0 : 1.0));
}
