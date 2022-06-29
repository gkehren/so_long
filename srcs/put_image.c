/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 13:44:51 by gkehren           #+#    #+#             */
/*   Updated: 2022/06/29 14:27:07 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	clamp_one_d(int *x, int *width, int *src, int bound)
{
	if (*x + *width < 0)
		*width = 0;
	else if (*x < 0 && *x + *width >= 0)
	{
		*width = *x + *width;
		*src -= *x;
		*x = 0;
	}
	else if (*x < bound && *x + *width >= bound)
		*width = bound - *x;
	else if (*x >= bound)
		*width = 0;
}

inline static int	mod_pos(int i, int m)
{
	return ((size_t)i % (size_t)m);
}

void	put_image(t_mlx *mlx, t_rect dst, t_img *src_img, t_srect src)
{
	int		x;
	int		y;
	t_rgba	c;

	clamp_one_d(&dst.x, &dst.width, &src.x, WIDTH);
	clamp_one_d(&dst.y, &dst.height, &src.y, HEIGHT);
	y = 0;
	while (y < dst.height)
	{
		x = 0;
		while (x < dst.width)
		{
			c= *(t_rgba *)(src_img->addr + src_img->line_len
				* (src.y + mod_pos(src.uv_y + y, src.height)) + 4
				* (src.x + mod_pos(src.uv_x + x, src.width)));
			if (c.a != 0)
				*(t_rgba *)(mlx->canvas.addr + mlx->canvas.line_len
				* (dst.y + y) + 4 * (dst.x)) = c;
			x++;
		}
		y++;
	}
}
