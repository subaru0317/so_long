NAME	=	so_long
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror
SRCS	=	get_next_line_utils.c \
			get_next_line.c \
			validate_map.c
OBJS	=	${SRCS:%.c=%.o}

%.o: %.c
	${CC} ${CFLAGS} -c $^ -o $@

${NAME}: ${OBJS}
	${MAKE} -C ./libft
	${CC} ${CFLAGS} ${OBJS} libft/libft.a -o $@

all: ${NAME}

clean:
	${MAKE} -C ./libft clean
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re:	fclean all

.PHONY:	all clean fclean re
