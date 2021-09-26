/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 18:07:24 by mamartin          #+#    #+#             */
/*   Updated: 2021/09/26 22:28:08 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

/*
** MAP STRUCTURE
** arr		2D array of int
** x		map size horizontally
** y		map size vertically
*/

typedef struct s_map
{
	int	**arr;
	int	x;
	int	y;
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
** WINDOW STRUCTURE
*/

typedef struct s_win
{
	void	*mlx;
	void	*window;
	t_image	screen;
	t_map	map;
}	t_win;

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
}	t_point;

#endif
