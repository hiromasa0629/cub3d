# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/19 15:59:25 by hyap              #+#    #+#              #
#    Updated: 2022/11/14 14:10:01 by hyap             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCSDIR = srcs
SRCS = ${wildcard $(SRCSDIR)/*.c} \
		${wildcard $(SRCSDIR)/gnl/*.c} \
		${wildcard $(SRCSDIR)/utils/*.c} \
		${wildcard $(SRCSDIR)/parsing/*.c} \
		${wildcard $(SRCSDIR)/render/*.c}
OBJSDIR = objs
OBJS = $(SRCS:%.c=$(OBJSDIR)/%.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBMLX = libmlx.dylib
FSANITIZE = -fsanitize=address -g
NAME = cub3D
RM = rm -f
MINIMAP = srcs/minimap/minimaptmp.c ${wildcard $(SRCSDIR)/utils/*.c} ${wildcard $(SRCSDIR)/gnl/*.c}

all: ${NAME}

$(OBJSDIR)/%.o: %.c 
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I includes -c $< -o $@

${NAME}: $(OBJS)
	${CC} ${LIBMLX} $(OBJS) -o ${NAME}
	
minimap:
	$(CC) ${FSANITIZE} $(CFLAGS) -I includes $(LIBMLX) $(MINIMAP) -o minimap
	
clean:
	${RM} -rv $(OBJSDIR)

fclean: clean
	${RM} ${NAME}

re: clean all

.PHONY: all clean fclean re minimap