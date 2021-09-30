/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 23:55:03 by mamartin          #+#    #+#             */
/*   Updated: 2021/09/29 20:15:56 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	check_filename(char *filename)
{
	size_t	len;
	char	*str;

	str = ft_strrchr(filename, '/');
	if (!str)
		str = filename + 1;
	else
		str++;
	len = ft_strlen(str);
	if (len < 5)
		return (2);
	else if (ft_strncmp(str + len - 4, ".fdf", 4) != 0)
		return (2);
	return (0);
}

int		parse_file(int fd, t_map *map)
{
	t_row	row;
	int		ret;
	int		i;

	ret = get_row(fd, &row);
	map->x = row.size;
	while (row.size != 0 && row.size == map->x)
	{
		if (realloc_map(map) == -1)
		{
			free_2d_array((void **)row.array, row.size);
			return (-1);
		}
		i = 0;
		while (i < row.size)
		{
			map->arr[map->y - 1][i].x = i;
			map->arr[map->y - 1][i].y = map->y - 1;
			map->arr[map->y - 1][i].z = ft_atoi(row.array[i]);
			i++;
		}
		free_2d_array((void **)row.array, row.size);
		ret = get_row(fd, &row);
	}
	free_2d_array((void **)row.array, row.size);
	if (ret == -1 || (row.size != 0 && row.size != map->x))
	{
		free_2d_array((void **)map->arr, map->y);
		if (ret == -1)
			return (-1);
		else
			return (2);
	}
	return (0);
}

int	get_row(int fd, t_row *row)
{
	char	*line;
	int		ret;

	row->size = 0;
	ret = get_next_line(fd, &line);
	if (ret == -1)
		return (ret);
	row->array = ft_split(line, ' ');
	free(line);
	if (!row->array)
		return (-1);
	while (row->array[row->size])
		row->size++;
	return (ret);
}
