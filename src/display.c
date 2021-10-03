/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 18:10:37 by mamartin          #+#    #+#             */
/*   Updated: 2021/10/03 19:21:49 by mamartin         ###   ########.fr       */
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
	mlx_do_key_autorepeatoff(win.mlx);
	mlx_hook(win.window, ClientMessage, 0L, &exit_program_success, &win);
	mlx_hook(win.window, KeyPress, 1L, &handle_keypress, &win);
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
	grid->system.i.x = IVECT_X_DEFAULT * grid->tilesize * cos(grid->rot);
	grid->system.i.y = IVECT_Y_DEFAULT * grid->tilesize * sin(grid->rot);
	grid->system.j.x = JVECT_X_DEFAULT * grid->tilesize * sin(grid->rot);
	grid->system.j.y = JVECT_Y_DEFAULT * grid->tilesize * cos(grid->rot);
	grid->size.x = map.x * grid->system.i.x + map.y * grid->system.j.x;
	grid->size.y = map.x * grid->system.i.y + map.y * grid->system.j.y;
	grid->origin.x = (WIN_WIDTH - grid->size.x) / 2 + grid->offset.x;
	grid->origin.y = (WIN_HEIGHT - grid->size.y) / 2 + grid->offset.y;
	to_iso_coordinates(grid, map);
	return (0);
}

void	to_iso_coordinates(t_grid *grid, t_map map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map.y)
	{
		j = 0;
		while (j < map.x)
		{
			grid->array[i][j].x
				= map.arr[i][j].x * grid->system.i.x
				+ map.arr[i][j].y * grid->system.j.x;
			grid->array[i][j].y
				= map.arr[i][j].x * grid->system.i.y
				+ map.arr[i][j].y * grid->system.j.y;
			grid->array[i][j].x += grid->origin.x;
			grid->array[i][j].y += grid->origin.y;
			grid->array[i][j].y
				-= map.arr[i][j].z * grid->tilesize * grid->z_factor;
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
			{
				draw_line(&win->screen, win->grid.array[i][j],
					win->grid.array[i][j + 1], &win->gradient);
			}
			if (i != win->map.y - 1)
			{
				draw_line(&win->screen, win->grid.array[i][j],
					win->grid.array[i + 1][j], &win->gradient);
			}
			j++;
		}
		i++;
	}
}
