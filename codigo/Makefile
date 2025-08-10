# ************************************************************************** #
#                                                                            #
#                                                        :::      ::::::::   #
#   Makefile                                           :+:      :+:    :+:   #
#                                                    +:+ +:+         +:+     #
#   By: brivera <brivera@student.42madrid.com>     #+#  +:+       +#+        #
#                                                +#+#+#+#+#+   +#+           #
#   Created: 2025-07-17 16:24:12 by brivera           #+#    #+#             #
#   Updated: 2025-07-17 16:24:12 by brivera          ###   ########.fr       #
#                                                                            #
# ************************************************************************** #

NAME		:= miniRT

CC 			:= cc
CFLAGS		:= -O3 -Wall -Wextra -Werror -g3 #-fsanitize=address

MLX42_DIR	:=	libs/MLX42
MLX42 		:= 	$(MLX42_DIR)/build/libmlx42.a
MLX42_INC 	:= 	$(MLX42_DIR)/include

LIBFT_DIR	:= 	libs/libft
LIBFTA		:= 	$(LIBFT_DIR)/libft.a

INCLUDE		:= include/

SRC_DIR		:= 	src/
SRCS 		:= 	$(SRC_DIR)main.c $(SRC_DIR)mrt_parce_data.c $(SRC_DIR)window_setup.c \
				$(SRC_DIR)mrt_create_render.c $(SRC_DIR)mrt_create_render_01.c\
				$(SRC_DIR)mrt_compute_camera_view.c $(SRC_DIR)mrt_check_ambient.c \
				$(SRC_DIR)mrt_check_rgb.c $(SRC_DIR)mrt_check_camera.c \
				$(SRC_DIR)mrt_parse_float.c $(SRC_DIR)mrt_check_light.c \
				$(SRC_DIR)mrt_setup_element.c $(SRC_DIR)vec_utils_00.c \
				$(SRC_DIR)vec_utils_01.c $(SRC_DIR)mrt_free_memory.c \
				$(SRC_DIR)mrt_check_sphere.c  $(SRC_DIR)mrt_read_file.c \
				$(SRC_DIR)mrt_init_scene_01.c $(SRC_DIR)mrt_check_plane.c \
				$(SRC_DIR)mrt_check_cylinder.c $(SRC_DIR)ft_atof.c \
				$(SRC_DIR)mrt_extrac_data_elements.c

OBJ_DIR 	:=	obj/
OBJS 		:=	$(addprefix $(OBJ_DIR), $(SRCS:$(SRC_DIR)%.c=%.o))

RED			:=	\033[91;1m
GREEN		:=	\033[92;1m
CLEAR_COLOR	:=	\033[0m
CYAN 		:=	\033[96;1m

OS = $(shell uname)
ifeq ($(OS), Linux)
	MLX_FLAGS := -lglfw -lm -ldl -lX11 -lpthread -lXrandr -lXi
else
	MLX_FLAGS := -framework Cocoa -framework OpenGL -framework IOKit -lglfw
endif

all:	$(NAME)

$(NAME): $(LIBFTA) $(MLX42) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFTA) $(MLX42) $(MLX_FLAGS) -I$(MLX42_INC) -o $(NAME)
	@echo "$(CYAN)✅ Compilado miniRT\n$(CLEAR_COLOR)"
						 
$(LIBFTA):
	@make -C $(LIBFT_DIR)
	@echo "$(GREEN)✅ Compilado LIBFT\n$(CLEAR_COLOR)"

$(MLX42):
	@cmake -B $(MLX42_DIR)/build $(MLX42_DIR)
	@cmake --build $(MLX42_DIR)/build
	@echo "$(GREEN)✅ Compilado MLX42\n$(CLEAR_COLOR)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INCLUDE)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -Iinclude -I$(MLX42_INC) -c $< -o $@

clean:
	@$(RM) $(OBJS)
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIBFT_DIR)
	@echo "$(RED)⛔ Limpieza de archivos objeto.$(CLEAR_COLOR)"

fclean: clean
	@$(RM) $(NAME)
	@rm -rf $(MLX42_DIR)/build
	@make fclean -C $(LIBFT_DIR)
	@echo "$(RED)⛔ Limpieza total (ejecutables y librerías).$(CLEAR_COLOR)"

re: fclean all

valgrind: re
	valgrind -s \
		--tool=memcheck \
		--leak-check=full \
		--show-leak-kinds=all \
		--show-reachable=yes \
		--track-origins=yes \
		--suppressions=valgrind/valgrind.sup \
		--log-file=valgrind/informe \
		./$(NAME) ejemplo.rt

norminette:
	@norminette $(SRCS) $(INCLUDE)

.PHONY: all clean fclean re norminette valgrind