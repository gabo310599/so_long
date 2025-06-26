/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 03:50:02 by gojeda            #+#    #+#             */
/*   Updated: 2025/06/26 14:22:43 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

static void	delete_player_img(t_game *game)
{
	if (game->img_player[0])
		mlx_delete_image(game->mlx, game->img_player[0]);
	if (game->img_player[1])
		mlx_delete_image(game->mlx, game->img_player[1]);
	if (game->img_player[2])
		mlx_delete_image(game->mlx, game->img_player[2]);
	if (game->img_player[3])
		mlx_delete_image(game->mlx, game->img_player[3]);
}

void	close_game(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (!game)
		return ;
	delete_player_img(game);
	if (game->img_wall)
		mlx_delete_image(game->mlx, game->img_wall);
	if (game->img_floor)
		mlx_delete_image(game->mlx, game->img_floor);
	if (game->img_coin)
		mlx_delete_image(game->mlx, game->img_coin);
	if (game->img_exit)
		mlx_delete_image(game->mlx, game->img_exit);
	if (game->img_enemy)
		mlx_delete_image(game->mlx, game->img_enemy);
	free_split(game->map);
	if (game->mlx)
		mlx_terminate(game->mlx);
	ft_printf("👋 Juego cerrado correctamente.\n");
	exit(0);
}

static void	render_elements(t_game *game, char tile, int px, int py)
{
	int	i;

	if (tile == '1')
		mlx_image_to_window(game->mlx, game->img_wall, px, py);
	else if (tile == 'P')
	{
		i = 0;
		while (i < 4)
		{
			mlx_image_to_window(game->mlx, game->img_player[i], px, py);
			game->img_player[i]->instances[0].enabled = (i == 0);
			mlx_set_instance_depth(&game->img_player[i]->instances[0], 1);
			i++;
		}
		game->player_pos.x = px / TILE_SIZE;
		game->player_pos.y = py / TILE_SIZE;
		game->anim_index = 0;
	}
	else if (tile == 'C')
		mlx_image_to_window(game->mlx, game->img_coin, px, py);
	else if (tile == 'E')
		mlx_image_to_window(game->mlx, game->img_exit, px, py);
	else if (tile == 'M')
		mlx_image_to_window(game->mlx, game->img_enemy, px, py);
}

void	render_map(t_game *game)
{
	int	y;
	int	x;
	int	px;
	int	py;

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
}
