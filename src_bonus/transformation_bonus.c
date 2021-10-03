/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 00:38:50 by mamartin          #+#    #+#             */
/*   Updated: 2021/10/01 23:22:58 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	rotate(double *rot, double direction)
{
	*rot += direction;
	if (*rot > 2 * M_PI)
		*rot = 0;
	if (*rot < 0)
		*rot = 2 * M_PI;
}

void	zoom(t_grid *grid, int direction)
{
	grid->tilesize += direction;
	if (grid->tilesize > MAX_ZOOM)
		grid->tilesize = MAX_ZOOM;
	else if (grid->tilesize < MIN_ZOOM)
		grid->tilesize = MIN_ZOOM;
}

void	z_factor(t_grid *grid, float direction)
{
	grid->z_factor += direction;
	if (grid->z_factor < Z_FACT_MIN)
		grid->z_factor = Z_FACT_MIN;
}
