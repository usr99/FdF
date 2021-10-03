NAME			= fdf
NAME_BONUS		= fdf_bonus
INC				= ./inc
LIBFT			= libft/libft.a
MLX				= minilibx/libmlx.a
SRC				= fdf.c parsing.c display.c keyboard_event.c utils.c display_utils.c bresenham.c parsing_utils.c
SRC_BONUS		= fdf.c parsing.c display.c keyboard_event.c mouse_event.c transformation.c utils.c display_utils.c color_gradient.c bresenham.c parsing_utils.c
OBJ_DIR			= objs/
OBJ_DIR_BONUS	= objs_bonus/
OBJ				= ${addprefix ${OBJ_DIR}, ${SRC:.c=.o}}
OBJ_BONUS		= ${addprefix ${OBJ_DIR_BONUS}, ${SRC_BONUS:.c=_bonus.o}}
CC				= gcc
CFLAGS			= -Wall -Wextra -Werror

${OBJ_DIR}%.o:	src/%.c
			@${CC} ${CFLAGS} -c $< -o $@
			@echo "$<"

${OBJ_DIR_BONUS}%.o:	src_bonus/%.c
			@${CC} ${CFLAGS} -c $< -o $@
			@echo "$<"

${NAME}:	${OBJ_DIR} ${OBJ} ${LIBFT} ${MLX} ${INC}
			${CC} ${CFLAGS} -o $@ ${OBJ} ${LIBFT} ${MLX} -I ${INC} -lXext -lX11 -lm

${OBJ_DIR}:
			@mkdir -p ${OBJ_DIR}
			@echo "Creating objs/ directory..."

${OBJ_DIR_BONUS}:
			@mkdir -p ${OBJ_DIR_BONUS}
			@echo "Creating objs/ directory..."

${LIBFT}:	
			@echo "Compiling libft..."
			@${MAKE} bonus -C libft

${MLX}:
			@echo "Compiling minilibx..."
			@${MAKE} -C minilibx

${NAME_BONUS}:		${OBJ_DIR_BONUS} ${OBJ_BONUS} ${LIBFT} ${MLX} ${INC}
			${CC} ${CFLAGS} -o ${NAME_BONUS} ${OBJ_BONUS} ${LIBFT} ${MLX} -I ${INC} -lXext -lX11 -lm

all:		${NAME} ${NAME_BONUS}

bonus:		${NAME_BONUS}

clean:
			rm -rf ${OBJ_DIR}
			rm -rf ${OBJ_DIR_BONUS}
			@${MAKE} clean -C libft
			@${MAKE} clean -C minilibx

fclean:		clean
			rm -rf ${NAME}
			rm -rf ${NAME_BONUS}
			@${MAKE} fclean -C libft

re: 		fclean all

.PHONY: 	all clean fclean re