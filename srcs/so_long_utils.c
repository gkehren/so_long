/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 00:17:04 by gkehren           #+#    #+#             */
/*   Updated: 2022/07/13 01:37:55 by gkehren          ###   ########.fr       */
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

void	*get_image(t_game *g, char *path)
{
	int		img_w;
	int		img_h;
	void	*img;

	img = mlx_xpm_file_to_image(g->mlx, path, &img_w, &img_h);
	return (img);
}
