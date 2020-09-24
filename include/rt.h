/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 22:45:47 by hcabel            #+#    #+#             */
/*   Updated: 2020/09/24 23:06:25 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

/*
**	Lib includes
*/
# include "SDL.h"
# include "ft_printf.h"

/*
**	Personal includes
*/
# include "types.h"

/*
**	Modifyable define
*/
# define WINDOW_NAME "RayTracer Engine"
# define WIN_HEIGTH 700
# define WIN_WIDTH 500

/*
**	Code understanding define
*/
# define GOOD 0
# define UNKNOWN_ERROR 1
# define MALLOC_ERROR 2
# define SDL_ERROR 3
# define PARSING_ERROR 4

/*
********************************************************************************
**	player file
********************************************************************************
*/

/*
**	hook.c
*/
void	hook_event(t_bool *quit, t_bool *update);

/*
********************************************************************************
**	viewport file
********************************************************************************
*/

/*
**	viewport.c
*/
void	new_viewport_frame_render(t_info *info);

/*
********************************************************************************
**	exit file
********************************************************************************
*/

/*
**	error.c
*/
int		program_exit(t_info *info, int code);


/*
**	free.c
*/
void	free_info_struct(t_info *info);

#endif
