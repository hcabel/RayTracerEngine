/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 16:52:21 by hcabel            #+#    #+#             */
/*   Updated: 2021/01/26 13:24:15 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "define.h"
# include "mathematical.h"

typedef struct s_object
{
	t_vector			location;
	t_vector2d			rotation;
	t_vector			scale;
	t_vector			color;
	unsigned int		sdf_index;
	int					istarget;
}						t_object;

typedef struct s_light
{
	t_vector			location;
	t_vector2d			rotation;
	float				intensity;
}						t_light;

typedef struct s_cam
{
	t_vector			location;
	t_vector2d			rotation;
	t_vector			forward;
	unsigned int		viewmode;
}						t_cam;

typedef struct s_scene
{
	t_object			*shapes;
	t_light				*lights;
	t_cam				cam;
	unsigned int		shapes_amount;
	unsigned int		light_amount;
	void				*target;
	int					target_type;
	float				(*sdf_list[5])(t_vector, t_vector);
	int					transphorm_axis;
	int					transphorm_method;
}						t_scene;

#endif