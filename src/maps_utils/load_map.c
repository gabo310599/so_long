/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 22:56:13 by gojeda            #+#    #+#             */
/*   Updated: 2025/06/25 23:50:08 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

char	**copy_map(char **map)
{
	int		i;
	char	**copy;

	i = 0;
	while (map[i])
		i++;
	copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (map[i])
	{
		copy[i] = ft_strdup(map[i]);
		if (!copy[i])
			return (free_split(copy), NULL);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

static void	count_coins_in_map(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map_heigh)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == 'C')
				game->coins++;
			x++;
		}
		y++;
	}
}

static bool	all_targets_reachable(char **map)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'C' || map[y][x] == 'E')
				return (false);
			x++;
		}
		y++;
	}
	return (true);
}

bool	is_valid_path(t_game *game)
{
	char	**copy;

	copy = copy_map(game->map);
	if (!copy)
		return (false);
	flood_fill(copy, game->player_pos.x, game->player_pos.y);
	if (!all_targets_reachable(copy))
		return (free_split(copy), false);
	free_split(copy);
	return (true);
}

bool	load_game_map(t_game *game, const char *filepath)
{
	char	*content;

	content = get_file_contents(filepath);
	if (!content)
		return (ft_printf(FILE_ERROR), false);
	game->map = ft_split(content, '\n');
	free(content);
	if (!game->map || !game->map[0])
		return (ft_printf(EMPTY_MAP_ERROR), false);
	game->map_heigh = get_map_height(game->map);
	game->map_width = get_map_width(game->map);
	game->coins = 0;
	game->moves = 0;
	count_coins_in_map(game);
	find_player_in_map(game);
	if (!is_valid_path(game))
		return (ft_printf(INV_PATH_ERROR), free_split(game->map), false);
	return (true);
}
