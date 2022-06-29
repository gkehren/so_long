/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 22:00:09 by gkehren           #+#    #+#             */
/*   Updated: 2022/06/29 14:33:21 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"
#include <math.h>

#define UP_KEY 119
#define DOWN_KEY 115
#define LEFT_KEY 97
#define RIGHT_KEY 100
#define ESCAPE_KEY 65307
#define SPACE_KEY 32

int	destroy_hook(t_mlx *mlx)
{
	mlx_loop_end(mlx->mlx);
	return (0);
}

static void	update_movement_input(t_mlx *mlx)
{
	float	inv_len;

	mlx->level.movement_input = (t_fvec){0.0, 0.0};
	if (mlx->level.press_up)
		mlx->level.movement_input.y -= 1.0;
	if (mlx->level.press_left)
		mlx->level.movement_input.x -= 1.0;
	if (mlx->level.press_down)
		mlx->level.movement_input.y += 1.0;
	if (mlx->level.press_right)
		mlx->level.movement_input.x += 1.0;
	if (mlx->level.movement_input.x != 0.0
		|| mlx->level.movement_input.y != 0.0)
	{
		inv_len = 1.0 / sqrtf(
				mlx->level.movement_input.x * mlx->level.movement_input.x
				+ mlx->level.movement_input.y * mlx->level.movement_input.y);
		mlx->level.movement_input.x *= inv_len;
		mlx->level.movement_input.y *= inv_len;
	}
}

int	space_key_hook(t_mlx *mlx)
{
	if (mlx->level.game_state == game_win)
	{
		if (mlx->cur_map == mlx->map_count - 1)
			return (mlx_loop_end(mlx->mlx));
		destroy_level(&mlx->level);
		mlx->cur_map++;
		generate_level(mlx, &mlx->map[mlx->cur_map]);
	}
	else if (mlx->level.game_state == game_lose)
	{
		destroy_level(&mlx->level);
		generate_level(mlx, &mlx->map[mlx->cur_map]);
	}
	return (0);
}

int	key_release_hook(unsigned long key, t_mlx *mlx)
{
	if (key == ESCAPE_KEY)
		return (mlx_loop_end(mlx->mlx));
	else if (key == UP_KEY)
		mlx->level.press_up = false;
	else if (key == LEFT_KEY)
		mlx->level.press_left = false;
	else if (key == DOWN_KEY)
		mlx->level.press_down = false;
	else if (key == RIGHT_KEY)
		mlx->level.press_right = false;
	else if (key == SPACE_KEY)
		return (space_key_hook(mlx), 0);
	update_movement_input(mlx);
	//update_player_dir(mlx);
	return (0);
}

int	key_press_hook(unsigned long key, t_mlx *mlx)
{
	if (key == UP_KEY)
		mlx->level.press_up = true;
	else if (key == LEFT_KEY)
		mlx->level.press_left = true;
	else if (key == DOWN_KEY)
		mlx->level.press_down = true;
	else if (key == RIGHT_KEY)
		mlx->level.press_right = true;
	update_movement_input(mlx);
	//update_player_dir(mlx);
	return (0);
}

int	loop_hook(t_mlx *mlx)
{
	//move_player(mlx);
	//update_enemies(mlx);
	//count_movements(mlx);
	//update_camera(mlx);
	//collect_coins(mlx);
	//finish(mlx);
	//animate_player(mlx);
	//animate_enemies(mlx);
	//animate_coins(mlx);
	//animate_exit(mlx);
	render_game(mlx);
	return (0);
}
