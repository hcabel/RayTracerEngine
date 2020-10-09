/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mathematical.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 13:17:59 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/09 11:04:05 by hcabel           ###   ########.fr       */
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

#endif
