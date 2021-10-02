/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 18:10:37 by mamartin          #+#    #+#             */
/*   Updated: 2021/10/02 02:15:24 by mamartin         ###   ########.fr       */
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
	mlx_hook(win.window, ClientMessage, 0L, &exit_program_success, &win);
	mlx_hook(win.window, KeyPress, 1L, &handle_keypress, &win);
	mlx_hook(win.window, KeyRelease, 1L << 1, &handle_keyrelease, &win);
	mlx_hook(win.window, ButtonPress, 1L << 2, &handle_buttonpress, &win);
	mlx_hook(win.window, ButtonRelease, 1L << 3, &handle_buttonrelease, &win);
	mlx_hook(win.window, MotionNotify, 1L << 6, &handle_pointer_motion, &win);
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

	i = GRADIENT_SIZE / 2 - 1;
	j = 0;
	while (i >= 0)
	{
		win->gradient.shades[j] = COLOR_YELLOW | i;
		i--;
		j++;
	}
	i = GRADIENT_SIZE / 2 - 1;
	while (i >= 0)
	{
		win->gradient.shades[j] = COLOR_RED | i << 8;
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
	win->keys.offset_button1.x = 0;
	win->keys.offset_button1.y = 0;
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

	grid->rot = ROTATION_DEFAULT;
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
				= map.arr[i][j].x * grid->system.i.x + map.arr[i][j].y * grid->system.j.x;
			grid->array[i][j].y
				= map.arr[i][j].x * grid->system.i.y + map.arr[i][j].y * grid->system.j.y;

			// offset
			grid->array[i][j].x += grid->origin.x;
			grid->array[i][j].y += grid->origin.y;
 			
			// z axis
			grid->array[i][j].y -= map.arr[i][j].z * grid->tilesize * grid->z_factor;
			grid->array[i][j].z = map.arr[i][j].z;

			grid->array[i][j].color = map.arr[i][j].color;
			j++;
		}
		i++;
	}
}

void	draw(t_win *win)
{
	int	i;
	int	j;

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

	if (!is_in_screen(from) && !is_in_screen(to))
		return ;

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
	index1 = ((from.z - gradient.smallest_z) * (GRADIENT_SIZE - 1)) / range;
	index2 = ((to.z - gradient.smallest_z) * (GRADIENT_SIZE - 1)) / range;

	dist = index2 - index1;

	i = 0;
	color = from.color;
	if (err_init.x > err_init.y)
	{
		while (i <= err_init.x)
		{
			if (gradient.state == 1)
			{
				if (err_init.x)
					color = gradient.shades[(int)(index1 + i * dist / err_init.x)];
				else
					color = gradient.shades[(int)(index1 + i * dist / 1)];
			}
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
			{
				if (err_init.y)
					color = gradient.shades[(int)(index1 + i * dist / err_init.y)];
				else
					color = gradient.shades[(int)(index1 + i * dist / 1)];
			}
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
	if (!is_in_screen(pixel))
		return ;
	screen->addr[pixel.x + pixel.y * (screen->size_line / BYTES_PER_PIXEL)] = color;
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
