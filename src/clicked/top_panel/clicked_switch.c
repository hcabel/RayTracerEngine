/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clicked_switch.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 17:59:25 by hcabel            #+#    #+#             */
/*   Updated: 2021/01/02 14:22:25 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	gpu_switch_clicked(t_info *info, t_switch *button)
{
	int	code;

	if (button->ison)
	{
		button->ison = 0;
		info->screen.viewport.sampling.threads_status =
			info->screen.viewport.sampling.threads_end_status;
		info->ongpu = 0;
		return (3);
	}
	else
	{
		if (!info->gpuinitialised)
		{
			if ((code = init_kernel(info)) != GOOD)
				return (code);
			if (!info->gpuinitialised)
				return (0);
		}
		info->ongpu = 1;
		button->ison = 1;
		return (3);
	}
	return (0);
}