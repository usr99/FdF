/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 18:18:07 by mamartin          #+#    #+#             */
/*   Updated: 2021/10/03 19:15:12 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	clear_screen(t_image *screen)
{
	int	i;
	int	nb_pixels;

	i = -1;
	nb_pixels = WIN_WIDTH * WIN_HEIGHT;
	while (i++ < nb_pixels)
		screen->addr[i] = 0;
}

int	is_in_screen(t_point p)
{
	if (p.x >= 0 && p.x < WIN_WIDTH && p.y >= 0 && p.y < WIN_HEIGHT)
		return (TRUE);
	return (FALSE);
}

int	refresh_display(t_win *win)
{
	clear_screen(&win->screen);
	draw(win);
	mlx_put_image_to_window(win->mlx, win->window, win->screen.img, 0, 0);
	return (0);
}
