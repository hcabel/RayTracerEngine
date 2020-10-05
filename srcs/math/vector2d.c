/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 13:26:28 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/05 18:38:53 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float		vector2d_length(t_vector2d a)
{
	return (sqrt(a.x * a.x + a.y * a.y));
}

t_vector2d	vector2d_subtract(t_vector2d a, t_vector2d b)
{
	a.x -= b.x;
	a.y -= b.y;
	return (a);
}

t_vector2d	vector2d_normalize(t_vector2d a)
{
	float	length;

	length = vector2d_length(a);
	a.x = a.x / length;
	a.y = a.y / length;
	return (a);
}

t_vector2d	vector2d_add(t_vector2d a, t_vector2d b)
{
	a.x += b.x;
	a.y += b.y;
	return (a);
}

float		vector2d_dot(t_vector2d a, t_vector2d b)
{
	return (a.x * b.x + a.y * b.y);
}
