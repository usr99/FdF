/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 23:55:07 by mamartin          #+#    #+#             */
/*   Updated: 2021/10/01 04:24:46 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	exit_error(char *errmessage, char exit_code)
{
	write(2, errmessage, ft_strlen(errmessage));
	return (exit_code);
}

void	free_2d_array(void **array, int size)
{
	int	i;

	i = 0;
	if (size != -1)
	{
		while (i < size)
		{
			free(array[i]);
			i++;
		}
	}
	else
	{
		while (array[i])
		{
			free(array[i]);
			i++;
		}
	}
	free(array);
}

void	exit_program_code(t_win *win, char exit_code)
{
	free_2d_array((void **)win->map.arr, win->map.y);
	free_2d_array((void **)win->grid.array, win->map.y);
	mlx_destroy_image(win->mlx, win->screen.img);
	mlx_destroy_window(win->mlx, win->window);
	mlx_destroy_display(win->mlx);
	free(win->mlx);
	exit(exit_code);
}

int	exit_program_success(t_win *win)
{
	exit_program_code(win, EXIT_SUCCESS);
	return (0);
}

t_point	**alloc_map(int x, int y)
{
	t_point **array;
	int		i;

	i = 0;
	array = malloc(sizeof(t_point *) * y);
	if (!array)
		return (NULL);
	while (i < y)
	{
		array[i] = malloc(sizeof(t_point) * x);
		if (!array[i])
		{
			free_2d_array((void **)array, i);
			return (NULL);
		}
		i++;
	}
	return (array);
}

t_point	**copy_map(t_point **src, t_point **dest, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i < y)
	{
		j = 0;
		while (j < x)
		{
			dest[i][j] = src[i][j];
			j++;
		}
		i++;
	}
	return (dest);
}

int	realloc_map(t_map *map)
{
	t_point	**tmp;

	tmp = alloc_map(map->x, map->y + 1);
	if (!tmp)
		return (-1);
	tmp = copy_map(map->arr, tmp, map->x, map->y);
	free_2d_array((void **)map->arr, map->y);
	map->arr = tmp;
	map->y++;
	return (0);
}

int	is_in_screen(t_point p)
{
	if (p.x >= 0 && p.x < WIN_WIDTH && p.y >= 0 && p.y < WIN_HEIGHT)
		return (TRUE);
	return (FALSE);
}
