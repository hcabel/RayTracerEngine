/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interfaces.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 18:18:15 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/29 12:49:01 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERFACES_H
# define INTERFACES_H

# include "SDL.h"

# define SCROLLBAR_SIZE 5;
# define SCROLLBAR_COLOR 0x444444FF
# define BUTTON_COLOR 0x063547FF
# define BUTTON_HOVER_COLOR 0xEC3547FF

# define VIEWMODE_SCROLLBOX_BUTTON_AMOUNT 5
# define VIEWMODE_BUTTONS_MARGIN 2
# define VIEWMODE_BACKGROUND_COLOR 0x1C1C22FF

# define DETAILS_BACKGROUND_COLOR 0x24242BFF
# define DETAILS_BUTTONS_MARGIN 5

typedef struct s_info	t_info;

typedef struct			s_bool
{
	unsigned			bool:1;
}						t_bool;

typedef struct			s_button
{
	SDL_Rect			area;
	unsigned int		color;
	unsigned int		hover_color;
	t_bool				ishover;
	int					(*clicked)(t_info*);
}						t_button;

typedef struct			s_buttons_scrollbox
{
	SDL_Rect			area;
	t_button			*list;
	unsigned int		amount;
	unsigned int		current;
	unsigned int		scrollbar_color;
	SDL_Rect			scrollbar_area;
	t_button			scrollbar_button;
}						t_buttons_scrollbox;

typedef struct			s_selector
{
	SDL_Rect			area;
	unsigned int		max;
	unsigned int		min;
	SDL_Rect			preview_area;
	t_button			b_left;
	t_button			b_right;
	unsigned int		(*preview)(t_vector2d, t_info*);
}						t_selector;

typedef struct			s_vector_visualizer
{
	SDL_Rect			area;
	SDL_Rect			areax;
	SDL_Rect			areay;
	SDL_Rect			areaz;
	t_vector			*values;
}						t_vector_visualizer;

typedef struct			s_triple_switch
{
	SDL_Rect			area;
	t_button			first;
	t_button			second;
	t_button			third;
}						t_triple_switch;

typedef struct			s_viewmode_panel
{
	SDL_Rect			area;
	t_buttons_scrollbox	scrollbox;
	void				*pixels;
	SDL_Texture			*images[VIEWMODE_SCROLLBOX_BUTTON_AMOUNT];
}						t_viewmode_panel;

typedef struct			s_details_panel
{
	SDL_Rect			area;
	t_selector			shape_selector;
	t_triple_switch		triple_switch_axis;
	SDL_Rect			tri_vector_pannel;
	t_button			addcomponent;
	void				*pixels;
}						t_details_panel;

#endif
