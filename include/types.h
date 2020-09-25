/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 22:46:53 by hcabel            #+#    #+#             */
/*   Updated: 2020/09/25 13:27:25 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

#include "mathematical.h"

/*
**	Upgrading Define
*/
# define UPGRADE_FUNCTION_AMOUNT 1

typedef struct			s_bool
{
	unsigned			bool:1;
}						t_bool;

typedef struct			s_object
{
	t_vector			location;
	t_vector2d			rotation;
	t_vector			scale;
}						t_object;

typedef struct			s_scene
{
	t_object			*shapes;
}						t_scene;

typedef struct s_info	t_info;

struct					s_info
{
	SDL_Window			*window;
	SDL_Renderer		*renderer;
	void				(*update_function_list[UPGRADE_FUNCTION_AMOUNT])
							(t_info *info);
};

#endif
