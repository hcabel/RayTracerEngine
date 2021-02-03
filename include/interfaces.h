/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interfaces.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 18:18:15 by hcabel            #+#    #+#             */
/*   Updated: 2021/02/03 14:59:30 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERFACES_H
# define INTERFACES_H

# include "SDL.h"
# include "define.h"
# include "mathematical.h"

typedef struct s_info		t_info;

typedef struct				s_button
{
	SDL_Rect				area;
	unsigned int			color;
	unsigned int			hover_color;
	int						ishover;
	int						(*clicked)(t_info*);
}							t_button;

typedef struct				s_scrollbar
{
	unsigned int			enable;
	unsigned int			max;
	float					ratio;
	unsigned int			color;
	SDL_Rect				area;
	t_button				button;

}							t_scrollbar;

typedef struct				s_switch
{
	SDL_Rect				area;
	unsigned int			color_on;
	unsigned int			color_off;
	unsigned int			hover_color;
	int						ishover;
	int						ison;
	int						(*clicked)(t_info*, struct s_switch*);
}							t_switch;

typedef struct				s_viewmode_scrollbox
{
	SDL_Rect				area;
	t_button				*viewmode_list;
	int						current;
	t_scrollbar				scrollbar;
}							t_viewmode_scrollbox;

typedef struct				s_selector
{
	SDL_Rect				area;
	unsigned int			max;
	unsigned int			min;
	SDL_Rect				preview_area;
	t_button				b_left;
	t_button				b_right;
	unsigned int			(*preview)(struct s_vector2d, t_info*);
}							t_selector;

typedef struct				s_vector_visualizer
{
	SDL_Rect				area;
	SDL_Rect				areax;
	SDL_Rect				areay;
	SDL_Rect				areaz;
	t_vector				*values;
}							t_vector_visualizer;

typedef struct				s_triple_switch
{
	SDL_Rect				area;
	unsigned int			selected_color;
	int						selected_button;
	t_button				first;
	t_button				second;
	t_button				third;
}							t_triple_switch;

typedef struct				s_top_panel
{
	SDL_Rect				area;
	t_button				savemap_button;
	t_viewmode_scrollbox	viewmode;
	t_switch				gpu_switch;
	SDL_Texture				*icon[TOP_PANEL_ICON_AMOUNT];
	void					*pixels;
}							t_top_panel;

/*
**	t_selector				shape_selector;
**	t_triple_switch			triple_switch_axis;
**	SDL_Rect				tri_vector_pannel;
*/

typedef struct				s_left_panel
{
	SDL_Rect				area;
	t_button				addcomponent;
	void					*pixels;
	int						skip_selector_preview;
}							t_left_panel;
#endif
