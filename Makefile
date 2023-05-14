# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kadigh <kadigh@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/17 01:40:26 by aaoutem-          #+#    #+#              #
#    Updated: 2023/05/14 23:24:48 by kadigh           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = gcc 
RM = rm 
FLAGS = -Wall -Wextra  -pthread -g  -fsanitize=address
SRC = main.c \
	src/init.c \
	src/util_fcts/error.c \
	src/util_fcts/ft_atoi.c \
	src/util_fcts/ft_calloc.c \
	src/util_fcts/ft_gettime.c \
	src/util_fcts/ft_strlen.c

OBJ_F = ${SRC:.c=.o}

all : ${NAME}

${NAME} : ${OBJ_F}
	@${CC} ${FLAGS} ${OBJ_F} -o philo
	@${RM} ${OBJ_F}

%.o : %.c 
	@${CC} ${FLAGS} $< -c -o $@ 

clean :
	@${RM} ${OBJ_F}

fclean : clean
	@${RM} ${NAME} 

re : fclean all
