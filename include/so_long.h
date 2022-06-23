/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 15:27:11 by gkehren           #+#    #+#             */
/*   Updated: 2022/06/23 14:24:54 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

/*******INCLUDE*******/

# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <fcntl.h>

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

/*******MAP*******/

char		*get_next_line(int fd);
t_parse_map	parse_map(char *file);

/*******UTILS*******/

void		memfree(char **s);

#endif
