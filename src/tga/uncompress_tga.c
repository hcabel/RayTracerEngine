/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uncompress_tga.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 11:03:56 by hcabel            #+#    #+#             */
/*   Updated: 2021/02/04 11:33:20 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	fill_colormap(t_tga *file, unsigned char *new_data, t_vector2d *i)
{
	int	again;

	again = (file->image_data[(int)i->y] & 0x7C) + 1;
	if (file->image_data[(int)i->y] & 0x80)
	{
		while (again)
		{
			fill_uncompresed_data(*i, file->colormap.data, new_data,
				file->colormap.bpp);
			i->x += 4;
			again--;
		}
		i->y += (int)(file->bpp >> 3);
	}
	else
	{
		while (again)
		{
			fill_uncompresed_data(*i, file->colormap.data, new_data,
				file->colormap.bpp);
			i->y += (int)(file->bpp >> 3);
			again--;
		}
	}
	i->y += 1;
}

static void	fill_data(t_tga *file, unsigned char *new_data, t_vector2d *i)
{
	int	again;

	again = (file->image_data[(int)i->y] & 0x7F) + 1;
	if (file->image_data[(int)i->y] & 0x80)
	{
		i->y += 1;
		while (again)
		{
			fill_uncompresed_data(*i, file->image_data, new_data, file->bpp);
			i->x += 4;
			again--;
		}
		i->y += (file->bpp >> 3);
	}
	else
	{
		i->y += 1;
		while (again)
		{
			fill_uncompresed_data(*i, file->image_data, new_data, file->bpp);
			i->x += 4;
			i->y += (file->bpp >> 3);
			again--;
		}
	}
}

static int	uncompress(t_tga *file, unsigned char *new_data,
		void (*fill)(t_tga*, unsigned char*, t_vector2d*))
{
	int			length;
	t_vector2d	index;

	index.x = 0;
	index.y = 0;
	length = file->area.w * file->area.h * 4;
	while (index.x < length)
		fill(file, new_data, &index);
	return (GOOD);
}

int			uncompress_tga(t_tga *file)
{
	unsigned char	*uncompressed_data;

	uncompressed_data = (unsigned char*)malloc(sizeof(unsigned char)
			* (file->area.w * file->area.h * file->bpp));
	if (uncompressed_data == NULL)
		return (MALLOC_ERROR);
	if (file->compression == 9)
	{
		if (uncompress(file, uncompressed_data, fill_colormap))
			return (TGA_UNCOMPRESSION_ERROR);
	}
	else
	{
		if (uncompress(file, uncompressed_data, fill_data))
			return (TGA_UNCOMPRESSION_ERROR);
	}
	ft_memdel((void**)&file->image_data);
	file->image_data = uncompressed_data;
	return (GOOD);
}
