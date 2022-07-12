/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 00:30:53 by gkehren           #+#    #+#             */
/*   Updated: 2022/07/13 01:52:59 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	*put_image(t_game *g, int i, int j)
{
	void	*img;

	if (i % 2 == 0)
	{
		if (j % 2 == 0)
			img = get_image(g, "./assets/white.xpm");
		else
			img = get_image(g, "./assets/black.xpm");
	}
	else
	{
		if (j % 2 != 0)
			img = get_image(g, "./assets/white.xpm");
		else
			img = get_image(g, "./assets/black.xpm");
	}
	return (img);
}

void	render_map(char **map, t_game *g, t_player *p, int rr)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == '1' && rr)
				render_image(g, "./assets/wall.xpm", i, j);
			else if (map[i][j] == 'E')
				render_image(g, g->exit, i, j);
			else if (map[i][j] == 'C' && rr)
				render_image(g, "./assets/coin.xpm", i, j);
			else if (map[i][j] != '0' && map[i][j] != 'X' &&
				map[i][j] != 'P' && rr)
			{
				write(1, "Error\n - La carte n'est pas valide\n", 36);
				exit(1);
			}
		}
	}
	render_image(g, g->player, p->y, p->x);
}

void	render_background(char **map, t_game g)
{
	int		i;
	int		j;
	void	*img;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] && map[i][j] != '\0')
		{
			img = put_image(&g, i, j);
			mlx_put_image_to_window(g.mlx, g.win, img,
				j * PIXELS, i * PIXELS);
			j++;
		}
		i++;
	}
}

void	render_image(t_game *g, char *path, int i, int j)
{
	void	*img;

	img = get_image(g, path);
	mlx_put_image_to_window(g->mlx, g->win, img,
		j * PIXELS, i * PIXELS);
}

void	render_pixel(t_game *g, int i, int j)
{
	void	*img;

	img = get_image(g, "./assets/white_image.xpm");
	mlx_put_image_to_window (g->mlx, g->win, img, 0, 0);
	img = put_image(g, i, j);
	mlx_put_image_to_window (g->mlx, g->win, img, \
		j * PIXELS, i * PIXELS);
}
