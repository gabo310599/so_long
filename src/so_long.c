/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 20:44:48 by gojeda            #+#    #+#             */
/*   Updated: 2025/05/30 21:29:06 by gojeda           ###   ########.fr       */
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
