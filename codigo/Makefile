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
NAME_BONUS	:= miniRT_bonus

CC 			:= cc
CFLAGS		:= -Wall -Wextra -Werror -g3 #-fsanitize=address

MLX42_DIR	:=	libs/MLX42
MLX42 		:= 	$(MLX42_DIR)/build/libmlx42.a
MLX42_INC 	:= 	$(MLX42_DIR)/include

LIBFT_DIR	:= 	libs/libft
LIBFTA		:= 	$(LIBFT_DIR)/libft.a

INCLUDE		:= include/
INCLUDE_BONUS	:= include_bonus/

SRC_DIR		:= 	src/

SRCS 		:= 	$(SRC_DIR)main.c \
				$(SRC_DIR)mrt_read_file.c \
				$(SRC_DIR)mrt_parce_data.c \
				$(SRC_DIR)mrt_check_ambient.c \
				$(SRC_DIR)mrt_check_light.c \
				$(SRC_DIR)mrt_check_camera.c \
				$(SRC_DIR)mrt_check_sphere.c \
				$(SRC_DIR)mrt_check_plane.c \
				$(SRC_DIR)mrt_check_cylinder.c \
				$(SRC_DIR)mrt_check_rgb.c \
				$(SRC_DIR)mrt_parse_float.c \
				$(SRC_DIR)mrt_init_scene.c \
				$(SRC_DIR)mrt_window_setup.c \
				$(SRC_DIR)mrt_setup_element.c \
				$(SRC_DIR)mrt_setup_objects.c\
				$(SRC_DIR)mrt_camera_view.c  \
				$(SRC_DIR)mrt_render.c \
				$(SRC_DIR)mrt_ray_color.c \
				$(SRC_DIR)mrt_hit_scene_render.c \
				$(SRC_DIR)mrt_hit_cylinder_body.c \
				$(SRC_DIR)mrt_hit_cylinder_caps.c \
				$(SRC_DIR)mrt_light_render.c \
				$(SRC_DIR)mrt_intersect_scene_light.c \
				$(SRC_DIR)mrt_extrac_data_elements.c \
				$(SRC_DIR)ft_vec_utils_00.c \
				$(SRC_DIR)ft_vec_utils_01.c \
				$(SRC_DIR)ft_vec_utils_02.c \
				$(SRC_DIR)ft_free_memory.c

SRC_DIR_BONUS := src_bonus/

SRCS_BONUS	:= 	$(SRC_DIR_BONUS)main_bonus.c \
				$(SRC_DIR_BONUS)mrt_read_file_bonus.c \
				$(SRC_DIR_BONUS)mrt_parce_data_bonus.c \
				$(SRC_DIR_BONUS)mrt_check_ambient_bonus.c \
				$(SRC_DIR_BONUS)mrt_check_light_bonus.c \
				$(SRC_DIR_BONUS)mrt_check_camera_bonus.c \
				$(SRC_DIR_BONUS)mrt_check_sphere_bonus.c \
				$(SRC_DIR_BONUS)mrt_check_plane_bonus.c \
				$(SRC_DIR_BONUS)mrt_check_cylinder_bonus.c \
				$(SRC_DIR_BONUS)mrt_check_rgb_bonus.c \
				$(SRC_DIR_BONUS)mrt_parse_float_bonus.c \
				$(SRC_DIR_BONUS)mrt_init_scene_bonus.c \
				$(SRC_DIR_BONUS)mrt_window_setup_bonus.c \
				$(SRC_DIR_BONUS)mrt_setup_element_bonus.c \
				$(SRC_DIR_BONUS)mrt_setup_objects_bonus.c\
				$(SRC_DIR_BONUS)mrt_camera_view_bonus.c \
				$(SRC_DIR_BONUS)mrt_render_bonus.c \
				$(SRC_DIR_BONUS)mrt_ray_color_bonus.c \
				$(SRC_DIR_BONUS)mrt_hit_scene_render_bonus.c \
				$(SRC_DIR_BONUS)mrt_hit_cylinder_body_bonus.c \
				$(SRC_DIR_BONUS)mrt_hit_cylinder_caps_bonus.c \
				$(SRC_DIR_BONUS)mrt_light_render_bonus.c \
				$(SRC_DIR_BONUS)mrt_intersect_scene_light_bonus.c \
				$(SRC_DIR_BONUS)mrt_extrac_data_elements_bonus.c \
				$(SRC_DIR_BONUS)ft_vec_utils_00_bonus.c \
				$(SRC_DIR_BONUS)ft_vec_utils_01_bonus.c \
				$(SRC_DIR_BONUS)ft_vec_utils_02_bonus.c \
				$(SRC_DIR_BONUS)ft_free_memory_bonus.c

