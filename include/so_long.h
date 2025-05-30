/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 20:16:41 by gojeda            #+#    #+#             */
/*   Updated: 2025/05/30 22:08:26 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"


typedef struct s_game
{
	mlx_t	*mlx;	
} t_game;

# define TILE	64
/*****************************************************************************/
//Mensajes error
# define ARG_ERROR "ERROR: solo debes pasar un mapa como argumento!."
/*****************************************************************************/
#endif
