/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 12:51:36 by hcabel            #+#    #+#             */
/*   Updated: 2020/12/31 13:05:16 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 22:36:14 by hcabel            #+#    #+#             */
/*   Updated: 2020/11/06 19:24:29 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			program_exit(t_info *info, int code)
{
	if (!info->ongpu)
		kill_all_thread(&info->screen.viewport.sampling);
	if (code != GOOD)
		ft_printf("{r}FATAL ERROR : %s !\n", error_to_str(code));
	else
		ft_printf("{g}Thanks for using, have a good day !\n{r}");

	if (info->gpuinitialised)
	{
		clFlush(info->kernel.command_queue);
		clFinish(info->kernel.command_queue);
		clReleaseProgram(info->kernel.program);
		ft_memdel((void**)&info->kernel.kernel_str);
	}

	if (code != SDL_ERROR)
	{
		free_info_struct(info);
		SDL_DestroyRenderer(info->renderer);
		SDL_DestroyWindow(info->window);
		SDL_Quit();
	}
	return (code);
}
