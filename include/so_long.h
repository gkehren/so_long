/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 15:27:11 by gkehren           #+#    #+#             */
/*   Updated: 2022/06/26 03:21:35 by gkehren          ###   ########.fr       */
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

/*******STRUCT*******/

typedef struct s_pos
{
	float	x;
	float	y;
}	t_pos;

typedef struct s_map
{
	char	**map;
	size_t	width;
	size_t	height;
	t_pos	*player;
	t_pos	*exit;
}	t_map;

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

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

/*******MAP*******/

char		*get_next_line(int fd);
int			parse_map(char *file, t_map *map);
void		map_line_close(t_parse_map *parse_map, int line);
void		map_side_close(t_parse_map *parse_map, int line);
void		map_is_close(t_parse_map *parse_map);
void		map_is_rectangle(t_parse_map *parse_map);
void		map_is_fill(t_parse_map *parse_map);
void		display_map(t_map *map);

/*******UTILS*******/

void		memfree(char **s);
char		*ft_strcpy(char *dst, char *src);
size_t		ft_strlen(char *s);
char		*ft_strjoin(char *s1, char *s2);
int			ft_strchr(char *s, int c);

#endif