OBJ_DIR      := obj/
OBJ_DIR_BONUS := obj_bonus/

OBJS        := $(addprefix $(OBJ_DIR), $(SRCS:$(SRC_DIR)%.c=%.o))
OBJS_BONUS := $(addprefix $(OBJ_DIR_BONUS), $(notdir $(SRCS_BONUS:.c=.o)))

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
bonus:	$(NAME_BONUS)

$(NAME): $(LIBFTA) $(MLX42) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFTA) $(MLX42) $(MLX_FLAGS) -I$(MLX42_INC) -o $(NAME)
	@echo "$(CYAN)✅ Compilado miniRT\n$(CLEAR_COLOR)"

$(NAME_BONUS): $(LIBFTA) $(MLX42) $(OBJS_BONUS)
	@$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBFTA) $(MLX42) $(MLX_FLAGS) -I$(MLX42_INC) -o $(NAME_BONUS)
	@echo "$(CYAN)✅ Compilado miniRT Bonus\n$(CLEAR_COLOR)"
						 
$(LIBFTA):
	@make -C $(LIBFT_DIR)
	@echo "$(GREEN)✅ Compilado LIBFT\n$(CLEAR_COLOR)"

$(MLX42):
	@cmake -B $(MLX42_DIR)/build $(MLX42_DIR)
	@cmake --build $(MLX42_DIR)/build
	@echo "$(GREEN)✅ Compilado MLX42\n$(CLEAR_COLOR)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INCLUDE)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(MATERIAL_FLAGS) -Iinclude -I$(MLX42_INC) -c $< -o $@

$(OBJ_DIR_BONUS)%.o:
	@mkdir -p $(OBJ_DIR_BONUS)
	@$(CC) $(CFLAGS) $(MATERIAL_FLAGS) -I$(INCLUDE_BONUS) -I$(MLX42_INC) -c src_bonus/$*.c -o $@


clean:
	@$(RM) $(OBJS) $(OBJS_BONUS)
	@rm -rf $(OBJ_DIR) $(OBJ_DIR_BONUS)
	@make clean -C $(LIBFT_DIR)
	@echo "$(RED)⛔ Limpieza de archivos objeto.$(CLEAR_COLOR)"

fclean: clean
	@$(RM) $(NAME) $(NAME_BONUS)
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
	@norminette $(SRCS) $(INCLUDE) $(SRCS_BONUS) $(INCLUDE_BONUS)

norminette_all:
	@norminette $(SRCS) $(INCLUDE) $(SRCS_BONUS) $(INCLUDE_BONUS) $(LIBFT_DIR)/src/ft/*.c $(LIBFT_DIR)/*.h

# Material targets
matte: fclean
	@$(MAKE) all MATERIAL_FLAGS="-DMATERIAL_TYPE=1"
	@echo "$(CYAN)✨ Compilado con material MATE$(CLEAR_COLOR)"

plastic: fclean
	@$(MAKE) all MATERIAL_FLAGS="-DMATERIAL_TYPE=2"
	@echo "$(CYAN)✨ Compilado con material PLÁSTICO$(CLEAR_COLOR)"

wood: fclean
	@$(MAKE) all MATERIAL_FLAGS="-DMATERIAL_TYPE=3"
	@echo "$(CYAN)✨ Compilado con material MADERA$(CLEAR_COLOR)"

shiny: fclean
	@$(MAKE) all MATERIAL_FLAGS="-DMATERIAL_TYPE=4"
	@echo "$(CYAN)✨ Compilado con material BRILLANTE$(CLEAR_COLOR)"

anti: fclean
	@$(MAKE) all MATERIAL_FLAGS="-DANTIALIASING=1"
	@echo "$(CYAN)🎯 Compilado con ANTIALIASING 4x$(CLEAR_COLOR)"

.PHONY: all bonus clean fclean re norminette norminette_all valgrind matte plastic wood shiny anti 