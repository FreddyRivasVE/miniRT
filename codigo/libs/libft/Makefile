# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: brivera@student.42madrid.com <brivera>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/25 10:33:30 by brivera           #+#    #+#              #
#    Updated: 2025/04/05 18:48:00 by brivera@stu      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -I./

SRC_DIR = src/ft
SRC = $(SRC_DIR)/ft_isalpha.c $(SRC_DIR)/ft_isdigit.c $(SRC_DIR)/ft_isalnum.c \
      $(SRC_DIR)/ft_isascii.c $(SRC_DIR)/ft_isprint.c $(SRC_DIR)/ft_strlen.c \
      $(SRC_DIR)/ft_memset.c $(SRC_DIR)/ft_bzero.c $(SRC_DIR)/ft_memcpy.c \
      $(SRC_DIR)/ft_memmove.c $(SRC_DIR)/ft_strlcpy.c $(SRC_DIR)/ft_strlcat.c \
      $(SRC_DIR)/ft_toupper.c $(SRC_DIR)/ft_tolower.c $(SRC_DIR)/ft_strchr.c \
      $(SRC_DIR)/ft_strrchr.c $(SRC_DIR)/ft_strncmp.c $(SRC_DIR)/ft_memchr.c \
      $(SRC_DIR)/ft_memcmp.c $(SRC_DIR)/ft_strnstr.c $(SRC_DIR)/ft_atoi.c \
      $(SRC_DIR)/ft_calloc.c $(SRC_DIR)/ft_strdup.c $(SRC_DIR)/ft_substr.c \
      $(SRC_DIR)/ft_strjoin.c $(SRC_DIR)/ft_strtrim.c $(SRC_DIR)/ft_split.c \
      $(SRC_DIR)/ft_itoa.c $(SRC_DIR)/ft_strmapi.c $(SRC_DIR)/ft_striteri.c \
      $(SRC_DIR)/ft_putchar_fd.c $(SRC_DIR)/ft_putstr_fd.c $(SRC_DIR)/ft_putendl_fd.c \
	  $(SRC_DIR)/ft_putnbr_fd.c \
	  $(SRC_DIR)/get_next_line.c \
	  $(SRC_DIR)/free_array.c \
	  $(SRC_DIR)/ft_lstnew_bonus.c $(SRC_DIR)/ft_lstadd_front_bonus.c \
	  $(SRC_DIR)/ft_lstsize_bonus.c $(SRC_DIR)/ft_lstlast_bonus.c \
	  $(SRC_DIR)/ft_lstadd_back_bonus.c $(SRC_DIR)/ft_lstdelone_bonus.c \
	  $(SRC_DIR)/ft_lstclear_bonus.c $(SRC_DIR)/ft_lstiter_bonus.c \
	  $(SRC_DIR)/ft_lstmap_bonus.c

OBJ_DIR = src/obj
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

INCLUDE = libft.h

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)
#@echo "$(GREEN)✅ Compilado LIBFT\n$(CLEAR_COLOR)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDE)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
#	@echo -n "\rCompilando: $<"

clean:
	@rm -rf $(OBJ_DIR)
#@echo "Archivos objeto eliminados."

fclean: clean
	@rm -f $(NAME)
#@echo "Librería eliminada."

re: fclean all

.PHONY: all clean fclean re
