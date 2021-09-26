/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 23:55:03 by mamartin          #+#    #+#             */
/*   Updated: 2021/09/26 18:11:57 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

char	parse_file(int fd, t_map *map)
{
	t_row	row;
	char	ret;
	int		i;

	ret = get_row(fd, &row);
	map->x = row.size;
	while (ret > 0)
	{
		if (realloc_map(map) == -1)
		{
			free_2d_array((void **)row.array, row.size);
			return (-1);
		}
		i = 0;
		while (i < row.size)
		{
			map->arr[map->y - 1][i] = ft_atoi(row.array[i]);
			i++;
		}
		free_2d_array((void **)row.array, row.size);
		ret = get_row(fd, &row);
	}
	free_2d_array((void **)row.array, row.size);
	if (ret == -1)
	{
		free_2d_array((void **)map->arr, map->y);
		return (-1);
	}
	return (0);
}

char	get_row(int fd, t_row *row)
{
	char	*line;
	char	ret;

	ret = get_next_line(fd, &line);
	if (ret == -1)
		return (ret);
	row->array = ft_split(line, ' ');
	free(line);
	if (!row->array)
		return (-1);
	row->size = 0;
	while (row->array[row->size])
		row->size++;
	return (ret);
}

char	realloc_map(t_map *map)
{
	int	**tmp;
	int	i;
	int	j;

	tmp = malloc(sizeof(int *) * (map->y + 1));
	if (!tmp)
		return (-1);
	i = -1;
	while (++i <= map->y)
	{
		tmp[i] = malloc(sizeof(int) * map->x);
		if (!tmp)
		{
			free_2d_array((void **)tmp, i);
			return (-1);
		}
		if (i != map->y)
		{
			j = -1;
			while (++j < map->x)
				tmp[i][j] = map->arr[i][j];
		}
	}
	free_2d_array((void **)map->arr, map->y);
	map->arr = tmp;
	map->y++;
	return (0);
}
