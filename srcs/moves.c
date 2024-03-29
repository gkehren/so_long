/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 00:59:07 by gkehren           #+#    #+#             */
/*   Updated: 2022/07/20 16:13:41 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	move_down(char **map, t_player *p, t_game *g)
{
	if (map[p->y + 1][p->x] != '1' && map[p->y + 1][p->x] != 'E')
		p->y = p->y + 1;
	else if (map[p->y + 1][p->x] == 'E' && g->coins == g->total_coins)
		p->y = p->y + 1;
}

void	move_up(char **map, t_player *p, t_game *g)
{
	if (map[p->y - 1][p->x] != '1' && map[p->y - 1][p->x] != 'E')
		p->y = p->y - 1;
	else if (map[p->y - 1][p->x] == 'E' && g->coins == g->total_coins)
		p->y = p->y - 1;
}

void	move_right(char **map, t_player *p, t_game *g)
{
	if (map[p->y][p->x + 1] != '1' && map[p->y][p->x + 1] != 'E')
		p->x = p->x + 1;
	else if (map[p->y][p->x + 1] == 'E' && g->coins == g->total_coins)
		p->x = p->x + 1;
	g->player = PLAYER_RIGHT;
}

void	move_left(char **map, t_player *p, t_game *g)
{
	if (map[p->y][p->x - 1] != '1' && map[p->y][p->x - 1] != 'E')
		p->x = p->x - 1;
	else if (map[p->y][p->x - 1] == 'E' && g->coins == g->total_coins)
		p->x = p->x - 1;
	g->player = PLAYER_LEFT;
}
