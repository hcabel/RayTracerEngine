/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 11:19:44 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/24 13:53:10 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <fcntl.h>
#include <unistd.h>

int		quit_reader(int error_code, int fd, t_tga *file)
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

int		read_header(t_tga *file, int fd)
{
	unsigned char	buffer[18];

	if (read(fd, &buffer, 18) != 18)
		return (FAILED);
	file->id_length = buffer[0];
	file->datatype = buffer[1];
	file->compression = buffer[2];
	file->colormap.entry_index = buffer[3] + (buffer[4] << 8);
	file->colormap.length = buffer[5] + (buffer[6] << 8);
	file->colormap.bpp = buffer[7];
	file->area.x = buffer[8] + (buffer[9] << 8);
	file->area.y = buffer[10] + (buffer[11] << 8);
	file->area.w = buffer[12] + (buffer[13] << 8);
	file->area.h = buffer[14] + (buffer[15] << 8);
	file->bpp = buffer[16];
	file->descriptor = buffer[17];
	return (GOOD);
}

int		get_image_id_data(t_tga *file, int fd)
{
	if (file->id_length <= 0)
		return (GOOD);
	if ((file->image_id = (unsigned char*)malloc(sizeof(unsigned char)
		* file->id_length)) == NULL)
		return (MALLOC_ERROR);
	if (read(fd, file->image_id, file->id_length) != file->id_length)
		return (TGA_CONTENT_PARSING_ERROR);
	return (GOOD);
}

int		get_colormap_data(t_colormap *colormap, int fd)
{
	if (colormap->length <= 0)
		return (GOOD);
	if ((colormap->data = (unsigned char*)malloc(sizeof(unsigned char)
		* colormap->length)) == NULL)
		return (MALLOC_ERROR);
	if (read(fd, colormap->data, colormap->length) != colormap->length)
		return (TGA_CONTENT_PARSING_ERROR);
	return (GOOD);
}

int		get_image_data(t_tga *file, int fd)
{
	unsigned int	bpp_size;

	bpp_size =  ((file->bpp >> 3) + (file->compression > 8 ? 1 : 0));
	if ((file->image_data = (unsigned char*)malloc(sizeof(unsigned char) *
		file->area.w * file->area.h * bpp_size)) == NULL)
		return (MALLOC_ERROR);
	if (file->compression < 8)
	{
		if (read(fd, file->image_data, file->area.w * file->area.h * bpp_size) !=
			file->area.w * file->area.h * bpp_size)
			return (TGA_CONTENT_PARSING_ERROR);
	}
	else
		read(fd, file->image_data, file->area.w * file->area.h * bpp_size);
	return (GOOD);
}

int		setup_contents(t_tga *file, int fd)
{
	int	error_code;

	file->image_data = NULL;
	file->colormap.data = NULL;
	file->image_id = NULL;
	if ((error_code = get_image_id_data(file, fd)) != GOOD)
		return (error_code);
	if ((error_code = get_colormap_data(&file->colormap, fd)) != GOOD)
		return (error_code);
	if ((error_code = get_image_data(file, fd)) != GOOD)
		return (error_code);
	return (GOOD);
}

void	convert_base_colormap_data(t_tga *file, unsigned char *converted_data)
{
	int	index;
	int	i;
	int	j;

	i = 0;
	j = 0;
	index = 0;
	while (i < file->area.w * file->area.h * 4)
	{
		fill_uncompresed_data(&i, &j, file->colormap.data, converted_data,
			file->colormap.bpp);
		index++;
		i += 4;
		j += file->image_data[index] * (file->colormap.bpp >> 3);
	}
}

void	convert_base_data(t_tga *file, unsigned char *converted_data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < file->area.w * file->area.h * 4)
	{
		fill_uncompresed_data(&i, &j, file->image_data, converted_data,
			file->bpp);
		i += 4;
		j += (file->bpp >> 3);
	}
}

int		convert_to_argb(t_tga *file)
{
	unsigned char	*converted_data;

	converted_data = NULL;
	if ((converted_data = (unsigned char*)malloc(sizeof(unsigned char) * (
		file->area.w * file->area.h * 4))) == NULL)
		return (MALLOC_ERROR);
	if (file->compression == 2 || file->compression == 3)
		convert_base_data(file, converted_data);
	else
		convert_base_colormap_data(file, converted_data);
	ft_memdel((void**)&file->image_data);
	file->image_data = converted_data;
	return (GOOD);
}

int		read_tga(char *path, t_tga *file)
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

t_tga	new_tga(char *path)
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

int		new_Image(SDL_Renderer *renderer, char *path, SDL_Texture **texture)
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
			return (GOOD);
		}
	}
	return (FAILED);
}
