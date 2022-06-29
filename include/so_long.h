/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 15:27:11 by gkehren           #+#    #+#             */
/*   Updated: 2022/06/29 17:29:56 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

/*******INCLUDE*******/

# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <fcntl.h>
# include "../minilibx/mlx.h"

/*******GAME*OPTIONS*******/

// Size of the window
# define WIDTH 1280
# define HEIGHT 720
# define NB_ASSETS 5
# define PIXELS_PER_UNIT 32.0f

/*******STRUCT*******/

typedef struct s_pos
{
	size_t	x;
	size_t	y;
}	t_pos;

typedef struct s_fpos
{
	float	x;
	float	y;
}	t_fpos;

typedef struct s_fvec
{
	float	x;
	float	y;
}	t_fvec;

typedef struct s_rect
{
	int	x;
	int	y;
	int	width;
	int	height;
}	t_rect;

typedef struct s_srect
{
	int	x;
	int	y;
	int	width;
	int	height;
	int	uv_x;
	int	uv_y;
}	t_srect;

typedef struct s_color
{
	unsigned char	a;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_rgba;

typedef enum e_wall_tile
{
	WALL_TOP_LEFT,
	WALL_TOP,
	WALL_TOP_RIGHT,
	WALL_RIGHT,
	WALL_BOT_RIGHT,
	WALL_BOT,
	WALL_BOT_LEFT,
	WALL_LEFT,
	WALL_CENTER,
}	t_wall_tile;

typedef struct s_wall
{
	t_fpos		pos;
	t_wall_tile	tile;
}	t_wall;

typedef struct s_corner
{
	t_fpos	pos;
	size_t	frame;
	float	next_frame;
}	t_corner;

typedef struct s_enemy
{
	t_fpos	pos;
	t_fvec	vel;

	size_t	dir;
	size_t	anim_frame;
	float	next_ami_frame;
}	t_enemy;

typedef enum e_game_state
{
	game_playing,
	game_win,
	game_lose,
}	t_state;

typedef enum e_game_image
{
	IMG_PLAYER,
	IMG_ITEM,
	IMG_EXIT,
	IMG_ENEMY,
	IMG_WALL,
}	t_gimg;

typedef struct s_level
{
	size_t		nb_wall;
	t_wall		*walls;

	size_t		max_corner;
	size_t		rem_corner;
	t_corner	*corner;

	float		rem_dist;
	size_t		move_count;

	t_fpos		exit;
	size_t		exit_anim_frame;
	float		next_exit_anim_frame;

	t_enemy		*enemy;
	size_t		nb_enemy;

	bool		dead;
	size_t		dead_anim_frame;
	float		next_dead_anim_frame;

	t_fpos		camera;

	bool		press_up;
	bool		press_down;
	bool		press_right;
	bool		press_left;
	t_fvec		movement_input;
	t_fvec		player_vel;
	t_fpos		player_pos;
	size_t		player_dir;
	float		next_player_anim_frame;
	size_t		player_anim_frame;

	t_state		game_state;
}	t_level;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_img
{
	void				*image;
	unsigned char		*addr;
	unsigned int		line_len;
}	t_img;

typedef struct s_map
{
	char	**map;
	size_t	width;
	size_t	height;
	void	*mlx;
	void	*win;
}	t_map;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;

	t_map	*map;
	size_t	map_count;
	size_t	cur_map;
	t_img	images[NB_ASSETS];
	t_img	canvas;
	t_level	level;
}	t_mlx;

typedef struct s_parse_map
{
	char	**map;

	bool	is_rectangle;
	bool	is_close;

	size_t	len_line;
	size_t	nb_invalid_char;
	size_t	nb_line;
	size_t	nb_player;
	size_t	nb_exit;
	size_t	nb_item;
}	t_parse_map;

/*******MAP*******/

char		*get_next_line(int fd);
int			parse_map(char *file, t_map *map);
void		map_line_close(t_parse_map *parse_map, int line);
void		map_side_close(t_parse_map *parse_map, int line);
void		map_is_close(t_parse_map *parse_map);
void		map_is_rectangle(t_parse_map *parse_map);
void		map_is_fill(t_parse_map *parse_map);
bool		load_assets(void *mlx, t_img *images);
bool		generate_image(void *mlx, unsigned int w, unsigned int h, t_img *img);
bool		generate_level(t_mlx *mlx, t_map *map);
void		mem_set(void *dst, unsigned char b, size_t n);
int			start_game(t_map *map, size_t map_count);
int			generate_game(t_mlx *mlx, t_map *map, size_t map_count);
void		destroy_level(t_level *level);
t_pos		pos_to_screen(t_mlx *mlx, t_fpos pos);
void		render_game(t_mlx *mlx);
void		put_image(t_mlx *mlx, t_rect dst, t_img *src_img, t_srect src);

/*******HOOK*******/

int	destroy_hook(t_mlx *mlx);
int	key_press_hook(unsigned long key, t_mlx *mlx);
int	key_release_hook(unsigned long key, t_mlx *mlx);
int	loop_hook(t_mlx *mlx);

/*******UTILS*******/

void		memfree(char **s);
char		*ft_strcpy(char *dst, char *src);
size_t		ft_strlen(char *s);
char		*ft_strjoin(char *s1, char *s2);
int			ft_strchr(char *s, int c);

#endif
