/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 23:55:03 by mamartin          #+#    #+#             */
/*   Updated: 2021/10/02 02:28:16 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	parse_file(int fd, t_map *map)
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
			map->arr[map->y - 1][i].color = get_color(row.array[i]);
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

int	get_color(char *str)
{
	char	*hexcode;
	int		color;
	int		i;

	hexcode = ft_strchr(str, ',');
	if (!hexcode)
		return (COLOR_WHITE);
	hexcode = ft_strnstr(hexcode, ",0x", 3);
	if (!hexcode)
		return (COLOR_WHITE);
	hexcode += 3;
	i = -1;
	while (hexcode[++i])
		hexcode[i] = ft_toupper(hexcode[i]);
	color = ft_atoi_base(hexcode, "0123456789ABCDEF");
	if (color)
		return (color);
	return (COLOR_WHITE);
}
