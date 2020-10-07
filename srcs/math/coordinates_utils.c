/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinates_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 14:14:49 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/07 14:14:58 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vector2d	get_pixel_coordinates(unsigned int i, unsigned int width)
{
	t_vector2d	result;

	result.x = i % width;
	result.y = i / width;
	return (result);
}
