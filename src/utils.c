/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 23:55:07 by mamartin          #+#    #+#             */
/*   Updated: 2021/09/26 18:17:55 by mamartin         ###   ########.fr       */
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

void	free_all(t_win *win)
{
	free_2d_array((void **)win->map.arr, win->map.y);
	mlx_destroy_window(win->mlx, win->window);
	mlx_destroy_display(win->mlx);
	free(win->mlx);
}
