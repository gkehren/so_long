/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 20:29:20 by gkehren           #+#    #+#             */
/*   Updated: 2022/06/23 14:34:20 by gkehren          ###   ########.fr       */
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

void	map_line_close(t_parse_map *parse_map, int line)
{
	size_t	i;

	i = 0;
	while (i < parse_map->len_line)
	{
		if (parse_map->map[line][i] == '1')
			i++;
		else
			break ;
	}
	if (i == parse_map->len_line)
		parse_map->is_close = 1;
	else
		parse_map->is_close = 0;
}

void	map_side_close(t_parse_map *parse_map, int line)
{
	size_t	i;

	i = 0;
	while (i < parse_map->nb_line)
	{
		if (parse_map->map[i][line] == '1')
			i++;
		else
			break ;
	}
	if (i == parse_map->nb_line)
		parse_map->is_close = 1;
	else
		parse_map->is_close = 0;
}

void	map_is_close(t_parse_map *parse_map)
{
	parse_map->len_line = 0;
	parse_map->nb_line = 0;
	while (parse_map->map[0][parse_map->len_line] != '\n')
		parse_map->len_line++;
	while (parse_map->map[parse_map->nb_line])
		parse_map->nb_line++;
	parse_map->nb_line--;
	map_line_close(parse_map, 0);
	if (parse_map->is_close == 1)
		map_line_close(parse_map, parse_map->nb_line);
	if (parse_map->is_close == 1)
		map_side_close(parse_map, 0);
	if (parse_map->is_close == 1)
		map_side_close(parse_map, parse_map->len_line - 1);
}

void	map_is_rectangle(t_parse_map *parse_map)
{
	size_t	i;
	size_t	j;

	j = 0;
	while (j < parse_map->nb_line + 1)
	{
		i = 0;
		while (parse_map->map[j][i])
			i++;
		if (i == parse_map->len_line + 1)
			parse_map->is_rectangle = 1;
		else
		{
			parse_map->is_rectangle = 0;
			break ;
		}
		j++;
	}
}

void	map_is_fill(t_parse_map *parse_map)
{
	size_t	i;
	size_t	j;

	j = 0;
	while (j < parse_map->nb_line + 1)
	{
		i = 0;
		while (i < parse_map->len_line)
		{
			if (parse_map->map[j][i] != 'P' && parse_map->map[j][i] != 'E'
				&& parse_map->map[j][i] != 'C' && parse_map->map[j][i] != '0'
				&& parse_map->map[j][i] != '1')
				parse_map->nb_invalid_char++;
			if (parse_map->map[j][i] == 'P')
				parse_map->nb_player++;
			if (parse_map->map[j][i] == 'E')
				parse_map->nb_exit++;
			if (parse_map->map[j][i] == 'C')
				parse_map->nb_item++;
			i++;
		}
		j++;
	}
}

bool	put_error(t_parse_map *parse_map)
{
	if (parse_map->nb_invalid_char > 0)
		write(1, "Il y a un caractère invalide dans la carte !\n", 47);
	if (parse_map->nb_player == 0)
		write(1, "Il manque un point d'apparition dans la carte !\n", 49);
	if (parse_map->nb_exit == 0)
		write(1, "Il manque une sortie dans la carte !\n", 38);
	if (parse_map->nb_item == 0)
		write(1, "Il manque des collectibles dans la carte !\n", 44);
	if (parse_map->is_close == 0)
		write(1, "La carte n'est pas correctement fermée !\n", 43);
	if (parse_map->is_rectangle == 0)
		write(1, "La carte ne forme pas un rectangle !\n", 38);
	if (parse_map->nb_player == 0 || parse_map->nb_exit == 0
		|| parse_map->nb_item == 0 || parse_map->is_close == 0
		|| parse_map->is_rectangle == 0 || parse_map->nb_invalid_char > 0)
		return (0);
	return (1);
}

t_parse_map	parse_map(char *file)
{
	t_parse_map	parse_map;

	parse_map.map = get_map_from_file(file);
	parse_map.nb_exit = 0;
	parse_map.nb_item = 0;
	parse_map.nb_player = 0;
	parse_map.nb_invalid_char = 0;
	printf("%s%s%s%s%s%s\n", parse_map.map[0], parse_map.map[1], parse_map.map[2], parse_map.map[3], parse_map.map[4], parse_map.map[5]);
	map_is_close(&parse_map);
	map_is_rectangle(&parse_map);
	map_is_fill(&parse_map);
	put_error(&parse_map);
	return (parse_map);
}
