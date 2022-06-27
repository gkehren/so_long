/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 18:42:52 by gkehren           #+#    #+#             */
/*   Updated: 2022/06/27 19:15:08 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	destroy_hook(t_map *map)
{
	mlx_loop_end(map->mlx);
	return (0);
}

int	start_game(t_map *map)
{
	mlx_hook(map->win, 17, 0, destroy_hook, map->mlx);
	mlx_loop(map->mlx);
	return (0);
}
