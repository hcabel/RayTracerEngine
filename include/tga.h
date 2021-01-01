/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 16:54:57 by hcabel            #+#    #+#             */
/*   Updated: 2020/12/31 14:18:29 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TGA_H
# define TGA_H

# include "SDL.h"

typedef struct			s_colormap
{
	unsigned char		*data;
	int					entry_index;
	int					length;
	int					bpp;
}						t_colormap;

typedef struct			s_tga
{
	int					parsed;
	unsigned char		*image_id;
	unsigned char		*image_data;
	int					id_length;
	int					datatype;
	int					compression;
	t_colormap			colormap;
	SDL_Rect			area;
	int					bpp;
	int					descriptor;
}						t_tga;

#endif