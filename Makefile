# # **************************************************************************** #
# #                                                                              #
# #                                                         :::      ::::::::    #
# #    Makefile                                           :+:      :+:    :+:    #
# #                                                     +:+ +:+         +:+      #
# #    By: eraad <eraad@student.42.fr>                +#+  +:+       +#+         #
# #                                                 +#+#+#+#+#+   +#+            #
# #    Created: 2025/12/16 12:00:00 by eraad             #+#    #+#              #
# #    Updated: 2025/12/16 21:15:46 by eraad            ###   ########.fr        #
# #                                                                              #
# # **************************************************************************** #

#* ==============================================================================
#*                                  BINARY
#* ==============================================================================
NAME            := miniRT
NAME_BONUS      := miniRT_bonus

#* ==============================================================================
#*                                  LAYOUT
#* ==============================================================================
SRC_DIR			:= sources
SRC_DIR_BONUS	:= sources_bonus
OBJ_DIR			:= objects
OBJ_DIR_BONUS	:= objects_bonus

LIBFT_DIR		:= libft
LIBFT_A			:= $(LIBFT_DIR)/libft.a

MLX_DIR			:= minilibx-linux
MLX_A			:= $(MLX_DIR)/libmlx.a

#* ==============================================================================
#*                                  TOOLCHAIN
#* ==============================================================================
CC				:= cc
CFLAGS			:= -Wall -Wextra -Werror -O3 -ffast-math -g3
CPPFLAGS		:= -Iincludes -Ilibft -Iminilibx-linux
CPPFLAGS_BONUS	:= -Iincludes_bonus -Ilibft -Iminilibx-linux

LDFLAGS			:= -L$(LIBFT_DIR) -L$(MLX_DIR)
LDLIBS			:= -lft -lmlx -lXext -lX11 -lm -lz

ARGS			:= assets/scenes/valgrind_test.rt

