/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 11:19:44 by hcabel            #+#    #+#             */
/*   Updated: 2020/11/05 12:22:29 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <fcntl.h>
#include <unistd.h>

static int	quit_reader(int error_code, int fd, t_tga *file)
{
	if (error_code != TGA_HEADER_PARSING_ERROR && error_code != TGA_PATH_ERROR)
	{
		ft_memdel((void**)&file->image_id);
		ft_memdel((void**)&file->image_data);
		ft_memdel((void**)&file->colormap.data);
	}
	close(fd);
	return (error_code);
}

static int	read_tga(char *path, t_tga *file)
{
	int	error_code;
	int	fd;

	if ((fd = open(path, O_RDONLY)) == -1)
		return (quit_reader(TGA_PATH_ERROR, fd, file));
	if (read_header(file, fd) != GOOD)
		return (quit_reader(TGA_HEADER_PARSING_ERROR, fd, file));
	if ((error_code = setup_contents(file, fd)) != GOOD)
		return (quit_reader(error_code, fd, file));
	if (file->compression > 8)
	{
		if (uncompress_tga(file) != GOOD)
			return (quit_reader(TGA_UNCOPRESSION_ERROR, fd, file));
	}
	else
		convert_to_argb(file);
	close(fd);
	return (GOOD);
}

t_tga		new_tga(char *path)
{
	int		code_error;
	t_tga	new_tga;

	if ((code_error = read_tga(path, &new_tga)) != GOOD)
	{
		if (code_error == TGA_HEADER_PARSING_ERROR
			|| code_error == TGA_CONTENT_PARSING_ERROR)
			ft_printf("{y}Tga : Pasing failed %s\n{/}", path);
		else if (code_error == TGA_PATH_ERROR)
			ft_printf("{y}Tga : Invalid path : %s\n{/}", path);
		else if (code_error == MALLOC_ERROR)
			ft_printf("{r}Tga : Malloc error you should restart !\n{/}");
		else
			ft_printf("{r}Tga : Unknown error, please report this %d !\n{/}", code_error);
		new_tga.parsed.bool = 0;
	}
	else
	{
		ft_printf("{g}Tga : load %s\n{/}", path);
		new_tga.parsed.bool = 1;
	}
	return (new_tga);
}

int			new_Image(SDL_Renderer *renderer, char *path, SDL_Texture **texture)
{
	t_tga		tga;
	SDL_Surface	*surface;

	tga = new_tga(path);
	if (tga.parsed.bool == 1)
	{
		surface = SDL_CreateRGBSurfaceWithFormatFrom(tga.image_data, tga.area.w,
			tga.area.h, 32, tga.area.w * 4, SDL_PIXELFORMAT_ARGB32);
		if (surface != NULL)
		{
			*texture = SDL_CreateTextureFromSurface(renderer, surface);
			SDL_FreeSurface(surface);
			ft_memdel((void**)&tga.image_data);
			return (GOOD);
		}
	}
	ft_memdel((void**)&tga.image_data);
	return (FAILED);
}
