/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mathematical.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 13:17:59 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/07 14:24:01 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHEMATICAL_H
# define MATHEMATICAL_H

# include <math.h>

typedef struct	s_vector2d
{
	float		x;
	float		y;
}				t_vector2d;

typedef struct	s_vector
{
	float		x;
	float		y;
	float		z;
}				t_vector;

typedef struct	s_vector4d
{
	float		x;
	float		y;
	float		z;
	float		w;
}				t_vector4d;

typedef struct	s_matrix44f
{
	float		m[4][4];
}				t_matrix44f;

/*
********************************************************************************
**	math Directory
********************************************************************************
*/

/*
**	matrix44.c
*/
t_matrix44f	new_matrix44f(t_vector4d a, t_vector4d b, t_vector4d c,
				t_vector4d d);
t_matrix44f	matrix_mult(t_matrix44f a, t_matrix44f b);

/*
**	vector.c
*/
float		vector_dot(t_vector a, t_vector b);
t_vector	vector_add(t_vector a, t_vector b);
t_vector	vector_normalize(t_vector a);
t_vector	vector_subtract(t_vector a, t_vector b);
float		vector_length(t_vector a);

/*
**	vector_2.c
*/
t_vector	vector_mult(t_vector v, float mult);
t_vector	vector_crossproduct(t_vector a, t_vector b);

/*
**	vector2d.c
*/
float		vector2d_dot(t_vector2d a, t_vector2d b);
t_vector2d	vector2d_add(t_vector2d a, t_vector2d b);
t_vector2d	vector2d_normalize(t_vector2d a);
t_vector2d	vector2d_subtract(t_vector2d a, t_vector2d b);
float		vector2d_length(t_vector2d a);


/*
**	vector4d.c
*/
float		vector4d_dot(t_vector4d a, t_vector4d b);
t_vector4d	vector4d_add(t_vector4d a, t_vector4d b);
t_vector4d	vector4d_normalize(t_vector4d a);
t_vector4d	vector4d_subtract(t_vector4d a, t_vector4d b);
float		vector4d_length(t_vector4d a);

/*
**	vector_init.c
*/
t_vector	new_vector(float x, float y, float z);
t_vector2d	new_vector2d(float x, float y);
t_vector4d	new_vector4d(float x, float y, float z, float w);

/*
**	rotations.c
*/
t_vector	rotate_y(t_vector r, float v);

/*
**	coordinates_utils.c
*/
t_vector2d	get_pixel_coordinates(unsigned int i, unsigned int width);

/*
**	aabb_algo.c
*/
int			aabb(SDL_Rect r, t_vector2d pixel_location);

#endif
