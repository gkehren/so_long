/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 15:23:41 by gkehren           #+#    #+#             */
/*   Updated: 2022/07/13 14:42:07 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	memfree(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		free(s[i++]);
}

void	init(t_game *g)
{
	g->coins = 0;
	g->total_coins = 0;
	g->frame = 0;
	g->move = 0;
	g->player = "./assets/thief-left.xpm";
	g->exit = "./assets/close_door.xpm";
}

int	close_window(t_game *g)
{
	mlx_destroy_window(g->mlx, g->win);
	exit(1);
}
#include <stdio.h>
int	main(int argc, char **argv)
{
	t_game		g;

	if (argc != 2)
		return (write(1, "Please give a path map\n", 24), 0);
	init(&g);
	if (parse_map(argv[1], &g) == 1)
		return (0);
	g.e = malloc(g.enemies * sizeof(t_enemy));
	get_player_and_enemies(g.map, &g.p, g.e);
	g.mlx = mlx_init();
	g.win = mlx_new_window(g.mlx, (ft_strlen(g.map[0])) * PIXELS, g.width
			* PIXELS, "so_long");
	printf("player x = %d | y = %d\n", g.p.x, g.p.y);
	printf("coins = %d | total coins = %d\n", g.coins, g.total_coins);
	render_background(g.map, g);
	mlx_key_hook(g.win, move_player, &g);
	mlx_loop_hook(g.mlx, move_enemy, &g);
	render_map(g.map, &g, &g.p, 1);
	mlx_hook(g.win, 17, 0, close_window, &g);
	mlx_loop(g.mlx);
	return (memfree(g.map), free(g.map), 0);
}
