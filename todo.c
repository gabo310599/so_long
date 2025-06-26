void	control_game(t_game *game)
{
	render_map(game);
	mlx_close_hook(game->mlx, close_game, &game);
	mlx_key_hook(game->mlx, handle_input, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
}
static void	update_player_position(t_game *game, int new_x, int new_y)
{
	int				i;
	mlx_instance_t	*inst;

	i = 0;
	while (i < 4)
		game->img_player[i++]->instances[0].enabled = false;
	inst = &game->img_player[game->anim_index]->instances[0];
	inst->x = new_x * TILE_SIZE;
	inst->y = new_y * TILE_SIZE;
	inst->enabled = true;
	mlx_set_instance_depth(inst, 1);
	game->player_pos.x = new_x;
	game->player_pos.y = new_y;
}

static void	move_player(t_game *game, int dx, int dy)
{
	int		new_x;
	int		new_y;
	char	tile;

	new_x = game->player_pos.x + dx;
	new_y = game->player_pos.y + dy;
	tile = game->map[new_y][new_x];
	if (tile == '1')
		return ;
	if (tile == 'C')
	{
		game->coins--;
		game->map[new_y][new_x] = '0';
	}
	if ((tile == 'E' && game->coins == 0) || tile == 'M')
		close_game(game);
	game->map[game->player_pos.y][game->player_pos.x] = '0';
	game->map[new_y][new_x] = 'P';
	game->anim_index = (game->anim_index + 1) % 4;
	update_player_position(game, new_x, new_y);
	game->moves++;
	ft_printf("📦 Movimientos: %d\n", game->moves);
}

void	handle_input(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.action != MLX_PRESS)
		return ;
	if (keydata.key == MLX_KEY_ESCAPE)
		close_game(game);
	else if (keydata.key == MLX_KEY_W)
		move_player(game, 0, -1);
	else if (keydata.key == MLX_KEY_S)
		move_player(game, 0, 1);
	else if (keydata.key == MLX_KEY_A)
		move_player(game, -1, 0);
	else if (keydata.key == MLX_KEY_D)
		move_player(game, 1, 0);
}
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
char	**copy_map(char **map)
{
	int		i;
	char	**copy;

	i = 0;
	while (map[i])
		i++;
	copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (map[i])
	{
		copy[i] = ft_strdup(map[i]);
		if (!copy[i])
			return (free_split(copy), NULL);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

static void	count_coins_in_map(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map_heigh)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == 'C')
				game->coins++;
			x++;
		}
		y++;
	}
}

static bool	all_targets_reachable(char **map)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'C' || map[y][x] == 'E')
				return (false);
			x++;
		}
		y++;
	}
	return (true);
}

bool	is_valid_path(t_game *game)
{
	char	**copy;

	copy = copy_map(game->map);
	if (!copy)
		return (false);
	flood_fill(copy, game->player_pos.x, game->player_pos.y);
	if (!all_targets_reachable(copy))
		return (free_split(copy), false);
	free_split(copy);
	return (true);
}

bool	load_game_map(t_game *game, const char *filepath)
{
	char	*content;

	content = get_file_contents(filepath);
	if (!content)
		return (ft_printf(FILE_ERROR), false);
	game->map = ft_split(content, '\n');
	free(content);
	if (!game->map || !game->map[0])
		return (ft_printf(EMPTY_MAP_ERROR), false);
	game->map_heigh = get_map_height(game->map);
	game->map_width = get_map_width(game->map);
	game->coins = 0;
	game->moves = 0;
	count_coins_in_map(game);
	find_player_in_map(game);
	if (!is_valid_path(game))
		return (ft_printf(INV_PATH_ERROR), free_split(game->map), false);
	return (true);
}

char	*get_file_contents(const char *filepath)
{
	int		fd;
	char	*line;
	char	*content;
	char	*tmp;

	content = ft_strdup("");
	fd = open(filepath, O_RDONLY);
	if (fd < 0 || !content)
		return (NULL);
	line = get_next_line(fd);
	while (line)
	{
		tmp = content;
		content = ft_strjoin(content, line);
		free(tmp);
		free(line);
		if (!content)
			return (close(fd), NULL);
		line = get_next_line(fd);
	}
	close(fd);
	return (content);
}
static void	count_requiered_element(char c, int *player, int *exit, int *coin)
{
	if (c == 'P')
		(*player)++;
	if (c == 'E')
		(*exit)++;
	if (c == 'C')
		(*coin)++;
}

