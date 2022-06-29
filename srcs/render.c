/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 13:20:15 by gkehren           #+#    #+#             */
/*   Updated: 2022/06/29 17:58:48 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

//static void	render_dead(t_pos pos, t_mlx *mlx)
//{
//	pos.x -= 22;
//	pos.y -= 22;
//	put_image(
//		mlx, (t_rect){pos.x, pos.y, 90, 90},
//		&mlx->images[IMG_DEAD],
//		(t_srect){90 * mlx->level.dead_anim_frame, 0, 90, 90, 0, 0});
//}

void	render_player(t_mlx *mlx)
{
	t_pos	pos;

	pos = pos_to_screen(mlx, mlx->level.player_pos);
	//if (mlx->level.dead)
	//	render_dead(pos, mlx);
	if (mlx->level.game_state == game_playing)
		return ;
	pos.x -= 16;
	pos.y -= 16;
	put_image(mlx, (t_rect){pos.x, pos.y, 32, 32},
			&mlx->images[IMG_PLAYER],
			(t_srect){32 * mlx->level.player_anim_frame, 32
			* mlx->level.player_dir, 32, 32, 0, 0});
}

void	render_game(t_mlx *mlx)
{
	mem_set(mlx->canvas.addr, 0x00, mlx->canvas.line_len * HEIGHT);
	//render_background(mlx);
	//render_corner(mlx);
	//render_exit(mlx);
	//render_walls(mlx);
	//render_enemies(mlx);
	render_player(mlx);
	//render_move_count(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->canvas.image, 0, 0);
}
