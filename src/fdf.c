/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 22:04:47 by mamartin          #+#    #+#             */
/*   Updated: 2021/09/30 01:15:21 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	main(int argc, char **argv)
{
	t_map	map;
	int		fd;
	char	ret;

	if (argc != 2)
		return (exit_error("Bad argument.\n", ERR_ARGUMENT));
	if (check_filename(argv[1]) != 0)
		return (exit_error("Bad filename.\n", ERR_FILE));
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (exit_error("Can't open file.\n", ERR_FILE));
	map.arr = NULL;
	map.x = 0;
	map.y = 0;
	ret = parse_file(fd, &map);
	if (ret == ERR_MALLOC)
		return (exit_error("Malloc failed.", ERR_MALLOC));
	else if (ret == ERR_FILE)
		return (exit_error("Map is not a rectangle.\n", ERR_FILE));
	close(fd);
	if (display_wireframe(map) == ERR_MALLOC)
		return (exit_error("Malloc failed.", ERR_MALLOC));
	return (0);
}


