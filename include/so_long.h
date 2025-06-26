/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 20:16:41 by gojeda            #+#    #+#             */
/*   Updated: 2025/06/26 13:17:31 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdbool.h>

# define TILE_SIZE	64
/*****************************************************************************/
//Game srtuctures
typedef struct s_vec2
{
	int	x;
	int	y;
}	t_vec2;

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*img_player[4];
	mlx_image_t	*img_wall;
	mlx_image_t	*img_floor;
	mlx_image_t	*img_coin;
	mlx_image_t	*img_exit;
	mlx_image_t	*img_enemy;
	char		**map;
	int			map_width;
	int			map_heigh;
	int			coins;
	int			moves;
	int			anim_index;
	t_vec2		player_pos;
}	t_game;
/*****************************************************************************/

/*****************************************************************************/
//Error messages
# define ARG_ERROR "ERROR\n❌ Usa ./so_long <mapa.ber>\n"
# define FILE_ERROR "ERRROR\n❌ Error al abrir y leer el archivo del mapa\n"
# define EMPTY_MAP_ERROR "ERROR\n❌ El archivo esta vacio\n"
# define NO_REC_MAP_ERROR "ERROR\n❌ El mapa no es rectangular\n"
# define BER_ERROR "ERROR\n❌ La extension del mapa tiene que ser .ber\n"
# define WALLS_ERROR "ERROR\n❌ El mapa no está rodeado por paredes\n"
# define ELEMENTS_ERROR "ERROR\n❌ El mapa debe tener 1 P, al menos 1 E y 1 C\n"
# define INV_PATH_ERROR "ERROR\n❌ El mapa no tiene un camino valido\n"
# define INIT_MLX_ERROR "ERROR\n❌ No se pudo iniciar MLX\n"
# define LOAD_TEXTURE_ERROR "ERROR\n❌ Error cargando textura\n"
/*****************************************************************************/

/*****************************************************************************/
//Validate map functions
bool	check_args(int argc, char **argv);
char	*get_file_contents(const char *filepath);
bool	validate_map_file(const char *filepath);
/*****************************************************************************/

/*****************************************************************************/
//Utils for the proyect
void	free_split(char **split);
int		get_map_height(char **map);
int		get_map_width(char **map);
void	find_player_in_map(t_game *game);
void	flood_fill(char **map, int x, int y);
/*****************************************************************************/

/*****************************************************************************/
//Load and render game functions
bool	load_game_map(t_game *game, const char *filepath);
char	**copy_map(char **map);
bool	init_window(t_game *game);
bool	load_textures1(t_game *game);
bool	load_textures2(t_game *game);
void	render_map(t_game *game);
void	close_game(void *param);
/*****************************************************************************/

/*****************************************************************************/
//Events and hooks functions
void	handle_input(mlx_key_data_t keydata, void *param);
void	control_game(t_game *game);
/*****************************************************************************/

#endif
