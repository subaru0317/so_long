/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smihata <smihata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 17:09:19 by smihata           #+#    #+#             */
/*   Updated: 2023/12/01 16:54:05 by smihata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include "libft/libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h> // tmp

typedef struct map
{
	char	**map;
	int		h;
	int		w;
}	t_map;

int		is_error_map(char** map);
int		is_rectangle(char **map, int h, int w);
void	dfs(char **map, int **seen, int current_h, int current_w, int h, int w);
void	ft_error();
int		is_path_between_P_to_E(char **map, int h, int w);
int		is_map_surrounded_by_walls(char **map, int h, int w);
int		is_valid_map_components(char **map, int h, int w);
int		measure_map_width(char **map);
int		measure_map_height(char **map);

// get_next_line_utils.c
char	*ft_strnjoin(char *s1, char *s2, size_t len);
size_t	ft_strchr_len(char *s, char c);
char	*free_all(char **line, char **save);

// get_next_line.c
char	*get_next_line(int fd);

#endif