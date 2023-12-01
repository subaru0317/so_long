/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smihata <smihata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 20:40:43 by smihata           #+#    #+#             */
/*   Updated: 2023/12/01 17:25:29 by smihata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_error_map(char** map)
{
	int	h;
	int	w;

	h = measure_map_height(map);
	w = measure_map_width(map);
	// mapが長方形であることを確認する
	if (!is_rectangle(map, h, w))
	{
		ft_putendl_fd("Map is not rectangle.\n", STDERR_FILENO);
		return (1);
	}
	// EまたはPが重複してマップに存在する場合、Errorとなる
	// 少なくともEが1つ、Cが1つ、Pが1つ存在すること
	if (!is_valid_map_components(map, h, w))
	{
		ft_putendl_fd("Map have invalid components.\n", STDERR_FILENO);
		return (1);
	}
	// mapが壁で囲まれていることを確認する
	// 1で囲まれているか？
	if (!is_map_surrounded_by_walls(map, h, w))
	{
		ft_putendl_fd("Map is not surrounded by walls.\n", STDERR_FILENO);
		return (1);
	}
	// map内に有効な通路があることを確認する
	// P-E間が0 or Cで繋がっているか？
	if (!is_path_between_P_to_E(map, h, w))
	{
		ft_putendl_fd("Map has no valid path.\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}

int	is_rectangle(char **map, int h, int w)
{
	int	i;

	i = 0;
	while (i < h)
	{
		if (w != (int)ft_strlen(map[i]))
			return (0);
		i++;
	}
	return (1);
}

void	dfs(char **map, int **seen, int current_h, int current_w, int h, int w)
{
	int	dx[4] = {1, 0, -1, 0};
	int	dy[4] = {0, 1, 0, -1};
	int	dir;
	int	next_h;
	int	next_w;

	dir = 0;
	while (dir < 4)
	{
		next_h = current_h + dx[dir];
		next_w = current_w + dy[dir];
		if (next_h < 0 || next_h >= h || next_w < 0 || next_w >= w)
			continue ;
		if (map[next_h][next_w] == '1')
			continue ;
		if (seen[next_h][next_w])
			continue ;
		dfs(map, seen, next_h, next_w, h, w);
		dir++;
	}
}

void	ft_error()
{
	exit(1);
}

// 深さ優先探索とかで作る。
// 構造体を作成するか？
// {
// 	map
// 	startの座標
// 	goalの座標
// 	mapの高さ
// 	mapの幅
// }
int	is_path_between_P_to_E(char **map, int h, int w)
{
	int	player_h;
	int	player_w;
	int	exit_h;
	int	exit_w;
	int	i;
	int	j;
	int	**seen;

	i = 0;
	j = 0;
	while (i < h)
	{
		while (j < w)
		{
			if (map[i][j] == 'P')
			{
				player_h = i;
				player_w = j;
			}
			if (map[i][j] == 'E')
			{
				exit_h = i;
				exit_w = j;
			}
			++j;
		}
		++i;
	}
	i = 0;
	j = 0;
	seen = NULL;
	while (i < h)
	{
		seen[i] = (int *)ft_calloc(w, sizeof(int));
		if (!seen[i])
			ft_error();
		++i;
	}
	dfs(map, seen, player_h, player_w, h, w);
	if (seen[exit_h][exit_w])
		return (1);
	return (0);
}


int	is_map_surrounded_by_walls(char **map, int h, int w)
{
	int	i;
	int	j;

	j = 0;
	while (j < w)
	{
		if (map[0][j] != '1' || map[h - 1][j] != '1')
			return (0);
	}
	i = 0;
	while (j < w)
	{
		if (map[i][0] != '1' || map[i][w - 1] != '1')
			return (0);
	}
	return (1);
}

int	is_valid_map_components(char **map, int h, int w)
{
	int	i = 0;
	int	j = 0;
	int cntE = 0;
	int cntP = 0;
	int cntC = 0;

	while (i < w)
	{
		while (j < h)
		{
			if (map[i][j] == 'E')
				cntE++;
			if (map[i][j] == 'P')
				cntP++;
			if (map[i][j] == 'C')
				cntC++;
			j++;
		}
		i++;
	}
	if (cntE == 1 && cntP == 1 && cntC >= 1)
		return (1);
	return (0);
}

int	measure_map_width(char **map)
{
	int w;

	w = ft_strlen(map[0]);
	return (w);
}

int measure_map_height(char **map)
{

	int	h;

	h = 0;
	while (map[h][0])
	{
		h++;
		printf("aaa\n");
	}
	return (h);
}


t_map build_map(char *map_file_path)
{
	int		fd;
	char	*line;
	int		i;
	t_map	map;
	int		line_len;

	fd = open(map_file_path, O_RDONLY);
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		line_len = ft_strlen(line);
		map.map[i] = (char *)malloc(sizeof(char) * (line_len + 1));
		ft_strlcpy(map.map[i], line, line_len);
		i++;
	}
	close(fd);
	map.h = i;
	// map.w = measure_map_width(map.map);
	return (map);
}


#include <stdio.h>
int main(void)
{
	t_map	map;
	map = build_map("maps/sample_map1.ber");
	// printf("!\n");
	// for(int i = 0; i < map.h; ++i)
	// 	printf("%s\n", map.map[i]);
	
	return (0);
}

__attribute__((destructor))
static void destructor(void){
    system("leaks -q so_long");
}