/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 18:13:12 by hcabel            #+#    #+#             */
/*   Updated: 2020/09/30 18:13:21 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vector	rotate_y(t_vector r, float v)
{
	t_vector	result;

	result.x = r.x * cos(v) + r.z * sin(v);
	result.y = r.y;
	result.z = r.z * cos(v) - r.x * sin(v);
	return (result);
}
