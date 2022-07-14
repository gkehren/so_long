/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 15:27:11 by gkehren           #+#    #+#             */
/*   Updated: 2022/07/14 15:56:05 by gkehren          ###   ########.fr       */
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
# define PIXELS 32

/*******STRUCT*******/

typedef	struct s_player
{
	int	x;
	int	y;
}	t_player;

typedef struct s_enemy
{
	int	x;
	int	y;
	int	dir;
}	t_enemy;

typedef struct s_game
{
	char		**map;
	int			move;
	int			total_coins;
	int			coins;
	int			enemies;
	int			width;
	int			height;
	int			frame;
	char		*exit;
	char		*player;
	void		*mlx;
	void		*win;
	t_player	p;
	t_enemy		*e;
}	t_game;

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
	size_t	nb_enemy;
}	t_parse_map;

/*******MAP*******/

char		*get_next_line(int fd);
int			parse_map(char *file, t_game *map);
void		map_line_close(t_parse_map *parse_map, int line);
void		map_side_close(t_parse_map *parse_map, int line);
void		map_is_close(t_parse_map *parse_map);
void		map_is_rectangle(t_parse_map *parse_map);
void		map_is_fill(t_parse_map *parse_map);
void		mem_set(void *dst, unsigned char b, size_t n);
int			check_name(char *file);

/*******GAME*******/

void	get_player_and_enemies(char **map, t_player *p, t_enemy *e);
void	*get_image(t_game *g, char *path);
void	render_pixel(t_game *g, int i, int j);
void	render_image(t_game *g, char *path, int i, int j);
void	render_background(char **map, t_game g);
void	render_map(char **map, t_game *game, t_player *p, int rr);

/*******MOVES*******/

void	move_down(char **map, t_player *p, t_game *g);
void	move_up(char **map, t_player *p, t_game *g);
void	move_left(char **map, t_player *p, t_game *g);
void	move_right(char **map, t_player *p, t_game *g);
void	get_direction(char **map, t_enemy *e, int i);
void	check_coins_and_exit(t_game *g, char **map);

/*******HOOKS*******/

int	move_player(int keycode, t_game *g);
int	move_enemy(t_game *g);

/*******UTILS*******/

void		memfree(char **s);
char		*ft_strcpy(char *dst, char *src);
size_t		ft_strlen(char *s);
char		*ft_strjoin(char *s1, char *s2);
int			ft_strchr(char *s, int c);
char		*ft_itoa(int n);

#endif
