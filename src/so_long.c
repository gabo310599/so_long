/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 22:07:56 by gojeda            #+#    #+#             */
/*   Updated: 2025/07/02 17:37:21 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (!check_args(argc, argv))
		return (1);
	if (!validate_map_file(argv[1]))
		return (1);
	if (!load_game_map(&game, argv[1]))
		return (1);
	if (!init_window(&game))
		return (1);
	if (!load_textures1(&game) || !load_textures2(&game))
		return (1);
	game.anim_index = 0;
	control_game(&game);
	return (0);
}
