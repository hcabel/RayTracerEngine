/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb_algo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 14:19:20 by hcabel            #+#    #+#             */
/*   Updated: 2021/01/29 17:45:59 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
**	Usefully for colisions between to square (sprites).
**	I gonna use it to detect if my pixel location is inside a button
*/

int		aabb(SDL_Rect r, t_vector2d pixel_location)
{
	if (pixel_location.x <= r.x + r.w && pixel_location.x >= r.x
		&& pixel_location.y <= r.y + r.h && pixel_location.y >= r.y)
		return (GOOD);
	return (FAILED);
}
