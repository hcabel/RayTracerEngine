/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 11:19:44 by hcabel            #+#    #+#             */
/*   Updated: 2021/02/04 12:14:03 by hcabel           ###   ########.fr       */
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

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (quit_reader(TGA_PATH_ERROR, fd, file));
	if (read_header(file, fd) != GOOD)
		return (quit_reader(TGA_HEADER_PARSING_ERROR, fd, file));
	error_code = setup_contents(file, fd);
	if (error_code != GOOD)
		return (quit_reader(error_code, fd, file));
	if (file->compression > 8)
	{
		if (uncompress_tga(file) != GOOD)
			return (quit_reader(TGA_UNCOMPRESSION_ERROR, fd, file));
	}
	else
		convert_to_argb(file);
	close(fd);
	return (GOOD);
}

t_tga	new_tga(char *path)
{
	int		code_error;
	t_tga	new_tga;

	code_error = read_tga(path, &new_tga);
	if (code_error != GOOD)
	{
		if (code_error == TGA_HEADER_PARSING_ERROR
			|| code_error == TGA_CONTENT_PARSING_ERROR)
			ft_printf("{y}		Pasing failed %s\n{/}", path);
		else if (code_error == TGA_PATH_ERROR)
			ft_printf("{y}		Invalid path : %s\n{/}", path);
		else if (code_error == MALLOC_ERROR)
			ft_printf("{r}		Malloc error you should restart !\n{/}");
		else
			ft_printf("{r}		Unknown error, %d !\n{/}", code_error);
		new_tga.parsed = 0;
	}
	else
	{
		ft_printf("{g}		load %s\n{/}", path);
		new_tga.parsed = 1;
	}
	return (new_tga);
}

int	new_tga_image(SDL_Renderer *renderer, char *path, SDL_Texture **texture)
{
	t_tga		tga;
	SDL_Surface	*surface;

	tga = new_tga(path);
	if (tga.parsed == 1)
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
		ft_memdel((void**)&tga.image_data);
	}
	return (FAILED);
}
