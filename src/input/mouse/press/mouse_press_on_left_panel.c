/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_press_on_left_panel.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 13:19:23 by hcabel            #+#    #+#             */
/*   Updated: 2021/02/04 11:24:28 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		press_on_left_panel(t_vector2d loc, t_info *info)
{
	loc.x -= 0;
	loc.y -= 0;
	if (!info)
		return (GOOD);
	return (0);
}
