/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector4d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 13:21:03 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/05 14:02:42 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float		vector4dlength(t_vector4d a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w));
}

t_vector4d	vector4dsubtract(t_vector4d a, t_vector4d b)
{
	a.x -= b.x;
	a.y -= b.y;
	a.z -= b.z;
	a.w -= b.w;
	return (a);
}

t_vector4d	vector4dnormalize(t_vector4d a)
{
	float	length;

	length = vector4dlength(a);
	a.x = a.x / length;
	a.y = a.y / length;
	a.z = a.z / length;
	a.w = a.w / length;
	return (a);
}

t_vector4d	vector4dadd(t_vector4d a, t_vector4d b)
{
	a.x += b.x;
	a.y += b.y;
	a.z += b.z;
	a.w += b.w;
	return (a);
}

float		vector4ddot(t_vector4d a, t_vector4d b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w);
}
