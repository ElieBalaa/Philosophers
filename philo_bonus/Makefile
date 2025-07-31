# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: the-flash <the-flash@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/04 00:00:00 by the-flash         #+#    #+#              #
#    Updated: 2025/01/04 00:00:00 by the-flash        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo_bonus

SRCDIR		= src
INCDIR		= includes
OBJDIR		= obj

SRCS		= $(SRCDIR)/main_bonus.c \
			  $(SRCDIR)/init_bonus.c \
			  $(SRCDIR)/cleanup_bonus.c \
			  $(SRCDIR)/utils_bonus.c \
			  $(SRCDIR)/philosopher_bonus.c \
			  $(SRCDIR)/monitor_bonus.c

OBJS		= $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -pthread -I$(INCDIR)
RM			= rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re 