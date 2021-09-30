/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 00:38:50 by mamartin          #+#    #+#             */
/*   Updated: 2021/09/30 01:29:18 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	zoom(t_grid *grid, int direction)
{
	grid->tilesize += direction;
	if (grid->tilesize > MAX_ZOOM)
		grid->tilesize = MAX_ZOOM;
	else if (grid->tilesize < MIN_ZOOM)
		grid->tilesize = MIN_ZOOM;
}

void	translate(int *axis, int direction, int max)
{
	*axis += TRANSLATION_STEP * direction;
	if (abs(*axis) >= max)
		*axis = max * direction;
}

void	z_factor(t_grid *grid, float direction)
{
	grid->z_factor += direction;
	if (grid->z_factor < Z_FACT_MIN)
		grid->z_factor = Z_FACT_MIN;
}
