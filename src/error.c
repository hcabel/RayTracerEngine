/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 18:48:19 by hcabel            #+#    #+#             */
/*   Updated: 2021/02/04 14:43:40 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static char	*error_kernel_to_str(int code)
{
	if (code == KERNEL_SOURCE_LOAD_ERROR)
		return ("source file not found");
	if (code == KERNEL_PLATFORM_ERROR)
		return ("No plateform found");
	if (code == KERNEL_CONTEXT_ERROR)
		return ("Context error");
	if (code == KERNEL_COMMANDQUEUE_ERROR)
		return ("Commandequeue error");
	if (code == KERNEL_BUFFER_ERROR)
		return ("Buffer creation failed");
	if (code == KERNEL_BUILD_ERROR)
		return ("Kernel build failed");
	if (code == KERNEL_CREATION_ERROR)
		return ("Kernel creation failed");
	if (code == KERNEL_ENQUEUE_ERROR)
		return ("Enqueue error");
	if (code == KERNEL_ITEM_SIZE_ERROR)
		return ("Item size error");
	if (code == RESIZE_NOT_ALLOW)
		return ("I'm sorry but your OS do not support resizing");
	return ("");
}

static char	*error_tga_to_str(int code)
{
	if (code == TGA_PATH_ERROR)
		return ("not found");
	if (code == TGA_HEADER_PARSING_ERROR)
		return ("header parsing failed");
	if (code == TGA_CONTENT_PARSING_ERROR)
		return ("color parsing failed");
	if (code == TGA_FOOTER_PARSING_ERROR)
		return ("footer parsing failed");
	if (code == TGA_UNCOMPRESSION_ERROR)
		return ("file uncompression failed");
	if (code == PARSING_NO_HEADER)
		return ("first line isn't a header node");
	return ("");
}

char		*error_to_str(int code)
{
	char	*res;

	if (code == FAILED)
		return ("failed");
	if (code == GOOD)
		return ("good");
	if (code == UNKNOWN_ERROR)
		return ("Error unknown");
	if (code == MALLOC_ERROR)
		return ("malloc error");
	if (code == SDL_ERROR)
		return ("SDL error");
	if (code == SDL_TEXTURE_CREATION_ERROR)
		return ("allocating SDL_Texture failed");
	if (code == O_THREAD_ERROR)
		return ("no thread define in header file");
	if (code == RESIZE_WINDOW_ERROR)
		return ("new window size probably too small");
	if (code == BUTTON_FUNCTION_NOT_SET)
		return ("button clicked has no clicked function");
	if (ft_strlen(res = error_tga_to_str(code)) > 0)
		return (res);
	if (ft_strlen(res = error_kernel_to_str(code)) > 0)
		return (res);
	return ("ERROR CODE UNDEFINED");
}

int			is_fatal_error(int code)
{
	if (code == MALLOC_ERROR
		|| code == SDL_ERROR
		|| code == SDL_TEXTURE_CREATION_ERROR
		|| code == O_THREAD_ERROR
		|| code == UNKNOWN_ERROR)
		return (GOOD);
	return (FAILED);
}
