/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 00:38:35 by gkehren           #+#    #+#             */
/*   Updated: 2022/07/13 01:25:43 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	move_player(int keycode, t_game *g)
{
	int	i;
	int	j;

	i = g->p.x;
	j = g->p.y;
	render_pixel(g, g->p.y, g->p.x);
	if (keycode == 125 || keycode == 1)
		move_down(g->map, &g->p, g);
	else if (keycode == 126 || keycode == 13)
		move_up(g->map, &g->p, g);
	else if (keycode == 123 || keycode == 0)
		move_right(g->map, &g->p, g);
	else if (keycode == 124 || keycode == 2)
		move_left(g->map, &g->p, g);
	else if (keycode == 53)
	{
		mlx_destroy_window(g->mlx, g->win);
		exit(1);
	}
	if (i != g->p.x || j != g->p.y)
		g->move++;
	//check_coins_and_exit(&g, g->map, g->p);
	//check_collision(g->p);
	render_map(g->map, g, &g->p, 0);
	return (0);
}
