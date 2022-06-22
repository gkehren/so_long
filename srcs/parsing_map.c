/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 20:29:20 by gkehren           #+#    #+#             */
/*   Updated: 2022/06/22 18:21:50 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"
#include <stdio.h>
int	get_number_line(int fd)
{
	int		line;
	char	*tmp;

	tmp = get_next_line(fd);
	free(tmp);
	line = 0;
	while (tmp != NULL)
	{
		tmp = get_next_line(fd);
		free(tmp);
		line++;
	}
	return (line);
}

char	**get_map_from_file(char *file)
{
	char	**map;
	int		line;
	int		i;
	int		fd;

	i = 0;
	fd = open(file, O_RDONLY);
	line = get_number_line(fd) + 1;
	map = (char **)malloc(sizeof(char *) * line);
	close(fd);
	fd = open(file, O_RDONLY);
	while (i < line)
		map[i++] = get_next_line(fd);
	close(fd);
	return (map);
}

t_parse_map	parse_map(char *file)
{
	t_parse_map	parse_map;

	parse_map.map = get_map_from_file(file);
	printf("%s%s%s%s%s%s\n", parse_map.map[0], parse_map.map[1], parse_map.map[2], parse_map.map[3], parse_map.map[4], parse_map.map[5]);
	return (parse_map);
}
