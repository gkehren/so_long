/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 20:29:20 by gkehren           #+#    #+#             */
/*   Updated: 2022/06/28 21:46:44 by gkehren          ###   ########.fr       */
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
	size_t	i;
	size_t	j;

	j = 0;
	map->map = (char **)malloc(sizeof(char *) * (parse_map->nb_line + 2));
	while (j < parse_map->nb_line + 1)
	{
		i = 0;
		map->map[j] = (char *)malloc(sizeof(char) * (parse_map->len_line + 1));
		while (parse_map->map[j][i] != '\n' && parse_map->map[j][i])
		{
			map->map[j][i] = parse_map->map[j][i];
			i++;
		}
		map->map[j][i] = '\0';
		j++;
	}
	map->map[j] = NULL;
	map->height = parse_map->nb_line + 1;
	map->width = parse_map->len_line;
}

int	check_name(char *file)
{
	size_t	i;

	i = 0;
	while (file[i])
		i++;
	if (i < 4)
		return (1);
	else if (file[i - 4]  == '.' && file[i - 3] == 'b'
			&& file[i - 2] == 'e' && file[i - 1] == 'r')
			return (0);
	return (1);

}

int	parse_map(char *file, t_map *map)
{
	t_parse_map	parse_map;

	if (check_name(file) == 1)
		return (write(1, "Le fichier doit être en .ber !\n", 33), 1);
	parse_map.nb_exit = 0;
	parse_map.nb_item = 0;
	parse_map.nb_player = 0;
	parse_map.nb_invalid_char = 0;
	parse_map.map = get_map_from_file(file);
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
