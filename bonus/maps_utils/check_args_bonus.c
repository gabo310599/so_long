/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:28:42 by gojeda            #+#    #+#             */
/*   Updated: 2025/06/25 20:47:56 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

static bool	has_ber_extension(char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 5)
		return (false);
	return (ft_strncmp(filename + len - 4, ".ber", 4) == 0);
}

bool	check_args(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_printf(ARG_ERROR);
		return (false);
	}
	if (!has_ber_extension(argv[1]))
	{
		ft_printf(BER_ERROR);
		return (false);
	}
	return (true);
}
