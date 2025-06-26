/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_prep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:32:12 by gojeda            #+#    #+#             */
/*   Updated: 2025/06/26 13:16:59 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

void	control_game(t_game *game)
{
	render_map(game);
	mlx_close_hook(game->mlx, close_game, &game);
	mlx_key_hook(game->mlx, handle_input, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
}