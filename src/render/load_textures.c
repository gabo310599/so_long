/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 03:24:10 by gojeda            #+#    #+#             */
/*   Updated: 2025/07/02 17:32:20 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

bool	init_window(t_game *game)
{
	game->mlx = mlx_init(game->map_width * TILE_SIZE,
			game->map_heigh * TILE_SIZE, "so_long", false);
	if (!game->mlx)
		return (ft_printf(INIT_MLX_ERROR), false);
	return (true);
}

bool	load_textures1(t_game *game)
{
	mlx_texture_t	*tex;

	tex = mlx_load_png("textures/floor.png");
	if (!tex)
		return (ft_printf(LOAD_TEXTURE_ERROR), false);
	game->img_floor = mlx_texture_to_image(game->mlx, tex);
	mlx_delete_texture(tex);
	mlx_resize_image(game->img_floor, TILE_SIZE, TILE_SIZE);
	tex = mlx_load_png("textures/wall.png");
	if (!tex)
		return (ft_printf(LOAD_TEXTURE_ERROR), false);
	game->img_wall = mlx_texture_to_image(game->mlx, tex);
	mlx_delete_texture(tex);
	mlx_resize_image(game->img_wall, TILE_SIZE, TILE_SIZE);
	tex = mlx_load_png("textures/exit.png");
	if (!tex)
		return (ft_printf(LOAD_TEXTURE_ERROR), false);
	game->img_exit = mlx_texture_to_image(game->mlx, tex);
	mlx_delete_texture(tex);
	mlx_resize_image(game->img_exit, TILE_SIZE, TILE_SIZE);
	return (true);
}

bool	load_textures2(t_game *game)
{
	mlx_texture_t	*tex;

	tex = mlx_load_png("textures/player1.png");
	if (!tex)
		return (ft_printf(LOAD_TEXTURE_ERROR), false);
	game->img_player[0] = mlx_texture_to_image(game->mlx, tex);
	mlx_delete_texture(tex);
	mlx_resize_image(game->img_player[0], TILE_SIZE, TILE_SIZE);
	tex = mlx_load_png("textures/coin.png");
	if (!tex)
		return (ft_printf(LOAD_TEXTURE_ERROR), false);
	game->img_coin = mlx_texture_to_image(game->mlx, tex);
	mlx_delete_texture(tex);
	mlx_resize_image(game->img_coin, TILE_SIZE, TILE_SIZE);
	return (true);
}
