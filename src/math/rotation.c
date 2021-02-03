/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 18:13:12 by hcabel            #+#    #+#             */
/*   Updated: 2021/02/02 14:50:55 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vector		rotate_y(t_vector r, float v)
{
	t_vector	result;

	result.x = r.x * cos(v) + r.z * sin(v);
	result.y = r.y;
	result.z = r.z * cos(v) - r.x * sin(v);
	return (result);
}

t_vector		rotation(t_vector src, t_vector2d f)
{
	t_vector	dst;
	float		a;
	float		b;
	float		c;

	a = src.x;
	b = src.y * cos(f.x) + src.z * -sin(f.x);
	c = src.y * sin(f.x) + src.z * cos(f.x);
	dst.x = a;
	dst.y = b;
	dst.z = c;
	a = dst.x * cos(f.y) + dst.z * -sin(f.y);
	b = dst.y;
	c = dst.x * sin(f.y) + dst.z * cos(f.y);
	dst.x = a;
	dst.y = b;
	dst.z = c;
	return (dst);
}

static double	deg2rad(double degrees)
{
	return (degrees * CL_M_PI_F / 180);
}

t_vector		get_ray_direction(t_vector2d coordinates, t_vector2d rot,
					float angle, SDL_Rect area)
{
	t_vector	dir;
	t_vector2d	pixel;
	float		scale;
	float		ratio;

	scale = tan(deg2rad(angle * 0.5));
	ratio = area.w / (float)area.h;
	pixel.x = (2 * ((coordinates.x + 0.5) / area.w) - 1) * scale * ratio;
	pixel.y = (1 - 2 * ((coordinates.y + 0.5) / area.h)) * scale;
	dir = rotation(new_vector(pixel.x, pixel.y, 1), rot);
	return (vector_normalize(dir));
}
