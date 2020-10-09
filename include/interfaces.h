/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interfaces.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 18:18:15 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/09 13:09:51 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERFACES_H
# define INTERFACES_H

# include "SDL.h"

# define SCROLLBAR_SIZE 5;

# define VIEWMODE_SCROLLBOX_BUTTON_AMOUNT 4
# define VIEWMODE_BUTTONS_MARGIN 7
# define VIEWMODE_SCROLLBAR_COLOR 0x444444ff
# define VIEWMODE_BACKGROUND_COLOR 0x333333ff
# define VIEWMODE_SCROLLBAR_BUTTON_COLOR 0x222222ff

# define DETAILS_SCROLLBOX_BUTTON_AMOUNT 4
# define DETAILS_BUTTONS_MARGIN 7
# define DETAILS_SCROLLBAR_COLOR 0x444444ff
# define DETAILS_BACKGROUND_COLOR 0x333333ff
# define DETAILS_SCROLLBAR_BUTTON_COLOR 0x222222ff

typedef struct s_info	t_info;

typedef struct			s_button
{
	SDL_Rect			area;
	unsigned			color;
	int					(*clicked)(t_info*);
}						t_button;

typedef struct			s_buttons_scrollbox
{
	SDL_Rect			area;
	t_button			*list;
	unsigned int		amount;
	unsigned int		current;
	unsigned int		color;
	unsigned int		scrollbar_color;
	SDL_Rect			scrollbar_area;
	t_button			scrollbar_button;
}						t_buttons_scrollbox;

typedef struct			s_switch
{
	SDL_Rect			area;
	unsigned			color;
	int					(*clicked)(t_info*);
}						t_switch;

typedef struct			s_viewmode_panel
{
	SDL_Rect			area;
	t_buttons_scrollbox	scrollbox;
}						t_viewmode_panel;

typedef struct			s_details_panel
{
	SDL_Rect			area;
	t_button			addcomponent;
}						t_details_panel;

typedef struct			s_viewport_panel
{
	SDL_Rect			area;
	t_buttons_scrollbox	scrollbox;
	SDL_Rect			image;
}						t_viewport_panel;


#endif
