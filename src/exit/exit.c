/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 12:51:36 by hcabel            #+#    #+#             */
/*   Updated: 2021/02/05 12:02:04 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	free_gpu(t_info *info)
{
	clFlush(info->kernel.command_queue);
	clFinish(info->kernel.command_queue);
	clReleaseProgram(info->kernel.program);
	ft_memdel((void**)&info->kernel.kernel_str);
}

static void	free_sdl(t_info *info)
{
	SDL_DestroyRenderer(info->renderer);
	SDL_DestroyWindow(info->window);
	SDL_Quit();
}

int			program_exit(t_info *info, int code)
{
	if (!info->ongpu)
		kill_all_thread(&info->screen.viewport.sampling);
	if (code != GOOD)
		ft_printf("{r}FATAL ERROR : %s !\n", error_to_str(code));
	else
		ft_printf("{g}Thanks for using, have a good day !\n{r}");
	free_info_struct(info);
	if (info->gpuinitialised)
		free_gpu(info);
	if (code != SDL_ERROR)
		free_sdl(info);
	return (code);
}
