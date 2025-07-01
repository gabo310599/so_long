/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:29:16 by gojeda            #+#    #+#             */
/*   Updated: 2025/06/27 22:18:28 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

static void	update_player_position(t_game *game, int new_x, int new_y)
{
	int	i;
	int	px;
	int	py;

	i = 0;
	while (i < 4)
		game->img_player[i++]->instances[0].enabled = 0;
	game->player_pos.x = new_x;
	game->player_pos.y = new_y;
	px = new_x * TILE_SIZE;
	py = new_y * TILE_SIZE;
	i = 0;
	while (i < 4)
	{
		game->img_player[i]->instances[0].x = px;
		game->img_player[i]->instances[0].y = py;
		i++;
	}
	game->img_player[game->anim_index]->instances[0].enabled = 1;
}

static void	move_player(t_game *game, int dx, int dy)
{
	int		new_x;
	int		new_y;
	char	tile;

	new_x = game->player_pos.x + dx;
	new_y = game->player_pos.y + dy;
	tile = game->map[new_y][new_x];
	if (tile == '1')
		return ;
	if (tile == 'C')
	{
		game->coins--;
		game->map[new_y][new_x] = '0';
		disable_coin_instance(game, new_x, new_y);
	}
	if ((tile == 'E' && game->coins == 0) || tile == 'M')
		close_game(game);
	if (game->map[game->player_pos.y][game->player_pos.x] != 'E')
		game->map[game->player_pos.y][game->player_pos.x] = '0';
	if (tile != 'E')
		game->map[new_y][new_x] = 'P';
	game->anim_index = (game->anim_index + 1) % 4;
	update_player_position(game, new_x, new_y);
	game->moves++;
	ft_printf("📦 Movimientos: %d\n", game->moves);
}

void	handle_input(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.action != MLX_PRESS)
		return ;
	if (keydata.key == MLX_KEY_ESCAPE)
		close_game(game);
	else if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP)
		move_player(game, 0, -1);
	else if (keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN)
		move_player(game, 0, 1);
	else if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_LEFT)
		move_player(game, -1, 0);
	else if (keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT)
		move_player(game, 1, 0);
}
