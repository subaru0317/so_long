/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smihata <smihata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:07:36 by smihata           #+#    #+#             */
/*   Updated: 2023/12/01 15:28:52 by smihata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_connect_line_to_save(char **line, char **save)
{
	size_t	len_to_nl;
	char	*tmp;

	len_to_nl = ft_strchr_len(*save, '\n');
	if (len_to_nl >= 1 && save[0][len_to_nl - 1] == '\n')
	{
		tmp = *line;
		*line = ft_strnjoin(tmp, *save, len_to_nl);
		free(tmp);
		tmp = *save;
		*save = ft_strdup(tmp + len_to_nl);
		free(tmp);
		if (!(*save) || !(*line))
			return (-1);
		return (1);
	}
	else
	{
		*line = ft_strdup(*save);
		if (!(*line))
			return (-1);
		free(*save);
		*save = NULL;
		return (0);
	}
}

int	ft_eof_or_read_error(int read_buf_size, char **line)
{
	if (read_buf_size == 0)
	{
		if (ft_strlen(*line) == 0)
		{
			free(*line);
			*line = NULL;
		}
		return (0);
	}
	else
		return (1);
}

int	ft_update_save(char buf[BUFFER_SIZE + 1], char **save, size_t len_to_nl)
{
	free(*save);
	if (ft_strlen(buf) == 1)
		*save = NULL;
	else
	{
		*save = ft_strdup(buf + len_to_nl);
		if (!(*save))
			return (1);
	}
	return (0);
}

int	ft_get_new_line(int fd, char **line, char **save)
{
	char	buf[BUFFER_SIZE + 1];
	char	*tmp_line;
	ssize_t	read_buf_size;
	size_t	len_to_nl;

	while (1)
	{
		read_buf_size = read(fd, buf, BUFFER_SIZE);
		if (read_buf_size <= 0)
			return (ft_eof_or_read_error(read_buf_size, line));
		buf[read_buf_size] = '\0';
		len_to_nl = ft_strchr_len(buf, '\n');
		tmp_line = *line;
		*line = ft_strnjoin(tmp_line, buf, len_to_nl);
		if (!(*line))
			return (1);
		free(tmp_line);
		tmp_line = NULL;
		if (line[0][ft_strlen(*line) - 1] == '\n')
			return (ft_update_save(buf, save, len_to_nl));
	}
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save;
	int			line_have_nl;
	int			error;

	if (fd < 0)
		return (NULL);
	line = NULL;
	if (save)
	{
		line_have_nl = ft_connect_line_to_save(&line, &save);
		if (line_have_nl == -1)
			return (free_all(&line, &save));
		if (line_have_nl == 1)
			return (line);
	}
	error = ft_get_new_line(fd, &line, &save);
	if (error)
		return (free_all(&line, &save));
	return (line);
}

// #include <fcntl.h>
// #include <stdio.h>
// int	main(void)
// {
// 	char	*line;
// 	int		i;
// 	int		fd1;
// 	fd1 = open("test.txt", O_RDONLY);
// 	i = 1;
// 	while (i < 7)
// 	{
// 		line = get_next_line(fd1);
// 		printf("line [%02d]: %s", i, line);
// 		free(line);
// 		i++;
// 	}
// 	close(fd1);
// 	return (0);
// }

// __attribute__((destructor))
// static void destructor(void){
//     system("leaks -q a.out");
// }