/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 13:26:28 by hcabel            #+#    #+#             */
/*   Updated: 2020/09/25 13:28:17 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float		vector2dlength(t_vector2d a)
{
	return (sqrt(a.x * a.x + a.y * a.y));
}

t_vector2d	vector2dsubtract(t_vector2d a, t_vector2d b)
{
	a.x -= b.x;
	a.y -= b.y;
	return (a);
}

t_vector2d	vector2dnormalize(t_vector2d a)
{
	float	length;

	length = vector2dlength(a);
	a.x = a.x / length;
	a.y = a.y / length;
	return (a);
}

t_vector2d	vector2dadd(t_vector2d a, t_vector2d b)
{
	a.x += b.x;
	a.y += b.y;
	return (a);
}

float		vector2ddot(t_vector2d a, t_vector2d b)
{
	return (a.x * b.x + a.y * b.y);
}
