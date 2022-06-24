/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 15:23:41 by gkehren           #+#    #+#             */
/*   Updated: 2022/06/24 14:38:25 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	memfree(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		free(s[i++]);
}

int	main(int argc, char **argv)
{
	t_map	map;

	if (argc != 2)
		return (write(1, "Please give a path map\n", 24), 0);
	if (parse_map(argv[1], &map) == 1)
		return (0);
}
