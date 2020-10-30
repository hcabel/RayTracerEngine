/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_tga_contents.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 11:21:42 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/27 10:08:02 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <unistd.h>

static int	get_image_id_data(t_tga *file, int fd)
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

static int	get_colormap_data(t_colormap *colormap, int fd)
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

static int	get_image_data(t_tga *file, int fd)
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

int			setup_contents(t_tga *file, int fd)
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

int			read_header(t_tga *file, int fd)
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
