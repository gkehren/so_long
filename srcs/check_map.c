/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 17:02:16 by gkehren           #+#    #+#             */
/*   Updated: 2022/06/23 17:06:58 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

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
