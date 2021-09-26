/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 22:04:47 by mamartin          #+#    #+#             */
/*   Updated: 2021/09/26 19:01:57 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	main(int argc, char **argv)
{
	t_map	map;
	int		fd;
	char	ret;

	if (argc != 2)
		return (exit_error("Bad argument.\n", 1));
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (exit_error("Can't open file.\n", 2));
	map.arr = NULL;
	map.x = 0;
	map.y = 0;
	ret = parse_file(fd, &map);
	if (ret == -1)
		return (exit_error("Malloc failed.", 3));
	close(fd);

	if (display_wireframe(map) == -1)
		return (exit_error("Malloc failed.", 3));

	return (0);
}


