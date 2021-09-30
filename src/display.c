/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 18:10:37 by mamartin          #+#    #+#             */
/*   Updated: 2021/09/30 14:51:01 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	display_wireframe(t_map map)
{
	t_win	win;

	if (create_window(&win, map) == -1)
		return (-1);
	if (create_iso_grid(&win.grid, map) == -1)
		return (-1);
	refresh_display(&win);
	mlx_do_key_autorepeatoff(win.mlx);
	mlx_hook(win.window, 33, 0L, &exit_program_success, &win);
	mlx_hook(win.window, 2, 1L << 0, &handle_keypress, &win);
	mlx_hook(win.window, 3, 1L << 1, &handle_keyrelease, &win);
	mlx_loop_hook(win.mlx, &refresh_display, &win);
	mlx_loop(win.mlx);
	return (0);
}

int	create_window(t_win *win, t_map map)
{
	win->mlx = mlx_init();
	if (!win->mlx)
		return (-1);
	win->map = map;
	win->window = mlx_new_window(win->mlx, WIN_WIDTH, WIN_HEIGHT, "FdF");
	if (!win->window)
		return (-1);
	win->screen.img = mlx_new_image(win->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!win->screen.img)
		return (-1);
	win->screen.addr = (unsigned int *)mlx_get_data_addr(win->screen.img,
		&win->screen.bpp, &win->screen.size_line, &win->screen.endian);

	int	i;
	int	j;

	i = 255;
	j = 0;
	while (i >= 0)
	{
		win->gradient.shades[j] = 0xFFFF00 | i;
		i--;
		j++;
	}
	i = 255;
	while (i >= 0)
	{
		win->gradient.shades[j] = 0xFF0000 | i << 8;
		i--;
		j++;
	}
	
	i = 0;
	win->gradient.smallest_z = map.arr[0][0].z;
	win->gradient.biggest_z = win->gradient.smallest_z;
	while (i < map.y)
	{
		j = 0;
		while (j < map.x)
		{
			if (map.arr[i][j].z < win->gradient.smallest_z)
				win->gradient.smallest_z = map.arr[i][j].z;
			if (map.arr[i][j].z > win->gradient.biggest_z)
				win->gradient.biggest_z = map.arr[i][j].z;
			j++;
		}
		i++;
	}
	win->gradient.state = -1;
	ft_memset(&win->keys, FALSE, sizeof(t_keyhandle));

	return (0);
}

int	create_iso_grid(t_grid *grid, t_map map)
{
	grid->array = alloc_map(map.x, map.y);
	if (!grid->array)
		return (-1);
	if (map.x > map.y)
		grid->tilesize = WIN_WIDTH / map.x;
	else
		grid->tilesize = WIN_HEIGHT / map.y;

	grid->base.i.x = 0.5 * 1;
	grid->base.i.y = 0.25 * 1;
	grid->base.j.x = -0.5 * 1;
	grid->base.j.y = 0.25 * 1;
	
	grid->offset.x = 0;
	grid->offset.y = 0;
	grid->z_factor = Z_FACT_DEFAULT;
	refresh_iso_grid(grid, map);
	return (0);
}

void	to_iso_coordinates(t_grid *grid, t_map map)
{
	int i;
	int j;

	i = 0;
	while (i < map.y)
	{
		j = 0;
		while (j < map.x)
		{
			// iso distorsion
			grid->array[i][j].x
				= map.arr[i][j].x * grid->actual.i.x + map.arr[i][j].y * grid->actual.j.x;
			grid->array[i][j].y
				= map.arr[i][j].x * grid->actual.i.y + map.arr[i][j].y * grid->actual.j.y;

			// offset
			grid->array[i][j].x += grid->origin.x;
			grid->array[i][j].y += grid->origin.y;
 			
			// z axis
			grid->array[i][j].y -= map.arr[i][j].z * grid->tilesize * grid->z_factor;
			grid->array[i][j].z = map.arr[i][j].z;
			j++;
		}
		i++;
	}
}

void	draw(t_win *win)
{
	int i;
	int j;
	
	i = 0;
	while (i < win->map.y)
	{
		j = 0;
		while (j < win->map.x)
		{
			if (j != win->map.x - 1)
				draw_line(&win->screen, win->grid.array[i][j], win->grid.array[i][j+1], win->gradient);
			if (i != win->map.y - 1)
				draw_line(&win->screen, win->grid.array[i][j], win->grid.array[i+1][j], win->gradient);
			j++;
		}
		i++;
	}
}

void	draw_line(t_image *screen, t_point from, t_point to, t_gradient gradient)
{
	t_point	px;		// pixel à afficher
	t_point	delta; 	// différence entre le départ et l'arrivée de la droite
	t_point	dir;	// direction de la droite
	t_vect	err;	// erreur dûe à la pixellisation
	t_vect	err_init;
	int		i;

	px = from;
	err.x = abs(to.x - from.x);
	err.y = abs(to.y - from.y);
	delta.x = 2 * err.x;
	delta.y = 2 * err.y;

	dir.x = 1;
	dir.y = 1;

	if (from.x > to.x)
		dir.x = -1;
	if (from.y > to.y)
		dir.y = -1;

	err_init.x = err.x;
	err_init.y = err.y;

	int	color;
	int	range;
	int	index1;
	int	index2;
	int	dist;

	range = gradient.biggest_z - gradient.smallest_z;
	if (!range)
		range = 1;
	index1 = ((from.z - gradient.smallest_z) * 511) / range;
	index2 = ((to.z - gradient.smallest_z) * 511) / range;

	dist = index2 - index1;

	i = 0;
	color = 0xFFFFFF;
	if (err_init.x > err_init.y)
	{
		while (i <= err_init.x)
		{
			if (gradient.state == 1)
				color = gradient.shades[(int)(index1 + i * dist / err_init.x)];
			put_pixel(screen, px, color);
			err.x -= delta.y;
			if (err.x < 0)
			{
				px.y += dir.y;
				err.x += delta.x;
			}
			px.x += dir.x;
			i++;
		}		
	}
	else
	{
		while (i <= err_init.y)
		{
			if (gradient.state == 1)
				color = gradient.shades[(int)(index1 + i * dist / err_init.y)];
			put_pixel(screen, px, color);
			err.y -= delta.x;
			if (err.y < 0)
			{
				px.x += dir.x;
				err.y += delta.y;
			}
			px.y += dir.y;
			i++;
		}
	}
}

void	put_pixel(t_image *screen, t_point pixel, int color)
{
	if (pixel.x < 0 || pixel.x >= WIN_WIDTH || pixel.y < 0 || pixel.y >= WIN_HEIGHT)
		return ;
	screen->addr[pixel.x + pixel.y * (screen->size_line / 4)] = color;
}

void	refresh_iso_grid(t_grid *grid, t_map map)
{
	grid->actual.i.x = grid->base.i.x * grid->tilesize;
	grid->actual.i.y = grid->base.i.y * grid->tilesize;
	grid->actual.j.x = grid->base.j.x * grid->tilesize;
	grid->actual.j.y = grid->base.j.y * grid->tilesize;
	grid->size.x = map.x * grid->actual.i.x + map.y * grid->actual.j.x;
	grid->size.y = map.x * grid->actual.i.y + map.y * grid->actual.j.y;
	grid->origin.x = (WIN_WIDTH - grid->size.x) / 2 + grid->offset.x;
	grid->origin.y = (WIN_HEIGHT - grid->size.y) / 2 + grid->offset.y;
}

void	clear_screen(t_image *screen)
{
	int	i;
	int	nb_pixels;

	i = -1;
	nb_pixels = WIN_WIDTH * WIN_HEIGHT;
	while (i++ < nb_pixels)
		screen->addr[i] = 0;
}

int	refresh_display(t_win *win)
{
	for (int i = 0 ; i < 1500000 ; i++);
	handle_event(&win->grid, win->keys);
	refresh_iso_grid(&win->grid, win->map);
	to_iso_coordinates(&win->grid, win->map);
	clear_screen(&win->screen);
	draw(win);
	mlx_put_image_to_window(win->mlx, win->window, win->screen.img, 0, 0);
	return (0);
}
