/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 18:13:12 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/09 11:01:51 by hcabel           ###   ########.fr       */
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
	t_matrix44f	rot_x;
	t_matrix44f	rot_y;
	t_matrix44f	r;
	t_vector	dst;
	float		a;
	float		b;
	float		c;
	float		w;

	rot_x = new_matrix44f(new_vector4d(1, 0, 0, 0),
		new_vector4d(0, cos(f.x), -sin(f.x), 0),
		new_vector4d(0, sin(f.x), cos(f.x), 0), new_vector4d(0, 0, 0, 1));
	rot_y = new_matrix44f(new_vector4d(cos(f.y), 0, -sin(f.y), 0),
		new_vector4d(0, 1, 0, 0),
		new_vector4d(sin(f.y), 0, cos(f.y), 0), new_vector4d(0, 0, 0, 1));
	a = src.x * rot_y.m[0][0] + src.y * rot_y.m[1][0] + src.z * rot_y.m[2][0] + rot_y.m[3][0];
	b = src.x * rot_y.m[0][1] + src.y * rot_y.m[1][1] + src.z * rot_y.m[2][1] + rot_y.m[3][1];
	c = src.x * rot_y.m[0][2] + src.y * rot_y.m[1][2] + src.z * rot_y.m[2][2] + rot_y.m[3][2];
	w = src.x * rot_y.m[0][3] + src.y * rot_y.m[1][3] + src.z * rot_y.m[2][3] + rot_y.m[3][3];
	dst.x = a / w;
	dst.y = b / w;
	dst.z = c / w;
	a = dst.x * rot_x.m[0][0] + dst.y * rot_x.m[1][0] + dst.z * rot_x.m[2][0] + rot_x.m[3][0];
	b = dst.x * rot_x.m[0][1] + dst.y * rot_x.m[1][1] + dst.z * rot_x.m[2][1] + rot_x.m[3][1];
	c = dst.x * rot_x.m[0][2] + dst.y * rot_x.m[1][2] + dst.z * rot_x.m[2][2] + rot_x.m[3][2];
	w = dst.x * rot_x.m[0][3] + dst.y * rot_x.m[1][3] + dst.z * rot_x.m[2][3] + rot_x.m[3][3];
	dst.x = a / w;
	dst.y = b / w;
	dst.z = c / w;
	return (dst);
}

static double	deg2rad(double degrees)
{
	return (degrees * M_PI / 180);
}

t_vector		get_ray_direction_from_coordinate(t_vector2d coordinates,
					t_cam *cam, unsigned int wid, unsigned int height)
{
	t_vector	dir;
	t_vector2d	pixel;
	float		scale = tan(deg2rad(90 * 0.5));
	float		imageAspectRatio = wid / (float)height;

	pixel.x = (2 * ((coordinates.x + 0.5) / wid) - 1) * scale * imageAspectRatio;
	pixel.y = (1 - 2 * ((coordinates.y + 0.5) / height)) * scale;

	dir = rotation(new_vector(pixel.x, pixel.y, 1), cam->rotation);
	return (vector_normalize(dir));
}
