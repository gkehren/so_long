/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 20:29:20 by gkehren           #+#    #+#             */
/*   Updated: 2022/06/24 15:39:54 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

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
	if (fd == -1)
	{
		write(1, "Error\n - Le fichier n'a pas pu être ouvert !\n", 46);
		return (NULL);
	}
	line = get_number_line(fd) + 1;
	map = (char **)malloc(sizeof(char *) * line);
	close(fd);
	fd = open(file, O_RDONLY);
	while (i < line)
		map[i++] = get_next_line(fd);
	close(fd);
	return (map);
}

bool	put_error(t_parse_map *parse_map)
{
	if (parse_map->nb_player == 0 || parse_map->nb_exit == 0
		|| parse_map->nb_item == 0 || parse_map->is_close == 0
		|| parse_map->is_rectangle == 0 || parse_map->nb_invalid_char > 0)
		write(1, "Error\n", 7);
	if (!parse_map->map[0])
		return (write(1, " - La carte ne peut pas être vide !\n", 37), 0);
	if (parse_map->nb_invalid_char > 0)
		write(1, " - Il y a un caractère invalide dans la carte !\n", 50);
	if (parse_map->nb_player == 0)
		write(1, " - Il manque un point d'apparition dans la carte !\n", 52);
	if (parse_map->nb_exit == 0)
		write(1, " - Il manque une sortie dans la carte !\n", 41);
	if (parse_map->nb_item == 0)
		write(1, " - Il manque des collectibles dans la carte !\n", 47);
	if (parse_map->is_close == 0)
		write(1, " - La carte n'est pas correctement fermée !\n", 46);
	if (parse_map->is_rectangle == 0)
		write(1, " - La carte ne forme pas un rectangle !\n", 41);
	if (!parse_map->map || parse_map->nb_player == 0 || parse_map->nb_exit == 0
		|| parse_map->nb_item == 0 || parse_map->is_close == 0
		|| parse_map->is_rectangle == 0 || parse_map->nb_invalid_char > 0)
		return (0);
	return (1);
}

void	fill_map(t_parse_map *parse_map, t_map *map)
{
	map->map = parse_map->map;
	map->height = parse_map->nb_line;
	map->width = parse_map->len_line - 1;
}

int	parse_map(char *file, t_map *map)
{
	t_parse_map	parse_map;

	parse_map.map = get_map_from_file(file);
	parse_map.nb_exit = 0;
	parse_map.nb_item = 0;
	parse_map.nb_player = 0;
	parse_map.nb_invalid_char = 0;
	if (!parse_map.map)
		return (1);
	if (parse_map.map[0])
	{
		map_is_close(&parse_map);
		map_is_rectangle(&parse_map);
		map_is_fill(&parse_map);
	}
	if (put_error(&parse_map) == 0)
		return (1);
	fill_map(&parse_map, map);
	memfree(parse_map.map);
	free(parse_map.map);
	return (0);
}
