/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 21:29:42 by mamartin          #+#    #+#             */
/*   Updated: 2021/10/01 04:22:56 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	handle_keypress(int key, t_win *win)
{
	if (key == XK_KP_Add)
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
	if (key == XK_KP_Add)
		win->keys.kp_plus = FALSE;
	else if (key == XK_KP_Subtract)
		win->keys.kp_minus = FALSE;
	return (0);
}

int	handle_buttonpress(int button, int x, int y, t_win *win)
{
	if (button == BUTTON_LEFT)
	{
		win->keys.button1 = TRUE;
		win->keys.cursor.x = x;
		win->keys.cursor.y = y;
	}
	else if (button == WHEEL_UP)
		zoom(&win->grid, IN);
	else if (button == WHEEL_DOWN)
		zoom(&win->grid, OUT);
	return (0);
}

int	handle_buttonrelease(int button, int x, int y, t_win *win)
{
	(void)x;
	(void)y;
	if (button == 1)
	{
		win->keys.button1 = FALSE;
		win->keys.last_offset.x = win->grid.offset.x;
		win->keys.last_offset.y = win->grid.offset.y;
	}
	return (0);
}

int	handle_pointer_motion(int x, int y, t_win *win)
{
	if (win->keys.button1)
	{
		win->grid.offset.x = win->keys.last_offset.x + x - win->keys.cursor.x;
		win->grid.offset.y = win->keys.last_offset.y + y - win->keys.cursor.y;
	}
	return (0);
}

void	handle_event(t_grid *grid, t_keyhandle key_info)
{
	if (key_info.kp_plus)
		z_factor(grid, Z_FACT_INCR);
	if (key_info.kp_minus)
		z_factor(grid, -Z_FACT_INCR);
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
