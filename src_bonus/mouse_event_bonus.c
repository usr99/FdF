/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 01:54:22 by mamartin          #+#    #+#             */
/*   Updated: 2021/10/02 18:17:18 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	handle_buttonpress(int button, int x, int y, t_win *win)
{
	if (button == BUTTON_LEFT)
	{
		win->keys.button1 = TRUE;
		win->keys.cursor_button1.x = x;
		win->keys.cursor_button1.y = y;
	}
	else if (button == BUTTON_RIGHT)
	{
		win->keys.button2 = TRUE;
		win->keys.cursor_button2_x = x;
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
	if (button == BUTTON_LEFT)
	{
		win->keys.button1 = FALSE;
		win->keys.last_offset.x = win->grid.offset.x;
		win->keys.last_offset.y = win->grid.offset.y;
	}
	else if (button == BUTTON_RIGHT)
		win->keys.button2 = FALSE;
	return (0);
}

int	handle_pointer_motion(int x, int y, t_win *win)
{
	if (win->keys.button1)
	{
		win->grid.offset.x
			= win->keys.last_offset.x + x - win->keys.cursor_button1.x;
		win->grid.offset.y
			= win->keys.last_offset.y + y - win->keys.cursor_button1.y;
	}
	if (win->keys.button2)
	{
		win->grid.rot
			-= (x - win->keys.cursor_button2_x) * 2 * M_PI / MOUSE_SENSITIVITY;
		win->keys.cursor_button2_x = x;
	}
	return (0);
}
