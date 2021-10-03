/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 23:55:07 by mamartin          #+#    #+#             */
/*   Updated: 2021/10/02 19:30:09 by mamartin         ###   ########.fr       */
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

void	put_pixel(t_image *screen, t_point pixel, int color)
{
	if (!is_in_screen(pixel))
		return ;
	screen->addr[pixel.x + pixel.y * (screen->size_line / BYTES_PER_PIXEL)]
		= color;
}
