/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 21:29:42 by mamartin          #+#    #+#             */
/*   Updated: 2021/09/30 14:49:01 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	handle_keypress(int key, t_win *win)
{
	if (key == XK_z)
		win->keys.z = TRUE;
	else if (key == XK_s)
		win->keys.s = TRUE;
	else if (key == XK_q)
		win->keys.q = TRUE;
	else if (key == XK_d)
		win->keys.d = TRUE;
	else if (key == XK_a)
		win->keys.a = TRUE;
	else if (key == XK_e)
		win->keys.e = TRUE;
	else if (key == XK_KP_Add)
		win->keys.kp_plus = TRUE;
	else if (key == XK_KP_Subtract)
		win->keys.kp_minus = TRUE;
	else if (key == XK_c)
		win->gradient.state *= -1;
	else if (key == XK_r)
		reset_display(win);
	else if (key == XK_Escape)
		exit_program_success(win);
	return (0);
}

int	handle_keyrelease(int key, t_win *win)
{
	if (key == XK_z)
		win->keys.z = FALSE;
	else if (key == XK_s)
		win->keys.s = FALSE;
	else if (key == XK_q)
		win->keys.q = FALSE;
	else if (key == XK_d)
		win->keys.d = FALSE;
	else if (key == XK_a)
		win->keys.a = FALSE;
	else if (key == XK_e)
		win->keys.e = FALSE;
	else if (key == XK_KP_Add)
		win->keys.kp_plus = FALSE;
	else if (key == XK_KP_Subtract)
		win->keys.kp_minus = FALSE;
	return (0);
}

void	handle_event(t_grid *grid, t_keyhandle key_info)
{
	if (key_info.z)
		translate(&grid->offset.y, UP, MAX_TRANSLATION_Y);
	if (key_info.q)
		translate(&grid->offset.x, LEFT, MAX_TRANSLATION_X);
	if (key_info.s)
		translate(&grid->offset.y, DOWN, MAX_TRANSLATION_Y);
	if (key_info.d)
		translate(&grid->offset.x, RIGHT, MAX_TRANSLATION_X);
	if (key_info.a)
		z_factor(grid, -Z_FACT_INCR);
	if (key_info.e)
		z_factor(grid, Z_FACT_INCR);
	if (key_info.kp_plus)
		zoom(grid, IN);
	if (key_info.kp_minus)
		zoom(grid, OUT);
}

void	reset_display(t_win *win)
{
	win->grid.offset.x = 0;
	win->grid.offset.y = 0;
	win->grid.z_factor = Z_FACT_DEFAULT;
	if (win->map.x > win->map.y)
		win->grid.tilesize = WIN_WIDTH / win->map.x;
	else
		win->grid.tilesize = WIN_HEIGHT / win->map.y;
}
