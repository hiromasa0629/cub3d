# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/19 15:59:25 by hyap              #+#    #+#              #
#    Updated: 2022/10/24 17:22:29 by hyap             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCSDIR = srcs
SRCS = ${wildcard $(SRCSDIR)/*.c} \
		${wildcard $(SRCSDIR)/gnl/*.c} \
		${wildcard $(SRCSDIR)/utils/*.c} \
		${wildcard $(SRCSDIR)/parsing/*.c} \
		${wildcard $(SRCSDIR)/minimap/*.c}
OBJSDIR = objs
OBJS = $(SRCS:%.c=$(OBJSDIR)/%.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBMLX = libmlx.dylib
FSANITIZE = -fsanitize=address 
NAME = cub3d
RM = rm -f

all: ${NAME}

$(OBJSDIR)/%.o: %.c 
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I includes -c $< -o $@

${NAME}: $(OBJS)
	${CC} ${LIBMLX} $(OBJS) -o ${NAME}

clean:
	${RM} -rv $(OBJSDIR)

fclean:
	${RM} ${NAME}

re: clean all

.PHONY: all clean re