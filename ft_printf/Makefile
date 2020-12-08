NAME		= libftprintf.a

SRCS		= ft_printf.c ft_display.c ft_display2.c utils.c utils2.c flagsft.c

SRCSBON		= 

OBJS		= ${SRCS:.c=.o}

OBJSBON		= ${SRCSBON:.c=.o}

CFLAGS		= -Wall -Wextra -Werror

all:		${NAME}

$(NAME):	${OBJS}
			ar rcs ${NAME} ${OBJS}

.c.o:		
			gcc ${CFLAGS} -c $< -o ${<:.c=.o}

bonus:		${OBJS} ${OBJSBON}
			rm -f ${NAME}
			ar rcs ${NAME} ${OBJS} ${OBJSBON}

clean:
			rm -f ${OBJS} ${OBJSBON}

fclean:		clean
			rm -f ${NAME}

re:			fclean all

.PHONY:		all clean fclean re bonus