static bool	is_rectangular(char **lines)
{
	size_t	len;
	int		i;

	len = ft_strlen(lines[0]);
	i = 1;
	while (lines[i])
	{
		if (ft_strlen(lines[i]) != len)
			return (false);
		i++;
	}
	return (true);
}

static bool	is_surrounded_by_walls(char **map)
{
	size_t	cols;
	int		rows;
	int		i;

	cols = ft_strlen(map[0]);
	rows = 0;
	while (map[rows])
		rows++;
	i = 0;
	while (i < (int) cols)
	{
		if (map[0][i] != '1' || map[rows - 1][i] != '1')
			return (false);
		i++;
	}
	i = 1;
	while (i < rows)
	{
		if (map[i][0] != '1' || map[i][cols - 1] != '1')
			return (false);
		i++;
	}
	return (true);
}

static bool	has_required_elements(char **map)
{
	int	i;
	int	j;
	int	player;
	int	exit;
	int	coin;

	player = 0;
	exit = 0;
	coin = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!ft_strchr("10PECM", map[i][j]))
				return (false);
			count_requiered_element(map[i][j], &player, &exit, &coin);
			j++;
		}
		i++;
	}
	return (player == 1 && exit == 1 && coin >= 1);
}

bool	validate_map_file(const char *filepath)
{
	char	**lines;
	char	*content;

	content = get_file_contents(filepath);
	if (!content)
		return (ft_printf(FILE_ERROR), false);
	lines = ft_split(content, '\n');
	free(content);
	if (!lines || !lines[0])
		return (ft_printf(EMPTY_MAP_ERROR), false);
	if (!is_rectangular(lines))
		return (ft_printf(NO_REC_MAP_ERROR), free_split(lines), false);
	if (!is_surrounded_by_walls(lines))
		return (ft_printf(WALLS_ERROR), free_split(lines), false);
	if (!has_required_elements(lines))
		return (ft_printf(ELEMENTS_ERROR), free_split(lines), false);
	free_split(lines);
	return (true);
}
bool	init_window(t_game *game)
{
	game->mlx = mlx_init(game->map_width * TILE_SIZE,
			game->map_heigh * TILE_SIZE, "so_long", false);
	if (!game->mlx)
		return (ft_printf(INIT_MLX_ERROR), false);
	return (true);
}

static bool	load_player_textures(t_game *game)
{
	mlx_texture_t	*tex;

	tex = mlx_load_png("textures/player2.png");
	if (!tex)
		return (ft_printf(LOAD_TEXTURE_ERROR), false);
	game->img_player[1] = mlx_texture_to_image(game->mlx, tex);
	mlx_delete_texture(tex);
	mlx_resize_image(game->img_player[1], TILE_SIZE, TILE_SIZE);
	tex = mlx_load_png("textures/player3.png");
	if (!tex)
		return (ft_printf(LOAD_TEXTURE_ERROR), false);
	game->img_player[2] = mlx_texture_to_image(game->mlx, tex);
	mlx_delete_texture(tex);
	mlx_resize_image(game->img_player[2], TILE_SIZE, TILE_SIZE);
	tex = mlx_load_png("textures/player4.png");
	if (!tex)
		return (ft_printf(LOAD_TEXTURE_ERROR), false);
	game->img_player[3] = mlx_texture_to_image(game->mlx, tex);
	mlx_delete_texture(tex);
	mlx_resize_image(game->img_player[3], TILE_SIZE, TILE_SIZE);
	return (true);
}

bool	load_textures1(t_game *game)
{
	mlx_texture_t	*tex;

	tex = mlx_load_png("textures/floor.png");
	if (!tex)
		return (ft_printf(LOAD_TEXTURE_ERROR), false);
	game->img_floor = mlx_texture_to_image(game->mlx, tex);
	mlx_delete_texture(tex);
	mlx_resize_image(game->img_floor, TILE_SIZE, TILE_SIZE);
	tex = mlx_load_png("textures/wall.png");
	if (!tex)
		return (ft_printf(LOAD_TEXTURE_ERROR), false);
	game->img_wall = mlx_texture_to_image(game->mlx, tex);
	mlx_delete_texture(tex);
	mlx_resize_image(game->img_wall, TILE_SIZE, TILE_SIZE);
	tex = mlx_load_png("textures/exit.png");
	if (!tex)
		return (ft_printf(LOAD_TEXTURE_ERROR), false);
	game->img_exit = mlx_texture_to_image(game->mlx, tex);
	mlx_delete_texture(tex);
	mlx_resize_image(game->img_exit, TILE_SIZE, TILE_SIZE);
	return (true);
}

