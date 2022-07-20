/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 15:23:41 by gkehren           #+#    #+#             */
/*   Updated: 2022/07/20 17:43:04 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	check_name(char *file)
{
	size_t	i;

	i = 0;
	while (file[i])
		i++;
	if (i < 4)
		return (1);
	else if (file[i - 4] == '.' && file[i - 3] == 'b'
		&& file[i - 2] == 'e' && file[i - 1] == 'r')
		return (0);
	return (1);
}

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
	g->player = PLAYER_RIGHT;
	g->exit = CHEST_CLOSE;
}

int	close_window(t_game *g)
{
	int	i;

	i = 0;
	free(g->e);
	memfree(g->map);
	free(g->map);
	while (i < IMG)
	{
		mlx_destroy_image(g->mlx, g->img[i].addr);
		i++;
	}
	free(g->img);
	mlx_destroy_window(g->mlx, g->win);
	mlx_destroy_display(g->mlx);
	free(g->mlx);
	exit(1);
}

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
	g.win = mlx_new_window(g.mlx, (ft_strlen(g.map[0])) * PIXELS, g.height
			* PIXELS, "so_long");
	generate_img(&g);
	render_background(g.map, g);
	mlx_key_hook(g.win, move_player, &g);
	mlx_loop_hook(g.mlx, move_enemy, &g);
	render_map(g.map, &g, &g.p, 1);
	mlx_hook(g.win, 17, 0, close_window, &g);
	mlx_loop(g.mlx);
	return (close_window(&g), 0);
}
