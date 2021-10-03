/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 18:18:07 by mamartin          #+#    #+#             */
/*   Updated: 2021/10/02 19:30:02 by mamartin         ###   ########.fr       */
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

void	refresh_iso_grid(t_grid *grid, t_map map)
{
	grid->system.i.x = IVECT_X_DEFAULT * grid->tilesize * cos(grid->rot);
	grid->system.i.y = IVECT_Y_DEFAULT * grid->tilesize * sin(grid->rot);
	grid->system.j.x = JVECT_X_DEFAULT * grid->tilesize * sin(grid->rot);
	grid->system.j.y = JVECT_Y_DEFAULT * grid->tilesize * cos(grid->rot);
	grid->size.x = map.x * grid->system.i.x + map.y * grid->system.j.x;
	grid->size.y = map.x * grid->system.i.y + map.y * grid->system.j.y;
	grid->origin.x = (WIN_WIDTH - grid->size.x) / 2 + grid->offset.x;
	grid->origin.y = (WIN_HEIGHT - grid->size.y) / 2 + grid->offset.y;
}

int	refresh_display(t_win *win)
{
	handle_event(&win->grid, win->keys);
	refresh_iso_grid(&win->grid, win->map);
	to_iso_coordinates(&win->grid, win->map);
	clear_screen(&win->screen);
	draw(win);
	mlx_put_image_to_window(win->mlx, win->window, win->screen.img, 0, 0);
	return (0);
}

void	reset_display(t_win *win)
{
	win->grid.offset.x = 0;
	win->grid.offset.y = 0;
	win->grid.rot = ROTATION_DEFAULT;
	win->grid.z_factor = Z_FACT_DEFAULT;
	if (win->map.x > win->map.y)
		win->grid.tilesize = WIN_WIDTH / win->map.x;
	else
		win->grid.tilesize = WIN_HEIGHT / win->map.y;
}
