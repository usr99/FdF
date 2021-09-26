/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 18:10:37 by mamartin          #+#    #+#             */
/*   Updated: 2021/09/26 19:32:58 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

char	display_wireframe(t_map map)
{
	t_win	win;

	if (create_window(&win, map) == -1)
		return (-1);

	if (create_iso_grid(&win) == -1)
		return (-1);

	refresh(&win);
	mlx_loop(win.mlx);
	return (0);
}

char	create_window(t_win *win, t_map map)
{
	win->mlx = mlx_init();
	if (!win->mlx)
		return (-1);
	win->map = map;
	win->window = mlx_new_window(win->mlx, WIN_WIDTH, WIN_HEIGHT, "FdF");
	if (!win->window)
		return (-1);
	return (0);
}

char	create_iso_grid(t_win *win)
{
	win->screen.img = mlx_new_image(win->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!win->screen.img)
		return (-1);
	win->screen.addr = (unsigned int *)mlx_get_data_addr(win->screen.img,
		&win->screen.bpp, &win->screen.size_line, &win->screen.endian);

	int	grid_size = ((80 * WIN_WIDTH) / 100) / win->map.x;

	t_point	p1;
	t_point	p2;

	p1.x = 20 * 1;
	p1.y = 20 * 1;

	p2.x = (20 + grid_size * 1);
	p2.y = 20 * 0.5;

	draw_line(&win->screen, p1, p2);

	return (0);
}

void	draw_line(t_image *screen, t_point from, t_point to)
{
	t_vect	d;
	double	m;
	t_point	px;

	d.x = abs(to.x - from.x);
	d.y = abs(to.y - from.y);
	m = d.y / d.x;

	px.x = from.x;
	px.y = 0;

	while (px.x <= to.x && px.y < WIN_HEIGHT)
	{
		px.y = m*px.x + from.y;
		put_pixel(screen, px);
		px.x++;
	}
}

void	put_pixel(t_image *screen, t_point pixel)
{
	screen->addr[pixel.x + pixel.y * (screen->size_line / 4)] = 0x58FF22;
}

void	refresh(t_win *win)
{
	mlx_put_image_to_window(win->mlx, win->window, win->screen.img, 0, 0);
}