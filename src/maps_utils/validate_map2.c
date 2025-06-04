/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:28:42 by gojeda            #+#    #+#             */
/*   Updated: 2025/06/04 17:06:45 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

//We fill a line for the map if it is valid line
char	*fill_map_line(char *line, int cols)
{
	char	*map_line;
	int		count_c;
	int		count_p;
	int		count_e;

	count_c = 0;
	count_p = 0;
	count_e = 0;
	while (line[i] && ft_strchr('01CEP', line[i]))
	{
		if (line[i] == 'C')
			count_c++;
		if (line[i] == 'E')
			count_e++;
		if (line[i] == 'P')
			count_p++;
		i++;
	}
}
