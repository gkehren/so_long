/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 00:17:04 by gkehren           #+#    #+#             */
/*   Updated: 2022/07/14 13:47:04 by gkehren          ###   ########.fr       */
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
		g->exit = "./assets/chest_open.xpm";
	if (map[g->p.y][g->p.x] == 'E' && g->coins == g->total_coins)
	{
		write(1, "Victoire !\n", 12);
		exit(1);
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
