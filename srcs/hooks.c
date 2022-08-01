/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 00:38:35 by gkehren           #+#    #+#             */
/*   Updated: 2022/08/01 12:43:31 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	check_collision(t_game *g)
{
	int	i;

	i = 0;
	while (i < g->enemies)
	{
		if (g->e[i].x == g->p.x && g->e[i].y == g->p.y)
		{
			write(1, "Perdu !\n", 9);
			close_window(g);
		}
		i++;
	}
}

int	move_enemy(t_game *g)
{
	int		i;
	char	*moves;

	i = 0;
	if (g->frame == 12000)
	{
		while (i < g->enemies)
		{
			render_pixel(g, g->e[i].y, g->e[i].x);
			get_direction(g->map, g->e, i);
			check_collision(g);
			render_image(g, ENEMY_RIGHT, g->e[i].y, g->e[i].x);
			moves = ft_itoa(g->move);
			mlx_string_put(g->mlx, g->win, 10, 10,
				0x00, moves);
			free(moves);
			i++;
		}
		g->frame = 0;
	}
	else
		g->frame++;
	return (0);
}

int	move_player(int keycode, t_game *g)
{
	int	i;
	int	j;

	i = g->p.x;
	j = g->p.y;
	render_pixel(g, g->p.y, g->p.x);
	if (keycode == 115)
		move_down(g->map, &g->p, g);
	else if (keycode == 119)
		move_up(g->map, &g->p, g);
	else if (keycode == 100)
		move_right(g->map, &g->p, g);
	else if (keycode == 97)
		move_left(g->map, &g->p, g);
	else if (keycode == 65307)
		close_window(g);
	if (i != g->p.x || j != g->p.y)
		g->move++;
	check_coins_and_exit(g, g->map);
	check_collision(g);
	render_map(g->map, g, &g->p, 0);
	return (0);
}
