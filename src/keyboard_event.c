/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_event.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 21:29:42 by mamartin          #+#    #+#             */
/*   Updated: 2021/10/02 01:55:14 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	handle_event(t_grid *grid, t_keyhandle key_info)
{
	if (key_info.a)
		rotate(&grid->rot, ROTATION_INCR);
	if (key_info.d)
		rotate(&grid->rot, -ROTATION_INCR);
	if (key_info.kp_plus)
		z_factor(grid, Z_FACT_INCR);
	if (key_info.kp_minus)
		z_factor(grid, -Z_FACT_INCR);
}

int	handle_keypress(int key, t_win *win)
{
	if (key == XK_a)
		win->keys.a = TRUE;
	else if (key == XK_d)
		win->keys.d = TRUE;
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
	if (key == XK_a)
		win->keys.a = FALSE;
	else if (key == XK_d)
		win->keys.d = FALSE;
	else if (key == XK_KP_Add)
		win->keys.kp_plus = FALSE;
	else if (key == XK_KP_Subtract)
		win->keys.kp_minus = FALSE;
	return (0);
}
