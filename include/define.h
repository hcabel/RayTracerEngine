/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 16:50:40 by hcabel            #+#    #+#             */
/*   Updated: 2020/12/31 19:17:27 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

/*
**	Editable define
*/
# define WINDOW_NAME "RayTracer Engine"
# define WIN_HEIGTH 900
# define WIN_WIDTH 1200

# define CPU_THREAD 20
# define ON_GPU 1
# define KERNELSOURCEFILE "src/raymarching/kernel_render.cl"

# define RAY_LOOP 100
# define FIRST_RESOLUTION 32
# define VIEW_DISTANCE 200
# define RAY_PRECIS 0.0005

/*
**	Interfaces editable define
*/
# define SCROLLBAR_SIZE 5
# define SCROLLBAR_COLOR 0x444444FF

# define BUTTON_COLOR 0x063547FF
# define BUTTON_HOVER_COLOR 0xEC3547FF
# define BUTTON_SELECTED_COLOR 0x0D6E94FF

# define TOP_PANEL_SIZE 50
# define TOP_PANEL_BUTTONS_MARGIN 4
# define TOP_PANEL_BACKGROUND_COLOR 0x1C1C22FF

# define LEFT_PANEL_SIZE 200
# define LEFT_PANEL_BUTTONS_MARGIN 5
# define LEFT_PANEL_BACKGROUND_COLOR 0x24242BFF

/*
**	Code understanding define
**	(Please don't touch)
*/
# define MAX_DRAWCALL 4
# define RAYMARCHING_THREAD (CPU_THREAD - 1)

# define FAILED -1
# define GOOD 0
# define UNKNOWN_ERROR 1
# define MALLOC_ERROR 2
# define SDL_ERROR 3
# define SDL_TEXTURE_CREATION_ERROR 4
# define O_THREAD_ERROR 5
# define TGA_PATH_ERROR 6
# define TGA_HEADER_PARSING_ERROR 7
# define TGA_CONTENT_PARSING_ERROR 8
# define TGA_FOOTER_PARSING_ERROR 9
# define TGA_UNCOMPRESSION_ERROR 10
# define KERNEL_SOURCE_LOAD_ERROR 11
# define KERNEL_PLATFORM_ERROR 12
# define KERNEL_CONTEXT_ERROR 13
# define KERNEL_COMMANDQUEUE_ERROR 14
# define KERNEL_BUFFER_ERROR 15
# define KERNEL_BUILD_ERROR 16
# define KERNEL_CREATION_ERROR 17
# define KERNEL_ENQUEUE_ERROR 18
# define KERNEL_ITEM_SIZE_ERROR 19
# define RESIZE_WINDOW_ERROR 20

# define DRAWCALL_CHECK_VIEWPORT drawcall_check_viewport
# define DRAWCALL_VIEWPORT drawcall_viewport
# define DRAWCALL_TOP_PANEL drawcall_top_panel
# define DRAWCALL_LEFT_PANEL drawcall_left_panel

# define VIEWMODE_BUTTON_AMOUNT 5
# define LAST_VIEWMODE_BUTTON (VIEWMODE_BUTTON_AMOUNT - 1)

// REMOVE
# define MAX_SOURCE_SIZE 0x100000

#endif