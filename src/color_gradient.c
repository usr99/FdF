/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_gradient.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 18:32:02 by mamartin          #+#    #+#             */
/*   Updated: 2021/10/02 23:00:39 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	create_gradient(t_win *win, t_map map)
{
	int	i;
	int	j;

	j = 0;
	i = GRADIENT_SIZE / 2 - 1;
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
	find_z_extremums(&win->gradient, map);
	win->gradient.state = -1;
}

void	find_z_extremums(t_gradient *grad, t_map map)
{
	int	i;
	int	j;

	i = 0;
	grad->smallest_z = map.arr[0][0].z;
	grad->biggest_z = grad->smallest_z;
	while (i < map.y)
	{
		j = 0;
		while (j < map.x)
		{
			if (map.arr[i][j].z < grad->smallest_z)
				grad->smallest_z = map.arr[i][j].z;
			if (map.arr[i][j].z > grad->biggest_z)
				grad->biggest_z = map.arr[i][j].z;
			j++;
		}
		i++;
	}
}

int	pick_color(t_line line, int i, double err, t_point px)
{
	if (line.color.gradient->state == 1)
	{
		if (err)
		{
			return (line.color.gradient->shades[(int)(line.color.from
					+ i * line.color.dist / err)]);
		}
		else
		{
			return (line.color.gradient->shades[(int)(line.color.from
					+ i * line.color.dist)]);
		}
	}
	return (px.color);
}
