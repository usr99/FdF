NAME		= fdf
INC			= ./inc
LIBFT		= libft/libft.a
MLX			= minilibx/libmlx.a
SRC			= fdf.c parsing.c display.c keyboard_event.c mouse_event.c transformation.c utils.c display_utils.c color_gradient.c bresenham.c parsing_utils.c
OBJ_DIR		= objs/
OBJ			= ${addprefix ${OBJ_DIR}, ${SRC:.c=.o}}
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -g

${OBJ_DIR}%.o:	src/%.c
			@${CC} ${CFLAGS} -c $< -o $@
			@echo "$<"

${NAME}:	${OBJ_DIR} ${OBJ} ${LIBFT} ${MLX} ${INC}
			@${CC} ${CFLAGS} -o $@ ${OBJ} ${LIBFT} ${MLX} -I ${INC} -lXext -lX11 -lm

${OBJ_DIR}:
			@mkdir -p ${OBJ_DIR}
			@echo "Creating objs/ directory..."

${LIBFT}:	
			@echo "Compiling libft..."
			@${MAKE} bonus -C libft

${MLX}:
			@echo "Compiling minilibx..."
			@${MAKE} -C minilibx

all:		${NAME}

clean:
			@rm -rf ${OBJ_DIR}
			@${MAKE} clean -C libft
			@${MAKE} clean -C minilibx

fclean:		clean
			@rm -rf ${NAME}
			@${MAKE} fclean -C libft

re: 		fclean all

.PHONY: 	all clean fclean re