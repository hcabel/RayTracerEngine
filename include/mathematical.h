/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mathematical.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 13:17:59 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/05 14:16:44 by hcabel           ###   ########.fr       */
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
t_matrix44f	newmatrix44f(t_vector4d a, t_vector4d b, t_vector4d c,
				t_vector4d d);
t_matrix44f	matrix_mult(t_matrix44f a, t_matrix44f b);

/*
**	vector.c
*/
float		vectordot(t_vector a, t_vector b);
t_vector	vectoradd(t_vector a, t_vector b);
t_vector	vectornormalize(t_vector a);
t_vector	vectorsubtract(t_vector a, t_vector b);
float		vectorlength(t_vector a);

/*
**	vector_2.c
*/
t_vector	vectormult(t_vector v, float mult);
t_vector	vectorcrossproduct(t_vector a, t_vector b);

/*
**	vector2d.c
*/
float		vector2ddot(t_vector2d a, t_vector2d b);
t_vector2d	vector2dadd(t_vector2d a, t_vector2d b);
t_vector2d	vector2dnormalize(t_vector2d a);
t_vector2d	vector2dsubtract(t_vector2d a, t_vector2d b);
float		vector2dlength(t_vector2d a);


/*
**	vector4d.c
*/
float		vector4ddot(t_vector4d a, t_vector4d b);
t_vector4d	vector4dadd(t_vector4d a, t_vector4d b);
t_vector4d	vector4dnormalize(t_vector4d a);
t_vector4d	vector4dsubtract(t_vector4d a, t_vector4d b);
float		vector4dlength(t_vector4d a);

/*
**	vector_init.c
*/
t_vector	newvector(float x, float y, float z);
t_vector2d	newvector2d(float x, float y);
t_vector4d	newvector4d(float x, float y, float z, float w);

/*
**	rotations.c
*/
t_vector	rotate_y(t_vector r, float v);

#endif
