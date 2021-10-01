/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 23:44:03 by mamartin          #+#    #+#             */
/*   Updated: 2021/10/01 04:25:14 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <math.h>

# include "../libft/libft.h"
# include "../minilibx/mlx.h"
# include "../minilibx/mlx_int.h"
# include "types.h"
# include "defines.h"

enum e_errcode
{
	ERR_MALLOC = -1,
	ERR_ARGUMENT = 1,
	ERR_FILE = 2,
};

/*
**	DISPLAY
*/

int		display_wireframe(t_map map);
int		create_window(t_win *win, t_map map);
int		create_iso_grid(t_grid *grid, t_map map);
void	draw(t_win *win);
void	to_iso_coordinates(t_grid *grid, t_map map);
void	draw_line(t_image *screen, t_point from, t_point to, t_gradient gradient);
void	put_pixel(t_image *screen, t_point pixel, int color);
void	refresh_iso_grid(t_grid *grid, t_map map);
void	clear_screen(t_image *screen);
int		refresh_display(t_win *win);

/*
** PARSING
*/	

int		parse_file(int fd, t_map *map);
int		get_row(int fd, t_row *row);
int		get_color(char *str);

/*
** EVENT
*/

int		handle_keypress(int key, t_win *win);
int		handle_keyrelease(int key, t_win *win);
int		handle_buttonpress(int button, int x, int y, t_win *win);
int		handle_buttonrelease(int button, int x, int y, t_win *win);
int		handle_pointer_motion(int x, int y, t_win *win);
void	handle_event(t_grid *grid, t_keyhandle key_info);
void	reset_display(t_win *win);

/*
** MATHS TRANSFORMATIONS
*/

void	zoom(t_grid *grid, int direction);
void	translate(int *axis, int direction, int max);
void	z_factor(t_grid *grid, float direction);

/*
** UTILS
*/

int		exit_error(char *errmessage, char exit_code);
void	free_2d_array(void **array, int size);
void	exit_program_code(t_win *win, char exit_code);
int		exit_program_success(t_win *win);
t_point	**alloc_map(int x, int y);
t_point	**copy_map(t_point **src, t_point **dest, int x, int y);
int		realloc_map(t_map *map);
int		is_in_screen(t_point p);

#endif
