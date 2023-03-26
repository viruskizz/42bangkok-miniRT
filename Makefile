NAME		= miniRT
CC			= gcc -g
CFLAGS		= -Wall -Wextra -Werror
PTHREAD 	= -pthread
RM			= /bin/rm -f

LIBFT_DIR	= ./libft

INCLUDE_DIR	= ./includes

UNAME = $(shell uname -s)
ifeq ($(UNAME), Linux)
	MLX_DIR		= mlx_Linux
	MLX_FLAGS	= -Imlx_Linux -Lmlx_Linux -lmlx_Linux -lXext -lX11 -lm -lz
	INCLUDES 	= -I$(INCLUDE_DIR) \
				  -I$(LIBFT_DIR) \
				  -I/usr/include
	LIBS		= -L$(LIBFT_DIR) -lft \
				  -L/usr/lib
else
	MLX_DIR		= mlx
	MLX_FLAGS	= -L$(MLX_DIR) -lmlx \
				  -framework OpenGL \
				  -framework AppKit
	INCLUDES 	= -I$(INCLUDE_DIR) \
				  -I$(LIBFT_DIR) \
				  -I$(PRINTF_DIR) \
				  -I$(MLX_DIR)
	LIBS		= -L$(LIBFT_DIR) -lft
endif

BUILD_DIR	= build
SRC_DIR		= srcs
SRCS = $(shell find $(SRC_DIR) -name '*.c')
OBJS = $(SRCS:%.c=$(BUILD_DIR)/%.o)

all: $(NAME)

restart: cbuild $(OBJS)
	$(CC) $(CFLAGS) $(PTHREAD) $(OBJS) $(INCLUDES) $(LIBS) $(MLX_FLAGS) -o $(NAME)

$(NAME): $(OBJS) libs
	$(CC) $(CFLAGS) $(PTHREAD) $(OBJS) $(LIBS) $(MLX_FLAGS) -o $(NAME)

$(OBJS): $(BUILD_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) -g $(CFLAGS) $(INCLUDES) -c $< -o $@

libs:
	@make -C $(LIBFT_DIR)
	@make -C $(MLX_DIR)

bonus: all

re: fclean all

cbuild:
	-$(RM) -r $(BUILD_DIR)

norminette:
	make norminette -C $(LIBFT_DIR)
	norminette -R CheckforbiddenSourceHeader $(SRCS)
	norminette -R CheckDefine $(INCLUDE_DIR)/*.h

clean:
	make clean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)
	$(RM) -r $(BUILD_DIR)

fclean:
	make fclean -C $(LIBFT_DIR)
	make fclean -C $(MLX_DIR)
	$(RM) -r $(BUILD_DIR)
	$(RM) $(NAME)

.PHONY: bonus cbuild libs restart norminette all clean fclean re
