/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 18:07:24 by mamartin          #+#    #+#             */
/*   Updated: 2021/10/02 02:22:43 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "defines.h"

/*
** VECTOR STRUCTURE
*/

typedef struct s_vect
{
	double	x;
	double	y;
}	t_vect;

/*
** POINT STRUCTURE
*/

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	color;
}	t_point;

/*
** MAP STRUCTURE
** arr		2D array of int
** x		map size horizontally
** y		map size vertically
*/

typedef struct s_map
{
	t_point	**arr;
	int		x;
	int		y;
}	t_map;

/*
** ROW STRUCTURE
** array	array of strings representing integers
** size		row size
*/

typedef struct s_row_str
{
	char	**array;
	int		size;
}	t_row;

/*
** IMAGE STRUCTURE
*/

typedef struct s_image
{
	void			*img;
	unsigned int	*addr;
	int				bpp;
	int				size_line;
	int				endian;
	int				width;
	int				height;	
}	t_image;

/*
** CARTESIAN COORDINATES SYSTEM STRUCTURE
*/

typedef struct s_coordinates_sys
{
	t_vect	i;
	t_vect	j;
}	t_coordinates_sys;

/*
** GRID STRUCTURE
*/

typedef struct s_grid
{
	t_point				**array;
	t_point				origin;
	t_point				offset;
	t_coordinates_sys	system;
	double				rot;
	t_point				size;
	int					tilesize;
	double				z_factor;
}	t_grid;

/*
**	GRADIENT STRUCTURE
*/

typedef struct s_gradient
{
	int		shades[GRADIENT_SIZE];
	int		smallest_z;
	int		biggest_z;
	char	state;
}	t_gradient;

/*
**	KEY HANDLING STRUCTURE
*/

typedef struct s_keyhandle
{
	char	a;
	char	d;
	char	kp_plus;
	char	kp_minus;
	char	button1;
	char	button2;
	t_point	cursor_button1;
	int		cursor_button2_x;
	t_point	last_offset;
}	t_keyhandle;

/*
** WINDOW STRUCTURE
*/

typedef struct s_win
{
	void		*mlx;
	void		*window;
	t_image		screen;
	t_map		map;
	t_grid		grid;
	t_gradient	gradient;
	t_keyhandle	keys;
}	t_win;

#endif
