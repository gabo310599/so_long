/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 22:07:56 by gojeda            #+#    #+#             */
/*   Updated: 2025/06/26 01:30:55 by gojeda           ###   ########.fr       */
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
	ft_printf("TODO BIEN\n");
	return (0);
}
