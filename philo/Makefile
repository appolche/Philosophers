NAME		=	philo

HEADER		=	philo.h

SRCS		= 	philo.c\
				simulation_start.c\
				action.c\
				error_parse.c\
				utils.c\

OBJS		=	$(SRCS:.c=.o)

PHILO_FLAGS	=	-pthread
FLAGS		=	-Wall -Wextra -Werror -g 
CC			=	gcc
GCC			=	$(CC) $(FLAGS)


all:			$(NAME)

%.o:			%.c $(HEADER)
				$(GCC) -c -o $@ $<
 
$(NAME):		$(OBJS)
				$(GCC) $(PHILO_FLAGS) $(OBJS) -o $(NAME)

clean:				
				rm -f $(OBJS)
			
fclean:			clean
				rm -f $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re