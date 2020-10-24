/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_uncompressed_data.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 11:54:30 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/24 12:33:04 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	bpp32(unsigned char *original, unsigned char *new_data,
		int i, int j)
{
	new_data[i] = original[j + 3];
	new_data[i + 1] = original[j + 2];
	new_data[i + 2] = original[j + 1];
	new_data[i + 3] = original[j];
}

static void	bpp24(unsigned char *original, unsigned char *new_data,
		int i, int j)
{
	new_data[i] = 255;
	new_data[i + 1] = original[j + 2];
	new_data[i + 2] = original[j + 1];
	new_data[i + 3] = original[j];
}

static void	bpp16(unsigned char *original, unsigned char *new_data,
		int i, int j)
{
	new_data[i] = (new_data[j] & 0x80) != 0 ? 255 : 255;
	new_data[i + 1] = ((((new_data[j + 1] & 0x7C) >> 2) * 255) / 31);
	new_data[i + 2] = ((new_data[j + 1] & 0x03) << 3);
	new_data[i + 2] += ((new_data[j] & 0xE0) >> 5);
	new_data[i + 3] = (((new_data[j] & 0x1F) * 255) / 31);
	new_data[i + 2] *= 255 / 31;
}

static void	bpp8(unsigned char *original, unsigned char *new_data,
		int i, int j)
{
	new_data[i] = ((original[j] & 0x80) != 0 ? 0 : 255);
	new_data[i + 1] = original[j] & 0x7F;
	new_data[i + 2] = original[j] & 0x7F;
	new_data[i + 3] = original[j] & 0x7F;
}

void		fill_uncompresed_data(int *i, int *j, unsigned char *original,
				unsigned char *new_data, int bpp)
{
	if (bpp == 32)
		bpp32(original, new_data, *i, *j);
	else if (bpp == 24)
		bpp24(original, new_data, *i, *j);
	else if (bpp == 16)
		bpp16(original, new_data, *i, *j);
	else
		bpp8(original, new_data, *i, *j);
}