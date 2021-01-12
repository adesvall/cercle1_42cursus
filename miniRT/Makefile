NAME		= miniRT

SGNL		= get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
SLIB		= libft/libftutils.c libft/libftutils2.c libft/libftutils3.c

SRCS		= main.c \
			collisions/vectop.c dispixel.c collisions/collision.c collisions/collisionany.c collisions/collisionutils.c \
			parse/init_scene.c parse/parseutils.c events.c parse/add_elem.c save_bmp.c ${SLIB} ${SGNL}

OBJS		= ${SRCS:.c=.o}

CFLAGS		= -Wall -Wextra -I/includes -I/usr/include -Imlx_linux -lpthread -O3 -g

all:		${NAME}

$(NAME):	${OBJS}
			gcc -o ${NAME} ${OBJS} ${CFLAGS} -L.. -lmlx -L/usr/lib -lXext -lX11 -lm -lpthread -lbsd -g

.c.o:		
			gcc ${CFLAGS} -c $< -o ${<:.c=.o}

clean:
			rm -f ${OBJS} ${OBJSBON}

fclean:		clean
			rm -f ${NAME}

re:			fclean all

.PHONY:		all clean fclean re bonus
