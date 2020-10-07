/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interfaces.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 18:18:15 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/07 17:10:10 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERFACES_H
# define INTERFACES_H

# include "SDL.h"

# define SCROLLBOX_VIEWMODE_BUTTON_AMOUNT 3
# define VIEWMODE_BUTTONS_MARGIN 7
# define VIEWMODE_SCROLLBAR_COLOR 0x444444ff
# define VIEWMODE_BACKGROUND_COLOR 0x333333ff
# define VIEWMODE_SCROLLBAR_BUTTON_COLOR 0x222222ff
# define SCROLLBAR_SIZE 5;
# define SCROLLBAR_BUTTON_SIZE 20;

typedef struct s_info	t_info;

typedef struct			s_button
{
	SDL_Rect			area;
	unsigned			color;
	void				(*click)(t_info*);
}						t_button;

typedef struct			s_scrollbox
{
	SDL_Rect			area;
	t_button			*list;
	unsigned int		amount;
	unsigned int		current;
	unsigned int		color;
	unsigned int		scrollbar_color;
	SDL_Rect			scrollbar_area;
	t_button			scrollbar_button;
}						t_scrollbox;

typedef struct			s_detail_panel
{

}						t_detail_panel;

#endif
