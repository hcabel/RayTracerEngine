/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 15:07:59 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/05 18:38:54 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vector	new_vector(float x, float y, float z)
{
	t_vector	a;

	a.x = x;
	a.y = y;
	a.z = z;
	return (a);
}

t_vector2d	new_vector2d(float x, float y)
{
	t_vector2d	a;

	a.x = x;
	a.y = y;
	return (a);
}

t_vector4d	new_vector4d(float x, float y, float z, float w)
{
	t_vector4d	a;

	a.x = x;
	a.y = y;
	a.z = z;
	a.w = w;
	return (a);
}
