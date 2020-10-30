/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonts.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 12:33:02 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/30 10:22:13 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static SDL_Rect	get_char_font_location(char c)
{
	SDL_Rect	char_font_location;

	char_font_location.w = 37;
	char_font_location.h = 58;
	char_font_location.x = ((int)c - 32) % 20 * 39 + 1;
	char_font_location.y = ((int)c - 32) / 20 * 80 + 21;
	return (char_font_location);
}

int			put_str_on_screen(SDL_Renderer *renderer, SDL_Texture *font,
				SDL_Rect *textarea, char *str)
{
	unsigned int	i;
	unsigned int	len;
	SDL_Rect		font_char_loc;
	SDL_Rect		char_area;

	len  = ft_strlen(str);
	char_area.x = textarea->x;
	char_area.y = textarea->y;
	char_area.h = textarea->h;
	if (textarea->w / len <= char_area.h / 2)
		char_area.w = textarea->h / 2;
	else
		char_area.w = textarea->w / len;
	i = 0;
	while (i < len)
	{
		font_char_loc = get_char_font_location(str[i]);
		SDL_RenderCopy(renderer, font, &font_char_loc, &char_area);
		char_area.x += char_area.w;
		i++;
	}
	return (GOOD);
}
