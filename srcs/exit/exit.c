/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 22:36:14 by hcabel            #+#    #+#             */
/*   Updated: 2020/09/24 23:22:03 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	get_error_info(int code)
{
	char	*errortab[] = {
		"Unkown error", "Malloc error", "SDL error", "Parsing error"
	};

	if (code == SDL_ERROR)
		ft_printf("{r}SDL error : %s\n", SDL_GetError());
	else if (code == PARSING_ERROR)
		ft_printf("{r}Parsing Error : %s\n", errortab[code - 1]);
	else
		ft_printf("{r}Raytracer Error : %s\n", errortab[code - 1]);

}

int			program_exit(t_info *info, int code)
{

	if (code != 0)
		get_error_info(code);
	else
		ft_printf("{g}Thanks for using, have a good day !\n");
	free_info_struct(info);
	SDL_DestroyRenderer(info->renderer);
	SDL_DestroyWindow(info->window);
	SDL_Quit();
	return (code);
}
