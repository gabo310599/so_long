/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 19:22:29 by gojeda            #+#    #+#             */
/*   Updated: 2025/07/01 19:51:25 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

static void	int_to_str(int n, char *str)
{
	int		i;
	int		j;
	char	temp[12];

	i = 0;
	if (n == 0)
	{
		str[0] = '0';
		str[1] = '\0';
		return ;
	}
	while (n > 0)
	{
		temp[i++] = (n % 10) + '0';
		n /= 10;
	}
	j = 0;
	while (i > 0)
		str[j++] = temp[--i];
	str[j] = '\0';
}

void	update_move_text(t_game *game)
{
	char		str[32];
	char		num_str[12];
	const char	*prefix;
	int			i;
	int			j;

	prefix = "Movimientos: ";
	i = 0;
	int_to_str(game->moves, num_str);
	while (prefix[i])
	{
		str[i] = prefix[i];
		i++;
	}
	j = 0;
	while (num_str[j])
		str[i++] = num_str[j++];
	str[i] = '\0';
	mlx_delete_image(game->mlx, game->move_text);
	game->move_text = mlx_put_string(game->mlx, str, 10, 10);
}
