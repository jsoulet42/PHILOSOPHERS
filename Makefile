# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/08 15:36:17 by jsoulet           #+#    #+#              #
#    Updated: 2023/08/09 10:33:11 by jsoulet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= philo
SRC= philosopher.c philo_status.c philosopher_02.c utils.c
SRCPATH= ./cfiles/
OBJ= $(SRC:.c=.o)
OBJS= $(addprefix $(OBJPATH), $(OBJ))
SRCS= $(addprefix $(SRCPATH), $(SRC))
OBJPATH= ./ofiles/

CC= gcc -Wall -Wextra -Werror -pthread -g
all: $(NAME)

$(OBJPATH)%.o: $(SRCPATH)%.c
	mkdir -p ofiles
	$(CC) -I./hfiles -o $@ -c $<

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) -I./hfiles

clean:
	rm -f $(OBJS)
	rm -rf ofiles

fclean: clean
	rm -f $(NAME)

re: fclean all
