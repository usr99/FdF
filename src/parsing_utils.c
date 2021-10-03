/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 19:28:34 by mamartin          #+#    #+#             */
/*   Updated: 2021/10/03 02:53:27 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

t_point	**alloc_map(int x, int y)
{
	t_point	**array;
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

int	finish_reading(int fd, char **line)
{
	while (get_next_line(fd, line) > 0)
		free(*line);
	free(*line);
	return (2);
}
