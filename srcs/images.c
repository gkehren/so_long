/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 14:57:04 by gkehren           #+#    #+#             */
/*   Updated: 2022/06/27 18:16:12 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static const char	**path(void)
{
	static const char	*assets_path[nb_assets] = {
		"assets/player_idle.xpm",
		"assets/player_walking.xpm",
		"assets/player_fly.xpm",
		"assets/wall.xpm",
		"assets/enemy_idle.xpm",
		"assets/enemy_walking.xpm",
		"assets/enemy_attack.xpm",
	};

	return (assets_path);
}

inline static bool	get_img_addr(t_img *img)
{
	int	endian;
	int	bpp;

	img->addr = (unsigned char *)mlx_get_data_addr(img->image,
													&bpp,
													(int *)&img->line_len,
													&endian);
	return(img->addr && bpp == 32 && endian == 0);
}

bool	load_asset(void	*mlx, const char *path, t_img *img)
{
	int	width;
	int	height;

	img->image = mlx_xpm_file_to_image(mlx, (char *)path, &width, &height);
	if (!img->image)
		return (false);
	return (get_img_addr(img));
}

bool	generate_image(void *mlx, unsigned int w, unsigned int h, t_img *img)
{
	img->image = mlx_new_image(mlx, w, h);
	if (!img->image)
		return (false);
	return (get_img_addr(img));
}

bool	load_assets(void *mlx, t_img *images)
{
	size_t	i;

	i = 0;
	while (i < nb_assets)
	{
		if (!load_asset(mlx, (char *)path()[i], &images[i]))
		{
			while (i)
				mlx_destroy_image(mlx, images[--i].image);
			return (false);
		}
		i++;
	}
	return (true);
}
