/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonts.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 12:33:02 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/25 16:34:00 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static SDL_Rect	get_char_font_location(char c)
{
	SDL_Rect	char_font_location;

	char_font_location.w = 29;
	char_font_location.h = 42;
	char_font_location.x = ((int)c - 32) % 20 * 39;
	char_font_location.y = ((int)c - 32) / 20 * 80;
	char_font_location.x += 9;
	char_font_location.y += 37;
	return (char_font_location);
}

int			put_str_on_screen(SDL_Renderer *renderer, SDL_Texture *font,
				SDL_Rect *startchar, char *str)
{
	unsigned int	i;
	unsigned int	len;
	SDL_Rect		font_char_loc;
	SDL_Rect		new_char_screen_loc;

	new_char_screen_loc.x = startchar->x;
	new_char_screen_loc.y = startchar->y;
	new_char_screen_loc.w = startchar->w;
	new_char_screen_loc.h = startchar->h;
	i = 0;
	len  = ft_strlen(str);
	while (i < len)
	{
		if (str[i] == ' ')
		{
			new_char_screen_loc.x += startchar->w / 3;
			i++;
		}
		font_char_loc = get_char_font_location(str[i]);
		SDL_RenderCopy(renderer, font, &font_char_loc, &new_char_screen_loc);
		new_char_screen_loc.x += startchar->w;
		i++;
	}
	return (GOOD);
}
