/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 00:17:04 by gkehren           #+#    #+#             */
/*   Updated: 2022/07/20 17:42:45 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	get_player_and_enemies(char **map, t_player *p, t_enemy *e)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	k = 0;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j] && map[i][j] != '\0')
		{
			if (map[i][j] == 'P')
			{
				p->y = i;
				p->x = j;
			}
			else if (map[i][j] == 'X')
			{
				e[k].y = i;
				e[k].x = j;
				e[k++].dir = 1;
			}
		}
	}
}

void	check_coins_and_exit(t_game *g, char **map)
{
	char	*moves;

	if (map[g->p.y][g->p.x] == 'C')
	{
		g->coins++;
		map[g->p.y][g->p.x] = 48;
		render_pixel(g, g->p.y, g->p.x);
	}
	if (g->coins == g->total_coins)
		g->exit = CHEST_OPEN;
	if (map[g->p.y][g->p.x] == 'E' && g->coins == g->total_coins)
	{
		write(1, "Victoire !\n", 12);
		close_window(g);
	}
	moves = ft_itoa(g->move);
	mlx_string_put(g->mlx, g->win, 10, 10, 0x00000000, moves);
	free(moves);
}

void	get_direction(char **map, t_enemy *e, int i)
{
	if (e[i].dir)
	{
		if (map[e[i].y + 1][e[i].x] != '1')
			e[i].y = e[i].y + 1;
		else
			e[i].dir = 0;
	}
	else
	{
		if (map[e[i].y - 1][e[i].x] != '1')
			e[i].y = e[i].y - 1;
		else
			e[i].dir = 1;
	}
}

void	*get_image(t_game *g, char *path)
{
	int		img_w;
	int		img_h;
	void	*img;

	img = mlx_xpm_file_to_image(g->mlx, path, &img_w, &img_h);
	return (img);
}

void	generate_img(t_game *g)
{
	int			i;
	static char	*path[IMG] = {
		"./assets/black.xpm",
		"./assets/chest_close.xpm",
		"./assets/chest_open.xpm",
		"./assets/coin.xpm",
		"./assets/enemy_left.xpm",
		"./assets/enemy_right.xpm",
		"./assets/player_left.xpm",
		"./assets/player_right.xpm",
		"./assets/wall.xpm",
		"./assets/white_image.xpm",
		"./assets/white.xpm",
	};

	i = 0;
	g->img = malloc(sizeof(t_img) * IMG);
	while (i < IMG)
	{
		g->img[i].addr = get_image(g, path[i]);
		i++;
	}
}
