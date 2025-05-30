/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 22:07:56 by gojeda            #+#    #+#             */
/*   Updated: 2025/05/30 22:08:01 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	main(int argc, char **argv)
{
	t_game	game;
	
	(void)	argv;
	if (argc != 2)
		ft_printf("%s\n", ARG_ERROR);
	game.mlx = mlx_init(1050 * TILE, 1050 * TILE, "so_long", true);
	mlx_loop(game.mlx);
	return (0);
}
