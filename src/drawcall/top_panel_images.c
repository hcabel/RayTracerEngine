/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   top_panel_images.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 12:53:24 by hcabel            #+#    #+#             */
/*   Updated: 2021/01/29 14:43:39 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	display_viewmode_images(SDL_Renderer *renderer, t_top_panel *panel)
{
	SDL_RenderCopy(renderer, panel->icon[0], NULL,
		&panel->gpu_switch.area);
	SDL_RenderCopy(renderer, panel->icon[1], NULL,
		&panel->savemap_button.area);
}
