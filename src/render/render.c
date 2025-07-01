/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 03:50:02 by gojeda            #+#    #+#             */
/*   Updated: 2025/07/01 20:00:56 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

void	init_player(t_game *game)
{
	int	i;
	int	px;
	int	py;

	i = 0;
	px = game->player_pos.x * TILE_SIZE;
	py = game->player_pos.y * TILE_SIZE;
	while (i < 4)
	{
		mlx_image_to_window(game->mlx, game->img_player[i], px, py);
		game->img_player[i]->instances[0].enabled = (i == 0);
		i++;
	}
	game->anim_index = 0;
}

void	disable_coin_instance(t_game *game, int x, int y)
{
	uint32_t	i;

	i = 0;
	while (i < game->img_coin->count)
	{
		if (game->img_coin->instances[i].x == x * TILE_SIZE
			&& game->img_coin->instances[i].y == y * TILE_SIZE)
		{
			game->img_coin->instances[i].enabled = false;
			break ;
		}
		i++;
	}
}

void	init_coins(t_game *game)
{
	int		y;
	int		x;

	y = 0;
	while (y < game->map_heigh)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == 'C')
				mlx_image_to_window(game->mlx, game->img_coin,
					x * TILE_SIZE, y * TILE_SIZE);
			x++;
		}
		y++;
	}
}

static void	render_elements(t_game *game, char tile, int px, int py)
{
	if (tile == '1')
		mlx_image_to_window(game->mlx, game->img_wall, px, py);
	else if (tile == 'P')
	{
		mlx_image_to_window(game->mlx, game->img_floor, px, py);
		game->player_pos.x = px / TILE_SIZE;
		game->player_pos.y = py / TILE_SIZE;
		game->anim_index = 0;
	}
	else if (tile == 'E')
		mlx_image_to_window(game->mlx, game->img_exit, px, py);
	else if (tile == 'M')
		mlx_image_to_window(game->mlx, game->img_enemy, px, py);
}

void	render_map(t_game *game)
{
	int		y;
	int		x;
	int		px;
	int		py;

	px = 0;
	py = 0;
	y = 0;
	while (y < game->map_heigh)
	{
		x = 0;
		while (x < game->map_width)
		{
			px = x * TILE_SIZE;
			py = y * TILE_SIZE;
			mlx_image_to_window(game->mlx, game->img_floor, px, py);
			mlx_set_instance_depth(&game->img_floor->instances[0], 0);
			render_elements(game, game->map[y][x], px, py);
			x++;
		}
		y++;
	}
	update_move_text(game);
}
