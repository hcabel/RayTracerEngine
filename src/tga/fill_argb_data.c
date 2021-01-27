/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_argb_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 11:18:13 by hcabel            #+#    #+#             */
/*   Updated: 2021/01/27 13:41:21 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	convert_base_colormap_data(t_tga *file,
				unsigned char *converted_data)
{
	int			index;
	t_vector2d	double_index;

	double_index.x = 0;
	double_index.y = 0;
	index = 0;
	while (double_index.x < file->area.w * file->area.h * 4)
	{
		fill_uncompresed_data(double_index, file->colormap.data, converted_data,
			file->colormap.bpp);
		index++;
		double_index.x += 4;
		double_index.y += file->image_data[index] * (file->colormap.bpp >> 3);
	}
}

static void	convert_base_data(t_tga *file, unsigned char *converted_data)
{
	t_vector2d	index;
	int	j;

	index.x = 0;
	index.y = 0;
	while (index.x < file->area.w * file->area.h * 4)
	{
		fill_uncompresed_data(index, file->image_data, converted_data,
			file->bpp);
		index.x += 4;
		index.y += (file->bpp >> 3);
	}
}

int			convert_to_argb(t_tga *file)
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
