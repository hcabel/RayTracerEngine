/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uncompress_tga.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 11:03:56 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/24 15:08:40 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	fill_colormap(t_tga *file, unsigned char *new_data, int *i, int *j)
{
	int	again;

	again = (file->image_data[*j] & 0x7C) + 1;
	if (file->image_data[*j] & 0x80)
	{
		while (again)
		{
			fill_uncompresed_data(i, j, file->colormap.data, new_data,
				file->colormap.bpp);
			*i += 4;
			again--;
		}
		*j += (file->bpp >> 3);
	}
	else
	{
		while (again)
		{
			fill_uncompresed_data(i, j, file->colormap.data, new_data,
				file->colormap.bpp);
			*j += (file->bpp >> 3);
			again--;
		}
	}
	*j += 1;
}

static void	fill_data(t_tga *file, unsigned char *new_data, int *i, int *j)
{
	int	again;

	again = (file->image_data[*j] & 0x7F) + 1;
	if (file->image_data[*j] & 0x80)
	{
		*j += 1;
		while (again)
		{
			fill_uncompresed_data(i, j, file->image_data, new_data,
				file->bpp);
			*i += 4;
			again--;
		}
		*j += (file->bpp >> 3);
	}
	else
	{
		*j += 1;
		while (again)
		{
			fill_uncompresed_data(i, j, file->image_data, new_data,
				file->bpp);
			*i += 4;
			*j += (file->bpp >> 3);
			again--;
		}
	}
}

static int	uncompress(t_tga *file, unsigned char *new_data,
		void (*fill)(t_tga*, unsigned char *, int *, int *))
{
	int	again;
	int	length;
	int	i;
	int	j;

	again = 0;
	i = 0;
	j = 0;
	length = file->area.w * file->area.h * 4;
	while (i < length)
		fill(file, new_data, &i, &j);
	return (GOOD);
}

int			uncompress_tga(t_tga *file)
{
	unsigned char	*uncompressed_data;
	void			(*fill_func)(t_tga*, unsigned char*, int*, int*);

	uncompressed_data = NULL;
	if ((uncompressed_data = (unsigned char*)malloc(sizeof(unsigned char) * (
		file->area.w * file->area.h * file->bpp))) == NULL)
		return (MALLOC_ERROR);
	if (file->compression == 9)
		fill_func = fill_colormap;
	else
		fill_func = fill_data;
	if (uncompress(file, uncompressed_data, fill_func))
		return (TGA_UNCOPRESSION_ERROR);
	ft_memdel((void**)&file->image_data);
	file->image_data = uncompressed_data;
	return (GOOD);
}
