/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 18:38:28 by mamartin          #+#    #+#             */
/*   Updated: 2021/10/02 23:01:05 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	draw_line(t_image *screen, t_point from, t_point to, t_gradient *grad)
{
	t_line	line;

	if (!is_in_screen(from) && !is_in_screen(to))
		return ;
	line = init_line(from, to);
	line.color = init_line_color(from, to, grad);
	if (line.err_init.x > line.err_init.y)
		draw_line_1(screen, from, line);
	else
		draw_line_2(screen, from, line);
}

t_line	init_line(t_point from, t_point to)
{
	t_line	line;

	line.err.x = abs(to.x - from.x);
	line.err.y = abs(to.y - from.y);
	line.delta.x = 2 * line.err.x;
	line.delta.y = 2 * line.err.y;
	line.dir.x = 1;
	line.dir.y = 1;
	if (from.x > to.x)
		line.dir.x = -1;
	if (from.y > to.y)
		line.dir.y = -1;
	line.err_init.x = line.err.x;
	line.err_init.y = line.err.y;
	return (line);
}

t_line_color	init_line_color(t_point from, t_point to, t_gradient *gradient)
{
	t_line_color	color;

	color.range = gradient->biggest_z - gradient->smallest_z;
	if (!color.range)
		color.range = 1;
	color.from
		= ((from.z - gradient->smallest_z) * (GRADIENT_SIZE - 1)) / color.range;
	color.to
		= ((to.z - gradient->smallest_z) * (GRADIENT_SIZE - 1)) / color.range;
	color.dist = color.to - color.from;
	color.gradient = gradient;
	return (color);
}

void	draw_line_1(t_image *screen, t_point start, t_line line)
{
	int	color;
	int	i;

	i = 0;
	while (i <= line.err_init.x)
	{
		color = pick_color(line, i, line.err_init.x, start);
		put_pixel(screen, start, color);
		line.err.x -= line.delta.y;
		if (line.err.x < 0)
		{
			start.y += line.dir.y;
			line.err.x += line.delta.x;
		}
		start.x += line.dir.x;
		i++;
	}	
}

void	draw_line_2(t_image *screen, t_point start, t_line line)
{
	int		color;
	int		i;

	i = 0;
	while (i <= line.err_init.y)
	{
		color = pick_color(line, i, line.err_init.y, start);
		put_pixel(screen, start, color);
		line.err.y -= line.delta.x;
		if (line.err.y < 0)
		{
			start.x += line.dir.x;
			line.err.y += line.delta.y;
		}
		start.y += line.dir.y;
		i++;
	}
}
