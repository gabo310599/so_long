/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 21:21:28 by gojeda            #+#    #+#             */
/*   Updated: 2025/07/01 21:53:36 by gojeda           ###   ########.fr       */
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
	if (game->move_text)
		mlx_delete_image(game->mlx, game->move_text);
	free_split(game->map);
	if (game->mlx)
		mlx_terminate(game->mlx);
	ft_memset(game, 0, sizeof(t_game));
	ft_printf("👋 Juego cerrado correctamente.\n");
	exit(0);
}
