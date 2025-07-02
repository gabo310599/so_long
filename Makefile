NAME = so_long
NAME_BONUS = so_long_bonus

CC = cc
CFLAGS = -Wall -Werror -Wextra -g

SRCS = src/so_long.c \
		src/utils/utils.c \
		src/utils/utils1.c \
		src/utils/close_game.c \
		src/maps_utils/check_args.c \
		src/maps_utils/load_map.c \
		src/maps_utils/read_file_content.c \
		src/maps_utils/validate_map.c \
		src/render/load_textures.c \
		src/render/render.c \
		src/events/game_prep.c \
		src/events/movements.c
SRCSBONUS = bonus/so_long_bonus.c \
		bonus/utils/utils_bonus.c \
		bonus/utils/utils1_bonus.c \
		bonus/utils/close_game_bonus.c \
		bonus/maps_utils/check_args_bonus.c \
		bonus/maps_utils/load_map_bonus.c \
		bonus/maps_utils/read_file_content_bonus.c \
		bonus/maps_utils/validate_map_bonus.c \
		bonus/render/load_textures_bonus.c \
		bonus/render/render_bonus.c \
		bonus/events/game_prep_bonus.c \
		bonus/events/movements_bonus.c


OBJS = $(SRCS:.c=.o)
OBJSBONUS = $(SRCSBONUS:.c=.o)

INCLUDES = -I include -I libft -I MLX42/include

LIBFT = libft/libft.a
MLX_LIB = MLX42/build/libmlx42.a
MLX_FLAGS = -ldl -lglfw -pthread -lm

#-----------------------------------------------------------
# Principal
#-----------------------------------------------------------
all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -C libft > /dev/null
	@$(MAKE) libmlx
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT) $(MLX_LIB) $(MLX_FLAGS) -o $(NAME)
	@echo "✅ Proyecto compilado correctamente."

#-----------------------------------------------------------
# Compilar archivos fuente
#-----------------------------------------------------------
%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@  > /dev/null
	@echo "🔧 Compilado: $<"

#-----------------------------------------------------------
# Compilar archivos fuente
#-----------------------------------------------------------
libmlx:
	@cmake -B MLX42/build MLX42 > /dev/null
	@make -C MLX42/build -j4 > /dev/null
	@echo "📦 MLX42 compilada."

# --------------------------------------------------------------
# Bonus
# --------------------------------------------------------------
bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJSBONUS)
	@$(MAKE) -C libft > /dev/null
	@$(MAKE) libmlx
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJSBONUS) $(LIBFT) $(MLX_LIB) $(MLX_FLAGS) -o $(NAME_BONUS)
	@echo "✅ Bonus compilado correctamente."

#-----------------------------------------------------------
# Compilar archivos fuente
#-----------------------------------------------------------
clean:
	@rm -f $(OBJS) $(OBJSBONUS)
	@$(MAKE) -C libft clean > /dev/null
	-@$(MAKE) -C MLX42/build clean > /dev/null 2>&1 || true
	@echo "🧹 Archivos objeto y temporales eliminados."

fclean: clean
	@rm -f $(NAME) $(NAME_BONUS)
	@rm -f MLX42/build/libmlx42.a
	@rm -rf MLX42/build
	@$(MAKE) -C libft fclean > /dev/null
	@echo "🧼 Todo limpio: binarios, Libft y MLX42."

re: fclean all

.PHONY: all clean fclean re bonus libmlx