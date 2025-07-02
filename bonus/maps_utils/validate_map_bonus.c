/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:28:42 by gojeda            #+#    #+#             */
/*   Updated: 2025/06/26 03:17:32 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

static void	count_requiered_element(char c, int *player, int *exit, int *coin)
{
	if (c == 'P')
		(*player)++;
	if (c == 'E')
		(*exit)++;
	if (c == 'C')
		(*coin)++;
}

static bool	is_rectangular(char **lines)
{
	size_t	len;
	int		i;

	len = ft_strlen(lines[0]);
	i = 1;
	while (lines[i])
	{
		if (ft_strlen(lines[i]) != len)
			return (false);
		i++;
	}
	return (true);
}

static bool	is_surrounded_by_walls(char **map)
{
	size_t	cols;
	int		rows;
	int		i;

	cols = ft_strlen(map[0]);
	rows = 0;
	while (map[rows])
		rows++;
	i = 0;
	while (i < (int) cols)
	{
		if (map[0][i] != '1' || map[rows - 1][i] != '1')
			return (false);
		i++;
	}
	i = 1;
	while (i < rows)
	{
		if (map[i][0] != '1' || map[i][cols - 1] != '1')
			return (false);
		i++;
	}
	return (true);
}

static bool	has_required_elements(char **map)
{
	int	i;
	int	j;
	int	player;
	int	exit;
	int	coin;

	player = 0;
	exit = 0;
	coin = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!ft_strchr("10PECM", map[i][j]))
				return (false);
			count_requiered_element(map[i][j], &player, &exit, &coin);
			j++;
		}
		i++;
	}
	return (player == 1 && exit == 1 && coin >= 1);
}

bool	validate_map_file(const char *filepath)
{
	char	**lines;
	char	*content;

	content = get_file_contents(filepath);
	if (!content)
		return (ft_printf(FILE_ERROR), false);
	lines = ft_split(content, '\n');
	free(content);
	if (!lines || !lines[0])
		return (ft_printf(EMPTY_MAP_ERROR), false);
	if (!is_rectangular(lines))
		return (ft_printf(NO_REC_MAP_ERROR), free_split(lines), false);
	if (!is_surrounded_by_walls(lines))
		return (ft_printf(WALLS_ERROR), free_split(lines), false);
	if (!has_required_elements(lines))
		return (ft_printf(ELEMENTS_ERROR), free_split(lines), false);
	free_split(lines);
	return (true);
}
