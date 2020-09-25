/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mathematical.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 13:17:59 by hcabel            #+#    #+#             */
/*   Updated: 2020/09/25 15:09:50 by hcabel           ###   ########.fr       */
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

/*
********************************************************************************
**	math Directory
********************************************************************************
*/

/*
**	vector.c
*/
float		vectordot(t_vector a, t_vector b);
t_vector	vectoradd(t_vector a, t_vector b);
t_vector	vectornormalize(t_vector a);
t_vector	vectorsubtract(t_vector a, t_vector b);
float		vectorlength(t_vector a);

/*
**	vector2d.c
*/
float		vector2ddot(t_vector2d a, t_vector2d b);
t_vector2d	vector2dadd(t_vector2d a, t_vector2d b);
t_vector2d	vector2dnormalize(t_vector2d a);
t_vector2d	vector2dsubtract(t_vector2d a, t_vector2d b);
float		vector2dlength(t_vector2d a);

/*
**	vector_utils.c
*/
t_vector	newvector(float x, float y, float z);
t_vector2d	newvector2d(float x, float y);

#endif
