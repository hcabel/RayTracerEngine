/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_images.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 13:50:40 by hcabel            #+#    #+#             */
/*   Updated: 2020/11/05 12:18:33 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	load_viewmode_images(SDL_Renderer *renderer,
				t_viewmode_panel *viewmode)
{
	if (new_Image(renderer, "assets/icon_unlit.tga", &(viewmode->images[0])) != GOOD)
		return (FAILED);
	if (new_Image(renderer, "assets/icon_normal.tga", &(viewmode->images[1])) != GOOD)
		return (FAILED);
	if (new_Image(renderer, "assets/icon_iterations.tga", &(viewmode->images[2])) != GOOD)
		return (FAILED);
	viewmode->images[3] = NULL;
	viewmode->images[4] = NULL;
	return (GOOD);
}

int		load_interface_images(SDL_Renderer *renderer, t_screen *screen)
{
	load_viewmode_images(renderer, &screen->viewmode);
	return (GOOD);
}

int		display_viewmode_images(SDL_Renderer *renderer,
			t_viewmode_panel *viewmode)
{
	SDL_RenderCopy(renderer, viewmode->images[0], NULL,
		&viewmode->scrollbox.list[1].area);
	SDL_RenderCopy(renderer, viewmode->images[1], NULL,
		&viewmode->scrollbox.list[2].area);
	SDL_RenderCopy(renderer, viewmode->images[2], NULL,
		&viewmode->scrollbox.list[3].area);
}
