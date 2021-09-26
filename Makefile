NAME		= fdf
INC			= ./inc/
LIBFT		= libft/libft.a
MLX			= minilibx/libmlx.a
SRC			= fdf.c parsing.c display.c utils.c
OBJ_DIR		= objs/
OBJ			= ${addprefix ${OBJ_DIR}, ${SRC:.c=.o}}
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -g

${OBJ_DIR}%.o:	src/%.c
			${CC} ${CFLAGS} -I ${INC} -c $< -o $@

${NAME}:	${OBJ_DIR} ${OBJ} ${LIBFT} ${MLX}
			${CC} ${CFLAGS} -o $@ ${OBJ} ${LIBFT} ${MLX} -lXext -lX11 -lm

${OBJ_DIR}:
			mkdir -p ${OBJ_DIR}

${LIBFT}:	
			${MAKE} bonus -C libft

${MLX}:
			${MAKE} -C minilibx

all:		${NAME}

bonus:		${OBJ_DIR} ${OBJ_BONUS} ${LIBFT} ${MLX} ${INC}
			${CC} ${CFLAGS} -o ${NAME} ${OBJ_BONUS} ${LIBFT} ${MLX} -lXext -lX11 -lm

clean:
			rm -rf ${OBJ_DIR}
			${MAKE} clean -C libft
			${MAKE} clean -C minilibx

fclean:		clean
			rm -rf ${NAME}
			${MAKE} fclean -C libft

re: 		fclean all

.PHONY: 	all clean fclean re