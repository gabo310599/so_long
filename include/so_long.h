/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 20:16:41 by gojeda            #+#    #+#             */
/*   Updated: 2025/06/04 16:41:26 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <fcntl.h>
# include <unistd.h>


typedef struct s_game
{
	mlx_t	*mlx;	
} t_game;

# define TILE	64
/*****************************************************************************/
//Error messages
# define ARG_ERROR "ERROR\nSolo debes pasar un mapa como argumento!"
# define OPEN_ERROR "ERRROR\nError al abrir el archivo del mapa"
# define EMPTY_MAP_ERROR "ERROR\nEl archivo esta vacio"
# define NO_REC_MAP_ERROR "ERROR\nEl mapa no es rectangular"
# define BER_ERROR "ERROR\nLa extension del mapa tiene que ser .ber"
/*****************************************************************************/

/*****************************************************************************/
//Validate map functions
int		map_is_ok(int fd);
int		map_is_rectangle(int fd);
int		ft_strlen_nnl(char *s);
char	**fill_map(int fd, int rows);
void	free_map_error(char **map);
char	*fill_map_line(char *line);
/*****************************************************************************/

#endif
