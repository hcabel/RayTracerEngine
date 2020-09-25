/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 10:30:45 by hcabel            #+#    #+#             */
/*   Updated: 2020/09/25 11:52:46 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		loop(t_info *info)
{
	t_bool	quit;

	quit.bool = 0;
	while (quit.bool == 0)
	{
		hook_event(&quit, info);
		draw_calls_execution(info);
		draw_calls_clear_list(info);
	}
	return (GOOD);
}
