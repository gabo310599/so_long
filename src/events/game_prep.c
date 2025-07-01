/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_prep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:32:12 by gojeda            #+#    #+#             */
/*   Updated: 2025/07/01 21:51:33 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

//Investigar mlx_hook y ver cambio a la estructura con referencia a la ventana
void	control_game(t_game *game)
{
	render_map(game);
	init_player(game);
	init_coins(game);
	mlx_close_hook(game->mlx, close_game, game);
	mlx_key_hook(game->mlx, handle_input, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
}
