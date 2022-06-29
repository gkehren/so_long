/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 13:40:28 by gkehren           #+#    #+#             */
/*   Updated: 2022/06/29 13:43:48 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

t_pos pos_to_screen(t_mlx *mlx, t_fpos pos)
{
	pos.x -= mlx->level.camera.x;
	pos.y -= mlx->level.camera.y;
	pos.x *= PIXELS_PER_UNIT;
	pos.y *= PIXELS_PER_UNIT;
	return ((t_pos){
		(size_t)pos.x + WIDTH / 2,
		(size_t)pos.y + HEIGHT / 2
	});
}
