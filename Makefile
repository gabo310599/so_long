NAME = so_long

CC = cc
CFLAGS = -Wall -Werror -Wextra -g

SRCS = src/so_long.c \

OBJS = $(SRCS:.c=.o)

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

#-----------------------------------------------------------
# Compilar archivos fuente
#-----------------------------------------------------------
clean:
	@rm -f $(OBJS)
	@$(MAKE) -C libft clean > /dev/null
	-@$(MAKE) -C MLX42/build clean > /dev/null 2>&1 || true
	@echo "🧹 Archivos objeto y temporales eliminados."

fclean: clean
	@rm -f $(NAME)
	@rm -f MLX42/build/libmlx42.a
	@rm -rf MLX42/build
	@$(MAKE) -C libft fclean > /dev/null
	@echo "🧼 Todo limpio: binarios, Libft y MLX42."

re: fclean all

.PHONY: all clean fclean re bonus libmlx