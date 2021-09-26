/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 23:44:03 by mamartin          #+#    #+#             */
/*   Updated: 2021/09/26 19:08:59 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"
# include "../minilibx/mlx.h"
# include "../minilibx/mlx_int.h"
# include "structures.h"

# define WIN_WIDTH	800
# define WIN_HEIGHT	600

/*
**	DISPLAY
*/

char	display_wireframe(t_map map);
char	create_window(t_win *win, t_map map);
char	create_iso_grid(t_win *win);
void	draw_line(t_image *screen, t_point from, t_point to);
void	put_pixel(t_image *screen, t_point pixel);
void	refresh(t_win *win);

/*
** PARSING
*/

char	parse_file(int fd, t_map *map);
char	get_row(int fd, t_row *row);
char	realloc_map(t_map *map);

/*
** UTILS
*/

int		exit_error(char *errmessage, char exit_code);
void	free_2d_array(void **array, int size);
void	free_all(t_win *win);

#endif
