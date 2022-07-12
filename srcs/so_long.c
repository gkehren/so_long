/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 15:23:41 by gkehren           #+#    #+#             */
/*   Updated: 2022/07/13 01:55:11 by gkehren          ###   ########.fr       */
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
	g->player = "./assets/thief-left.xpm";
	g->exit = "./assets/close_door.xpm";
}

int	close_window(t_game *g)
{
	mlx_destroy_window(g->mlx, g->win);
	exit(1);
}

int	main(int argc, char **argv)
{
	t_game		g;
	t_player	p;
	t_enemy		*e;

	if (argc != 2)
		return (write(1, "Please give a path map\n", 24), 0);
	if (parse_map(argv[1], &g) == 1)
		return (0);
	e = malloc(g.enemies * sizeof(t_enemy));
	get_player_and_enemies(g.map, &p, e);
	g.mlx = mlx_init();
	g.win = mlx_new_window(g.mlx, (ft_strlen(g.map[0])) * PIXELS, g.width
			* PIXELS, "so_long");
	render_background(g.map, g);
	init(&g);
	mlx_key_hook(g.win, move_player, &g);
	render_map(g.map, &g, &p, 1);
	mlx_hook(g.win, 17, 0, close_window, &g);
	mlx_loop(g.mlx);
	return (memfree(g.map), free(g.map), 0);
}
