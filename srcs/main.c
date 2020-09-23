/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 22:46:14 by hcabel            #+#    #+#             */
/*   Updated: 2020/09/23 23:04:02 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "rt.h"

int	main(int argc, char** argv)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0 ) {
		ft_printf("Échec de l'initialisation de la SDL |%s|\n", SDL_GetError());
		return (-1);
	}

	SDL_Window* pWindow = NULL;
	pWindow = SDL_CreateWindow("Ma première application SDL2",SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
	SDL_Quit();
	return (0);
}