bool	load_textures2(t_game *game)
{
	mlx_texture_t	*tex;

	tex = mlx_load_png("textures/player1.png");
	if (!tex)
		return (ft_printf(LOAD_TEXTURE_ERROR), false);
	game->img_player[0] = mlx_texture_to_image(game->mlx, tex);
	mlx_delete_texture(tex);
	mlx_resize_image(game->img_player[0], TILE_SIZE, TILE_SIZE);
	if (!load_player_textures(game))
		return (ft_printf(LOAD_TEXTURE_ERROR), false);
	tex = mlx_load_png("textures/enemy.png");
	if (!tex)
		return (ft_printf(LOAD_TEXTURE_ERROR), false);
	game->img_enemy = mlx_texture_to_image(game->mlx, tex);
	mlx_delete_texture(tex);
	mlx_resize_image(game->img_enemy, TILE_SIZE, TILE_SIZE);
	tex = mlx_load_png("textures/coin.png");
	if (!tex)
		return (ft_printf(LOAD_TEXTURE_ERROR), false);
	game->img_coin = mlx_texture_to_image(game->mlx, tex);
	mlx_delete_texture(tex);
	mlx_resize_image(game->img_coin, TILE_SIZE, TILE_SIZE);
	return (true);
}
static void	delete_player_img(t_game *game)
{
	if (game->img_player[0])
		mlx_delete_image(game->mlx, game->img_player[0]);
	if (game->img_player[1])
		mlx_delete_image(game->mlx, game->img_player[1]);
	if (game->img_player[2])
		mlx_delete_image(game->mlx, game->img_player[2]);
	if (game->img_player[3])
		mlx_delete_image(game->mlx, game->img_player[3]);
}

void	close_game(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (!game)
		return ;
	delete_player_img(game);
	if (game->img_wall)
		mlx_delete_image(game->mlx, game->img_wall);
	if (game->img_floor)
		mlx_delete_image(game->mlx, game->img_floor);
	if (game->img_coin)
		mlx_delete_image(game->mlx, game->img_coin);
	if (game->img_exit)
		mlx_delete_image(game->mlx, game->img_exit);
	if (game->img_enemy)
		mlx_delete_image(game->mlx, game->img_enemy);
	free_split(game->map);
	if (game->mlx)
		mlx_terminate(game->mlx);
	ft_printf("👋 Juego cerrado correctamente.\n");
	exit(0);
}

static void	render_elements(t_game *game, char tile, int px, int py)
{
	int	i;

	if (tile == '1')
		mlx_image_to_window(game->mlx, game->img_wall, px, py);
	else if (tile == 'P')
	{
		i = 0;
		while (i < 4)
		{
			mlx_image_to_window(game->mlx, game->img_player[i], px, py);
			game->img_player[i]->instances[0].enabled = (i == 0);
			mlx_set_instance_depth(&game->img_player[i]->instances[0], 1);
			i++;
		}
		game->player_pos.x = px / TILE_SIZE;
		game->player_pos.y = py / TILE_SIZE;
		game->anim_index = 0;
	}
	else if (tile == 'C')
		mlx_image_to_window(game->mlx, game->img_coin, px, py);
	else if (tile == 'E')
		mlx_image_to_window(game->mlx, game->img_exit, px, py);
	else if (tile == 'M')
		mlx_image_to_window(game->mlx, game->img_enemy, px, py);
}

void	render_map(t_game *game)
{
	int	y;
	int	x;
	int	px;
	int	py;

	px = 0;
	py = 0;
	y = 0;
	while (y < game->map_heigh)
	{
		x = 0;
		while (x < game->map_width)
		{
			px = x * TILE_SIZE;
			py = y * TILE_SIZE;
			mlx_image_to_window(game->mlx, game->img_floor, px, py);
			mlx_set_instance_depth(&game->img_floor->instances[0], 0);
			render_elements(game, game->map[y][x], px, py);
			x++;
		}
		y++;
	}
}
void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
		i++;
	while (i)
		free(split[--i]);
	free(split);
}

int	get_map_height(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

int	get_map_width(char **map)
{
	if (!map || !map[0])
		return (0);
	return (ft_strlen(map[0]));
}

void	find_player_in_map(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map_heigh)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == 'P')
			{
				game->player_pos.x = x;
				game->player_pos.y = y;
			}
			x++;
		}
		y++;
	}
}

void	flood_fill(char **map, int x, int y)
{
	if (map[y][x] == '1' || map[y][x] == 'F' || map[y][x] == 'M')
		return ;
	map[y][x] = 'F';
	flood_fill(map, x + 1, y);
	flood_fill(map, x - 1, y);
	flood_fill(map, x, y + 1);
	flood_fill(map, x, y - 1);
}

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
