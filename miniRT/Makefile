NAME		= miniRT

SRCS		= main.c collisions/vectop.c dispixel.c collisions/collision.c init_scene.c

OBJS		= ${SRCS:.c=.o}

CFLAGS		= -I/usr/include -Imlx_linux -O3 -g

all:		${NAME}

$(NAME):	${OBJS}
			gcc -o ${NAME} ${OBJS} -L.. -lmlx -L/usr/lib -lXext -lX11 -lm -lbsd -g

.c.o:		
			gcc ${CFLAGS} -c $< -o ${<:.c=.o}

clean:
			rm -f ${OBJS} ${OBJSBON}

fclean:		clean
			rm -f ${NAME}

re:			fclean all

.PHONY:		all clean fclean re bonus