#* ==============================================================================
#*                                  COLORS/SYMBOLS/STYLES
#* ==============================================================================
RESET			:= \033[0m
BOLD			:= \033[1m
DIM				:= \033[2m
ITALIC			:= \033[3m
UNDERLINE		:= \033[4m

BLACK			:= \033[30m
RED				:= \033[31m
GREEN			:= \033[32m
YELLOW			:= \033[33m
BLUE			:= \033[34m
MAGENTA			:= \033[35m
CYAN			:= \033[36m
WHITE			:= \033[37m

BRIGHT_GREEN	:= \033[92m
BRIGHT_MAGENTA	:= \033[95m
BRIGHT_CYAN		:= \033[96m

OK				:= ✓
KO				:= ✗
INFO			:= ⓘ

#* ==============================================================================
#*                                  SOURCES
#* ==============================================================================

#* ---- Core ----
SRCS := \
    $(SRC_DIR)/core/main.c \
    $(SRC_DIR)/core/cleanup.c \

#* ---- Graphics ----
SRCS += \
    $(SRC_DIR)/graphics/init_graphics.c \
    $(SRC_DIR)/graphics/render_frame.c \
    $(SRC_DIR)/graphics/color_to_int.c \
    $(SRC_DIR)/graphics/image_pixel_put.c \

#* ---- Parsing ----
SRCS += \
    $(SRC_DIR)/parsing/parse_file.c \
    $(SRC_DIR)/parsing/utils.c \
    $(SRC_DIR)/parsing/parse_numbers.c \
    $(SRC_DIR)/parsing/parse_vec3.c \
    $(SRC_DIR)/parsing/parse_color.c \
    $(SRC_DIR)/parsing/parse_ambient.c \
    $(SRC_DIR)/parsing/parse_camera.c \
    $(SRC_DIR)/parsing/parse_light.c \
    $(SRC_DIR)/parsing/parse_sphere.c \
    $(SRC_DIR)/parsing/parse_plane.c \
    $(SRC_DIR)/parsing/parse_cylinder.c \
    $(SRC_DIR)/parsing/add_object_to_scene.c \
    $(SRC_DIR)/parsing/get_count.c \

#* ---- Scene ----
SRCS += \
    $(SRC_DIR)/scene/load_scene.c \
    $(SRC_DIR)/scene/camera.c \
    $(SRC_DIR)/scene/modifiers/transformation_dispatch.c \
	$(SRC_DIR)/scene/modifiers/update.c \
	$(SRC_DIR)/scene/modifiers/utils.c \
    $(SRC_DIR)/scene/modifiers/translate/translate_camera.c \
    $(SRC_DIR)/scene/modifiers/translate/translate_light.c \
    $(SRC_DIR)/scene/modifiers/translate/translate_sphere.c \
    $(SRC_DIR)/scene/modifiers/translate/translate_plane.c \
    $(SRC_DIR)/scene/modifiers/translate/translate_cylinder.c \
    $(SRC_DIR)/scene/modifiers/rotate/rotate_camera.c \
    $(SRC_DIR)/scene/modifiers/rotate/rotate_plane.c \
    $(SRC_DIR)/scene/modifiers/rotate/rotate_cylinder.c \
    $(SRC_DIR)/scene/modifiers/resize/resize_sphere.c \
    $(SRC_DIR)/scene/modifiers/resize/resize_cylinder.c \

#* ---- Raytracer ----
SRCS += \
    $(SRC_DIR)/raytracer/intersection/hit_objects.c \
    $(SRC_DIR)/raytracer/intersection/hit_sphere.c \
    $(SRC_DIR)/raytracer/intersection/hit_plane.c \
    $(SRC_DIR)/raytracer/intersection/hit_cylinder.c \
    $(SRC_DIR)/raytracer/lighting/phong_model.c \
    $(SRC_DIR)/raytracer/lighting/reflect.c \
	$(SRC_DIR)/raytracer/utils.c \
	$(SRC_DIR)/raytracer/ray.c \

#* ---- Inputs ----
SRCS += \
    $(SRC_DIR)/inputs/input_manager.c \
    $(SRC_DIR)/inputs/key_hooks.c \
    $(SRC_DIR)/inputs/mouse_hooks.c \
	$(SRC_DIR)/inputs/camera_input.c \
    $(SRC_DIR)/inputs/utils.c \

#* ---- Maths ----
SRCS += \
    $(SRC_DIR)/maths/solve_quadratic.c \
    $(SRC_DIR)/maths/vector/add.c \
    $(SRC_DIR)/maths/vector/substract.c \
    $(SRC_DIR)/maths/vector/product.c \
    $(SRC_DIR)/maths/vector/scalar_product.c \
    $(SRC_DIR)/maths/vector/cross_product.c \
    $(SRC_DIR)/maths/vector/len.c \
    $(SRC_DIR)/maths/vector/normalize.c \
    $(SRC_DIR)/maths/matrix/identity.c \
    $(SRC_DIR)/maths/matrix/translation.c \
    $(SRC_DIR)/maths/matrix/mult.c \
	$(SRC_DIR)/maths/matrix/transpose.c \
	$(SRC_DIR)/maths/matrix/inverse.c \
	$(SRC_DIR)/maths/matrix/rotate_vector.c \
	$(SRC_DIR)/maths/matrix/scale.c \
	$(SRC_DIR)/maths/matrix/rotation_euler.c \
	$(SRC_DIR)/maths/matrix/rotation_axis.c \
	$(SRC_DIR)/maths/matrix/rotation_align.c \

#* ---- Errors & Utils ----
SRCS += \
    $(SRC_DIR)/error/print_error.c \
    $(SRC_DIR)/error/print_error_exit.c \
    $(SRC_DIR)/error/print_error_free_exit.c \
	$(SRC_DIR)/error/print_error_loc.c \
    $(SRC_DIR)/utils/print.c \
    $(SRC_DIR)/utils/ft_strspn.c \
    $(SRC_DIR)/utils/log.c \

OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

SRC_COUNT := $(words $(SRCS))

#* ==============================================================================
#*                                  SOURCES_BONUS
#* ==============================================================================

#* ---- Core ----
SRCS_BONUS := \
    $(SRC_DIR_BONUS)/core/main_bonus.c \
    $(SRC_DIR_BONUS)/core/cleanup_bonus.c \
	$(SRC_DIR_BONUS)/core/save_bonus.c \

#* ---- Graphics ----
SRCS_BONUS += \
    $(SRC_DIR_BONUS)/graphics/init_graphics_bonus.c \
    $(SRC_DIR_BONUS)/graphics/render_frame_bonus.c \
    $(SRC_DIR_BONUS)/graphics/multi_threading_bonus.c \
    $(SRC_DIR_BONUS)/graphics/color_to_int_bonus.c \
    $(SRC_DIR_BONUS)/graphics/image_pixel_put_bonus.c \

#* ---- Parsing ----
SRCS_BONUS += \
    $(SRC_DIR_BONUS)/parsing/parse_file_bonus.c \
    $(SRC_DIR_BONUS)/parsing/utils/add_object_to_scene_bonus.c \
    $(SRC_DIR_BONUS)/parsing/utils/get_count_bonus.c \
    $(SRC_DIR_BONUS)/parsing/utils/parse_color_bonus.c \
    $(SRC_DIR_BONUS)/parsing/utils/parse_numbers_bonus.c \
    $(SRC_DIR_BONUS)/parsing/utils/parse_vec3_bonus.c \
    $(SRC_DIR_BONUS)/parsing/utils/utils_bonus.c \
#* ---- Objects / Entities ----
SRCS_BONUS += \
    $(SRC_DIR_BONUS)/parsing/scene/parse_ambient_bonus.c \
    $(SRC_DIR_BONUS)/parsing/scene/parse_camera_bonus.c \
    $(SRC_DIR_BONUS)/parsing/scene/parse_light_bonus.c \
    $(SRC_DIR_BONUS)/parsing/scene/parse_resolution_bonus.c \
    $(SRC_DIR_BONUS)/parsing/objects/parse_cylinder_bonus.c \
    $(SRC_DIR_BONUS)/parsing/objects/parse_plane_bonus.c \
    $(SRC_DIR_BONUS)/parsing/objects/parse_sphere_bonus.c \
	$(SRC_DIR_BONUS)/parsing/objects/parse_rectangle_bonus.c \
	${SRC_DIR_BONUS}/parsing/objects/parse_disk_bonus.c \
	${SRC_DIR_BONUS}/parsing/objects/parse_triangle_bonus.c \

#* ---- Scene ----
SRCS_BONUS += \
    $(SRC_DIR_BONUS)/scene/load_scene_bonus.c \
    $(SRC_DIR_BONUS)/scene/camera_bonus.c \
    $(SRC_DIR_BONUS)/scene/modifiers/transformation_dispatch_bonus.c \
    $(SRC_DIR_BONUS)/scene/modifiers/utils_bonus.c \
#* ---- Update ---
SRCS_BONUS += \
    $(SRC_DIR_BONUS)/scene/update/update_bonus.c \
	$(SRC_DIR_BONUS)/scene/update/update_rectangle_bonus.c \
	$(SRC_DIR_BONUS)/scene/update/update_sphere_bonus.c \
	$(SRC_DIR_BONUS)/scene/update/update_plane_bonus.c \
	$(SRC_DIR_BONUS)/scene/update/update_cylinder_bonus.c \
	$(SRC_DIR_BONUS)/scene/update/update_disk_bonus.c \
	$(SRC_DIR_BONUS)/scene/update/update_triangle_bonus.c \
	$(SRC_DIR_BONUS)/scene/update/update_camera_bonus.c \
#* ---- Translate ---
SRCS_BONUS += \
    $(SRC_DIR_BONUS)/scene/modifiers/translate/translate_camera_bonus.c \
    $(SRC_DIR_BONUS)/scene/modifiers/translate/translate_light_bonus.c \
    $(SRC_DIR_BONUS)/scene/modifiers/translate/translate_sphere_bonus.c \
    $(SRC_DIR_BONUS)/scene/modifiers/translate/translate_plane_bonus.c \
    $(SRC_DIR_BONUS)/scene/modifiers/translate/translate_cylinder_bonus.c \
	$(SRC_DIR_BONUS)/scene/modifiers/translate/translate_rectangle_bonus.c \
	$(SRC_DIR_BONUS)/scene/modifiers/translate/translate_disk_bonus.c \
	$(SRC_DIR_BONUS)/scene/modifiers/translate/translate_triangle_bonus.c \
#* ---- Rotate ---
SRCS_BONUS += \
    $(SRC_DIR_BONUS)/scene/modifiers/rotate/rotate_camera_bonus.c \
    $(SRC_DIR_BONUS)/scene/modifiers/rotate/rotate_plane_bonus.c \
    $(SRC_DIR_BONUS)/scene/modifiers/rotate/rotate_cylinder_bonus.c \
	$(SRC_DIR_BONUS)/scene/modifiers/rotate/rotate_rectangle_bonus.c \
	$(SRC_DIR_BONUS)/scene/modifiers/rotate/rotate_disk_bonus.c \
	$(SRC_DIR_BONUS)/scene/modifiers/rotate/rotate_triangle_bonus.c \
#* ---- Resize ---
SRCS_BONUS += \
    $(SRC_DIR_BONUS)/scene/modifiers/resize/resize_sphere_bonus.c \
    $(SRC_DIR_BONUS)/scene/modifiers/resize/resize_cylinder_bonus.c \
	$(SRC_DIR_BONUS)/scene/modifiers/resize/resize_rectangle_bonus.c \
	$(SRC_DIR_BONUS)/scene/modifiers/resize/resize_disk_bonus.c \
	$(SRC_DIR_BONUS)/scene/modifiers/resize/resize_triangle_bonus.c \
#* ---- Save ----
SRCS_BONUS += \
	$(SRC_DIR_BONUS)/scene/save/save_scene_bonus.c \
	$(SRC_DIR_BONUS)/scene/save/objects/save_plane_bonus.c \
	$(SRC_DIR_BONUS)/scene/save/objects/save_sphere_bonus.c \
	$(SRC_DIR_BONUS)/scene/save/objects/save_cylinder_bonus.c \
	$(SRC_DIR_BONUS)/scene/save/objects/save_rectangle_bonus.c \
	$(SRC_DIR_BONUS)/scene/save/objects/save_disk_bonus.c \
	$(SRC_DIR_BONUS)/scene/save/objects/save_triangle_bonus.c \
#* ---- Reset ----
SRCS_BONUS += \
	$(SRC_DIR_BONUS)/scene/reset/reset_scene_bonus.c \
	$(SRC_DIR_BONUS)/scene/reset/objects/reset_plane_bonus.c \
	$(SRC_DIR_BONUS)/scene/reset/objects/reset_sphere_bonus.c \
	$(SRC_DIR_BONUS)/scene/reset/objects/reset_cylinder_bonus.c \
	$(SRC_DIR_BONUS)/scene/reset/objects/reset_rectangle_bonus.c \
	$(SRC_DIR_BONUS)/scene/reset/objects/reset_disk_bonus.c \
	$(SRC_DIR_BONUS)/scene/reset/objects/reset_triangle_bonus.c \

#* ---- Raytracer ----
SRCS_BONUS += \
    $(SRC_DIR_BONUS)/raytracer/lighting/phong_model_bonus.c \
    $(SRC_DIR_BONUS)/raytracer/lighting/reflect_bonus.c \
    $(SRC_DIR_BONUS)/raytracer/ray_bonus.c \
    $(SRC_DIR_BONUS)/raytracer/utils_bonus.c \
#* ---- Intersection ---
SRCS_BONUS += \
    $(SRC_DIR_BONUS)/raytracer/intersection/hit_objects_bonus.c \
    $(SRC_DIR_BONUS)/raytracer/intersection/hit_sphere_bonus.c \
    $(SRC_DIR_BONUS)/raytracer/intersection/hit_plane_bonus.c \
    $(SRC_DIR_BONUS)/raytracer/intersection/hit_cylinder_bonus.c \
	$(SRC_DIR_BONUS)/raytracer/intersection/hit_rectangle_bonus.c \
	$(SRC_DIR_BONUS)/raytracer/intersection/hit_disk_bonus.c \
	$(SRC_DIR_BONUS)/raytracer/intersection/hit_triangle_bonus.c \

#* ---- Inputs ----
SRCS_BONUS += \
    $(SRC_DIR_BONUS)/inputs/input_manager_bonus.c \
    $(SRC_DIR_BONUS)/inputs/key_camera_bonus.c \
    $(SRC_DIR_BONUS)/inputs/key_edit_bonus.c \
    $(SRC_DIR_BONUS)/inputs/key_hooks_bonus.c \
    $(SRC_DIR_BONUS)/inputs/mouse_hooks_bonus.c \
    $(SRC_DIR_BONUS)/inputs/utils_bonus.c \
#* ---- Input Handlers ----
SRCS_BONUS += \
    $(SRC_DIR_BONUS)/inputs/handles/handle_c_key_bonus.c \
    $(SRC_DIR_BONUS)/inputs/handles/handle_click_bonus.c \
    $(SRC_DIR_BONUS)/inputs/handles/handle_l_key_bonus.c \
    $(SRC_DIR_BONUS)/inputs/handles/handle_scroll_bonus.c \
    $(SRC_DIR_BONUS)/inputs/handles/handle_space_key_bonus.c \
    $(SRC_DIR_BONUS)/inputs/handles/handle_tab_key_bonus.c \
	$(SRC_DIR_BONUS)/inputs/handles/handle_t_key_bonus.c \
	$(SRC_DIR_BONUS)/inputs/handles/handle_h_key_bonus.c \
	$(SRC_DIR_BONUS)/inputs/handles/handle_r_key_bonus.c \
	$(SRC_DIR_BONUS)/inputs/handles/handle_enter_key_bonus.c \

#* ---- Maths ----
SRCS_BONUS += \
    $(SRC_DIR_BONUS)/maths/solve_quadratic_bonus.c \
    $(SRC_DIR_BONUS)/maths/vector/add_bonus.c \
    $(SRC_DIR_BONUS)/maths/vector/substract_bonus.c \
    $(SRC_DIR_BONUS)/maths/vector/product_bonus.c \
    $(SRC_DIR_BONUS)/maths/vector/scalar_product_bonus.c \
    $(SRC_DIR_BONUS)/maths/vector/cross_product_bonus.c \
    $(SRC_DIR_BONUS)/maths/vector/len_bonus.c \
    $(SRC_DIR_BONUS)/maths/vector/normalize_bonus.c \
    $(SRC_DIR_BONUS)/maths/matrix/identity_bonus.c \
    $(SRC_DIR_BONUS)/maths/matrix/translation_bonus.c \
    $(SRC_DIR_BONUS)/maths/matrix/mult_bonus.c \
    $(SRC_DIR_BONUS)/maths/matrix/transpose_bonus.c \
    $(SRC_DIR_BONUS)/maths/matrix/inverse_bonus.c \
    $(SRC_DIR_BONUS)/maths/matrix/rotate_vector_bonus.c \
    $(SRC_DIR_BONUS)/maths/matrix/scale_bonus.c \
    $(SRC_DIR_BONUS)/maths/matrix/rotation_euler_bonus.c \
    $(SRC_DIR_BONUS)/maths/matrix/rotation_axis_bonus.c \
    $(SRC_DIR_BONUS)/maths/matrix/rotation_align_bonus.c \

#* ---- Errors & Utils ----
SRCS_BONUS += \
    $(SRC_DIR_BONUS)/error/print_error_bonus.c \
    $(SRC_DIR_BONUS)/error/print_error_exit_bonus.c \
    $(SRC_DIR_BONUS)/error/print_error_free_exit_bonus.c \
    $(SRC_DIR_BONUS)/error/print_error_loc_bonus.c \
    $(SRC_DIR_BONUS)/utils/print_bonus.c \
    $(SRC_DIR_BONUS)/utils/ft_strspn_bonus.c \
    $(SRC_DIR_BONUS)/utils/log_bonus.c \
    $(SRC_DIR_BONUS)/utils/time_bonus.c \
	$(SRC_DIR_BONUS)/utils/display_progress_bonus.c \

OBJS_BONUS := $(SRCS_BONUS:$(SRC_DIR_BONUS)/%.c=$(OBJ_DIR_BONUS)/%.o)

SRC_COUNT_BONUS := $(words $(SRCS_BONUS))
#* ==============================================================================
#*                                  RULES
#* ==============================================================================
all: $(NAME) project_logo

$(NAME): $(LIBFT_A) $(MLX_A) entry_message $(OBJS)
	@echo "${GREEN}${BOLD} DONE${RESET}"
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $@
	@echo "$(MAGENTA)${BOLD}${NAME} created\n$(RESET)"

bonus: $(NAME_BONUS) project_logo_bonus

$(NAME_BONUS): $(LIBFT_A) $(MLX_A) entry_message_bonus $(OBJS_BONUS)
	@echo "${GREEN}${BOLD} DONE${RESET}"
	@$(CC) $(CFLAGS) $(OBJS_BONUS) $(LDFLAGS) $(LDLIBS) -o $@
	@echo "$(MAGENTA)${BOLD}${NAME_BONUS} created\n$(RESET)"

#* ---- Objects ----
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	@printf "$(GREEN)${BOLD}$(OK)$(RESET)"

$(OBJ_DIR_BONUS)/%.o: $(SRC_DIR_BONUS)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(CPPFLAGS_BONUS) -c $< -o $@
	@printf "$(GREEN)${BOLD}$(OK)$(RESET)"

#* ---- Libft ----
$(LIBFT_A):
	@echo "$(CYAN)Building Libft...$(RESET)"
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)

#* ---- MinilibX ----
$(MLX_A):
	@echo "$(CYAN)Building MiniLibX...$(RESET)"
	@chmod +x $(MLX_DIR)/configure 2>/dev/null || true
	@$(MAKE) --no-print-directory -C $(MLX_DIR) >/dev/null 2>&1 || true
	@echo "$(MAGENTA)${BOLD}libmlx.a created\n$(RESET)"

#* ---- Convenience ----
run: $(NAME)
	@echo "$(YELLOW)${BOLD}[RUN] ./$(NAME) $(ARGS)$(RESET)"
	@-./$(NAME) $(ARGS)

valgrind:
	@echo "$(YELLOW)${BOLD}[VG] ./$(NAME) $(ARGS)$(RESET)"
	@valgrind --leak-check=full --show-leak-kinds=all \
		--track-origins=yes --suppressions=valgrind.supp\
		./$(NAME) $(ARGS) || true

valgrind_bonus:
	@echo "$(YELLOW)${BOLD}[VG] ./$(NAME_BONUS) $(ARGS)$(RESET)"
	@valgrind --leak-check=full --show-leak-kinds=all \
		--track-origins=yes --suppressions=valgrind.supp\
		./$(NAME_BONUS) $(ARGS) || true

#* ---- Cleanup ----
clean:
	@if [ -d $(OBJ_DIR) ] ; then echo "$(RED)[RM] objects$(RESET)" ; rm -rf $(OBJ_DIR) ; fi
	@if [ -d $(OBJ_DIR_BONUS) ] ; then echo "$(RED)[RM] objects_bonus$(RESET)" ; rm -rf $(OBJ_DIR_BONUS) ; fi
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean

fclean: clean
	@if [ -f $(NAME) ] ; then echo "$(RED)[RM] $(NAME)$(RESET)" ; fi
	@if [ -f $(NAME_BONUS) ] ; then echo "$(RED)[RM] $(NAME_BONUS)$(RESET)" ; fi
	@if [ -f libft/libft.a ] ; then echo "$(RED)[RM] libft.a$(RESET)" ; fi
	@if [ -f minilibx-linux/libmlx.a ] ; then echo "$(RED)[RM] libmlx.a$(RESET)" ; fi
	@if [ -f minilibx-linux/libmlx_Linux.a ] ; then echo "$(RED)[RM] libmlx_Linux.a$(RESET)" ; fi
	@rm -f $(NAME) $(NAME_BONUS)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean
	@$(MAKE) --no-print-directory -C $(MLX_DIR) clean >/dev/null 2>&1 || true

re: fclean all

re_bonus: fclean bonus

help:
	@echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
	@echo "$(BRIGHT_MAGENTA)all       →  ${RESET}Compile the program."
	@echo "$(BRIGHT_MAGENTA)clean     →  ${RESET}Removes temporary files."
	@echo "$(BRIGHT_MAGENTA)fclean    →  ${RESET}Deletes all generated files."
	@echo "$(BRIGHT_MAGENTA)re        →  ${RESET}Rebuilds the project."
	@echo "$(BRIGHT_MAGENTA)bonus     →  ${RESET}Compile the bonus version."
	@echo "$(BRIGHT_MAGENTA)re_bonus  →  ${RESET}Rebuilds the bonus version."
	@echo "$(BRIGHT_MAGENTA)run       →  ${RESET}Executes the program."
	@echo "$(BRIGHT_MAGENTA)valgrind  →  ${RESET}Check for memory leaks."
	@echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"

#* ---- Messages ----
entry_message:
	@echo "$(GREEN)${BOLD}Compiling ${NAME}$(RESET)"
	@echo "$(YELLOW)$(INFO) ${SRC_COUNT} files$(RESET)"

entry_message_bonus:
	@echo "$(GREEN)${BOLD}Compiling ${NAME_BONUS}$(RESET)"
	@echo "$(YELLOW)$(INFO) ${SRC_COUNT_BONUS} files$(RESET)"

debug_message:
	@echo "$(GREEN)${BOLD}Compiling ${NAME_DEBUG}$(RESET)"
	@echo "$(YELLOW)$(INFO) ${SRC_COUNT} files$(RESET)"

project_logo:
	@echo ""
	@echo "${CYAN}${BOLD}                     m  i  n  i  R  T                        ${RESET}"
	@echo         "  ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
	@echo "${WHITE}    ┏━┓    ┏━┓  ┏┓  ┏━┓  ┏━┓  ┏┓  ┏━━━━━┓ ┏━━━━━━━┓                 ${RESET}"
	@echo "${WHITE}    ┃ ┣┓  ┏┫ ┃  ┃┃  ┃ ┣┓ ┃ ┃  ┃┃  ┃ ┏━┓ ┃ ┗━━┓ ┏━━┛                 ${RESET}"
	@echo "${WHITE}    ┃ ┃┣┓┏┫┃ ┃  ┃┃  ┃ ┃┃┏┫ ┃  ┃┃  ┃ ┗━┛ ┃    ┃ ┃                    ${RESET}"
	@echo "${WHITE}    ┃ ┃┣┛┗┫┃ ┃  ┃┃  ┃ ┣┛┃┃ ┃  ┃┃  ┃ ┏┓ ┏┛    ┃ ┃                    ${RESET}"
	@echo "${WHITE}    ┃ ┣┛  ┗┫ ┃  ┃┃  ┃ ┃ ┗┫ ┃  ┃┃  ┃ ┃┃ ┗┓    ┃ ┃                    ${RESET}"
	@echo "${WHITE}    ┗━┛    ┗━┛  ┗┛  ┗━┛  ┗━┛  ┗┛  ┗━┛┗━━┛    ┗━┛                    ${RESET}"
	@echo         "  ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
	@echo "${CYAN}${BOLD}                            Eloi RAAD & Jean HUBBERT${RESET}"
	@echo ""

project_logo_bonus:
	@echo ""
	@echo "${CYAN}${BOLD}                     m  i  n  i  R  T                         ${RESET}"
	@echo         "  ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓"
	@echo "${WHITE}    ┏━┓    ┏━┓  ┏┓  ┏━┓  ┏━┓  ┏┓  ┏━━━━━┓ ┏━━━━━━━┓                 ${RESET}"
	@echo "${WHITE}    ┃ ┣┓  ┏┫ ┃  ┃┃  ┃ ┣┓ ┃ ┃  ┃┃  ┃ ┏━┓ ┃ ┗━━┓ ┏━━┛                 ${RESET}"
	@echo "${WHITE}    ┃ ┃┣┓┏┫┃ ┃  ┃┃  ┃ ┃┃┏┫ ┃  ┃┃  ┃ ┗━┛ ┃    ┃ ┃                    ${RESET}"
	@echo "${WHITE}    ┃ ┃┣┛┗┫┃ ┃  ┃┃  ┃ ┣┛┃┃ ┃  ┃┃  ┃ ┏┓ ┏┛    ┃ ┃                    ${RESET}"
	@echo "${WHITE}    ┃ ┣┛  ┗┫ ┃  ┃┃  ┃ ┃ ┗┫ ┃  ┃┃  ┃ ┃┃ ┗┓    ┃ ┃                    ${RESET}"
	@echo "${WHITE}    ┗━┛    ┗━┛  ┗┛  ┗━┛  ┗━┛  ┗┛  ┗━┛┗━━┛    ┗━┛                    ${RESET}"
	@echo         "  ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓"
	@echo "${WHITE}                    ┏━━━━┓   ┏━━━━┓  ┏━┓  ┏━┓  ┏┓   ┏┓  ┏━━━━┓    ${RESET}"
	@echo "${WHITE}                    ┃ ┏┓ ┃   ┃┏━━┓┃  ┃ ┣┓ ┃ ┃  ┃┃   ┃┃  ┃┏━━━┛    ${RESET}"
	@echo "${WHITE}                    ┃ ┗┛ ┗┓  ┃┃┏┓┃┃  ┃ ┃┃┏┫ ┃  ┃┃ ┃ ┃┃  ┃┗━━━━━┓  ${RESET}"
	@echo "${WHITE}                    ┃ ┏━┓ ┃  ┃┃┗┛┃┃  ┃ ┣┛┃┃ ┃  ┃┃   ┃┃  ┗━━━━┓ ┃  ${RESET}"
	@echo "${WHITE}                    ┃ ┗━┛ ┃  ┃┗━━┛┃  ┃ ┃ ┗┫ ┃  ┃┗━━━┛┃  ┏━━━━┛ ┃  ${RESET}"
	@echo "${WHITE}                    ┗━━━━━┛  ┗━━━━┛  ┗━┛  ┗━┛  ┗━━━━━┛  ┗━━━━━━┛  ${RESET}"
	@echo         "                  ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛"
	@echo "${CYAN}${BOLD}                                          Eloi RAAD & Jean HUBBERT${RESET}"
	@echo ""

#* ---- Phony -------------------------------------------------------------------
.PHONY: all clean fclean re re_bonus bonus help run valgrind valgrind_bonus