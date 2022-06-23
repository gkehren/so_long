/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:31:15 by gkehren           #+#    #+#             */
/*   Updated: 2022/06/23 17:07:45 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

char	*get_read_line(int fd, char *save)
{
	char	*line;
	int		bytes;

	bytes = 1;
	line = (char *)malloc(sizeof(char) * 4 + 1);
	if (!line)
		return (NULL);
	while (ft_strchr(save, '\n') == 0 && bytes != 0)
	{
		bytes = read(fd, line, 4);
		if (bytes == -1)
		{
			free(line);
			return (NULL);
		}
		line[bytes] = '\0';
		save = ft_strjoin(save, line);
	}
	free(line);
	return (save);
}

char	*get_write_line(char *save)
{
	int		i;
	char	*temp;

	i = 0;
	if (!save[i])
		return (NULL);
	while (save[i] != '\0' && save[i] != '\n')
		i++;
	temp = (char *)malloc(sizeof(char) * i + 2);
	if (!temp)
		return (NULL);
	i = 0;
	while (save[i] != '\n' && save[i] != '\0')
	{
		temp[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
	{
		temp[i] = '\n';
		i++;
	}
	temp[i] = '\0';
	return (temp);
}

char	*get_new_line(char *save)
{
	int		i;
	char	*temp;

	i = 0;
	while (save[i] != '\n' && save[i] != '\0')
		i++;
	if (!save[i])
	{
		free(save);
		return (NULL);
	}
	temp = (char *)malloc(sizeof(char) * ft_strlen(save) - i + 1);
	if (!temp)
		return (NULL);
	temp = ft_strcpy(temp, save + i + 1);
	free(save);
	return (temp);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save;

	if (fd < 0)
		return (NULL);
	save = get_read_line(fd, save);
	if (!save)
		return (NULL);
	line = get_write_line(save);
	save = get_new_line(save);
	return (line);
}
