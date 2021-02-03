/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_interfaces_images.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 16:49:23 by hcabel            #+#    #+#             */
/*   Updated: 2021/01/29 14:45:04 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	init_top_panel_images(SDL_Renderer *renderer, t_top_panel *panel)
{
	int	code;

	code = new_image(renderer, "assets/GPU_icon.tga", &(panel->icon[0]));
	if (code != GOOD)
		return (code);
	code = new_image(renderer, "assets/Save_icon.tga", &(panel->icon[1]));
	if (code != GOOD)
		return (code);
	return (GOOD);
}
