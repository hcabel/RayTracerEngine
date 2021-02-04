/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 16:50:40 by hcabel            #+#    #+#             */
/*   Updated: 2021/02/04 15:32:59 by hcabel           ###   ########.fr       */
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

# define RAYMARCHING_THREAD 1
# define ON_GPU 0
# define KERNELSOURCEFILE "src/raymarching/kernel_render.cl"

# define RAY_LOOP 100
# define FIRST_RESOLUTION 32
# define VIEW_DISTANCE 200
# define DISTANCE_FOG_COLOR 0x0
# define RAY_PRECIS 0.0005

# define FOG_START 0.5
# define KS 1.0
# define KD 0.7
# define KA 0.2

# define ABLE_TO_RESIZE 0

/*
**	Interfaces editable define
*/
# define SCROLLBAR_SIZE 5
# define SCROLLBAR_COLOR 0x444444FF

# define BUTTON_COLOR 0x063547FF
# define BUTTON_HOVER_COLOR 0xEC3547FF
# define BUTTON_SELECTED_COLOR 0x0D6E94FF

# define BUTTON_SWITCH_COLOR_ON 0x54FF7CFF
# define BUTTON_SWITCH_COLOR_OFF 0xBABABAFF

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

# define GOOD 0
# define FAILED -1
# define UNKNOWN_ERROR -2
# define MALLOC_ERROR -3
# define SDL_ERROR -4
# define SDL_TEXTURE_CREATION_ERROR -5
# define O_THREAD_ERROR -6
# define TGA_PATH_ERROR -7
# define TGA_HEADER_PARSING_ERROR -8
# define TGA_CONTENT_PARSING_ERROR -9
# define TGA_FOOTER_PARSING_ERROR -10
# define TGA_UNCOMPRESSION_ERROR -11
# define KERNEL_SOURCE_LOAD_ERROR -12
# define KERNEL_PLATFORM_ERROR -13
# define KERNEL_CONTEXT_ERROR -14
# define KERNEL_COMMANDQUEUE_ERROR -15
# define KERNEL_BUFFER_ERROR -16
# define KERNEL_BUILD_ERROR -17
# define KERNEL_CREATION_ERROR -18
# define KERNEL_ENQUEUE_ERROR -19
# define KERNEL_ITEM_SIZE_ERROR -20
# define RESIZE_WINDOW_ERROR -21
# define BUTTON_FUNCTION_NOT_SET -22
# define PARSING_NO_HEADER -23
# define RESIZE_NOT_ALLOW -24

# define GAME_VIEWMODE 0
# define EDITOR_VIEWMODE 1
# define UNLIT_VIEWMODE 2
# define ITERATION_VIEWMODE 3
# define NORMAL_VIEWMODE 4
# define DIRECT_ILLUMINATION_VIEWMODE 5
# define DISTANCE_FOG_VIEWMODE 8
/*
**	TODO
*/
# define GLOSSY_ILLUMINATION_VIEWMODE 6
# define GLOBAL_ILLUMINATION_VIEWMODE 7

# define DRAWCALL_CHECK_VIEWPORT drawcall_check_viewport
# define DRAWCALL_VIEWPORT drawcall_viewport
# define DRAWCALL_TOP_PANEL drawcall_top_panel
# define DRAWCALL_LEFT_PANEL drawcall_left_panel

# define VIEWMODE_BUTTON_AMOUNT 9

# define TOP_PANEL_ICON_AMOUNT 2

#endif
