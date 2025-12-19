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
#* BINARY
#* ==============================================================================
NAME            := miniRT

#* ==============================================================================
#* LAYOUT
#* ==============================================================================
SRC_DIR         := sources
OBJ_DIR         := objects

LIBFT_DIR       := libft
LIBFT_A         := $(LIBFT_DIR)/libft.a

MLX_DIR         := minilibx-linux
MLX_A           := $(MLX_DIR)/libmlx.a

#* ==============================================================================
#* TOOLCHAIN
#* ==============================================================================
CC              := cc
CFLAGS          := -Wall -Wextra -Werror -O3 -ffast-math -g3
CPPFLAGS        := -Iincludes -Ilibft -Iminilibx-linux

LDFLAGS         := -L$(LIBFT_DIR) -L$(MLX_DIR)
LDLIBS          := -lft -lmlx -lXext -lX11 -lm -lz

NAME_DEBUG      := $(NAME)_debug
DEBUG_FLAGS     := -O0 -g3 -DDEBUG
ASAN_FLAGS      := -O0 -g3 -fsanitize=address -fno-omit-frame-pointer

ARGS            := test_files/test.rt

#* ==============================================================================
#* COLORS/SYMBOLS/STYLES
#* ==============================================================================
RESET        := \033[0m
BOLD         := \033[1m
DIM          := \033[2m
ITALIC       := \033[3m
UNDERLINE    := \033[4m

BLACK        := \033[30m
RED          := \033[31m
GREEN        := \033[32m
YELLOW       := \033[33m
BLUE         := \033[34m
MAGENTA      := \033[35m
CYAN         := \033[36m
WHITE        := \033[37m

BRIGHT_GREEN   := \033[92m
BRIGHT_MAGENTA := \033[95m
BRIGHT_CYAN    := \033[96m

OK      := ✓
KO      := ✗
INFO    := ⓘ

#* ==============================================================================
#* SOURCES
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
	$(SRC_DIR)/inputs/entities_utils.c \
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
    $(SRC_DIR)/maths/matrix/rotation.c \
    $(SRC_DIR)/maths/matrix/mult.c \
	$(SRC_DIR)/maths/matrix/transpose.c \
	$(SRC_DIR)/maths/matrix/inverse.c \

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
#* RULES
#* ==============================================================================
all: $(NAME) project_logo

$(NAME): $(LIBFT_A) $(MLX_A) entry_message $(OBJS)
	@echo "${GREEN}${BOLD} DONE${RESET}"
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $@
	@echo "$(MAGENTA)${BOLD}${NAME} created\n$(RESET)"

#* ---- Objects ----
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
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

debug: $(LIBFT_A) $(MLX_A) debug_message $(OBJS)
	@echo "${GREEN}${BOLD} DONE${RESET}"
	@$(CC) $(DEBUG_FLAGS) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $(NAME_DEBUG)
	@echo "$(MAGENTA)${BOLD}${NAME_DEBUG} created\n$(RESET)"

valgrind: debug
	@echo "$(YELLOW)${BOLD}[VG] ./$(NAME_DEBUG) $(ARGS)$(RESET)"
	@valgrind --leak-check=full --show-leak-kinds=all \
		--track-origins=yes --suppressions=valgrind.supp\
		./$(NAME_DEBUG) $(ARGS) || true

#* ---- Cleanup ----
clean:
	@echo "$(RED)[RM] objects$(RESET)"
	@rm -rf $(OBJ_DIR)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean
	@$(MAKE) --no-print-directory -C $(MLX_DIR) clean >/dev/null 2>&1 || true

fclean: clean
	@echo "$(RED)[RM] $(NAME)$(RESET)"
	@echo "$(RED)[RM] $(NAME_DEBUG)$(RESET)"
	@echo "$(RED)[RM] libft.a$(RESET)"
	@echo "$(RED)[RM] libmlx.a$(RESET)\n"
	@rm -f $(NAME) $(NAME_DEBUG) $(NAME_ASAN)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean

re: fclean all

help:
	@echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
	@echo "$(BRIGHT_MAGENTA)all       →  ${RESET}Compile the program."
	@echo "$(BRIGHT_MAGENTA)clean     →  ${RESET}Removes temporary files."
	@echo "$(BRIGHT_MAGENTA)fclean    →  ${RESET}Deletes all generated files."
	@echo "$(BRIGHT_MAGENTA)re        →  ${RESET}Rebuilds the project."
	@echo "$(BRIGHT_MAGENTA)run       →  ${RESET}Executes the program."
	@echo "$(BRIGHT_MAGENTA)valgrind  →  ${RESET}Check for memory leaks."
	@echo "$(BRIGHT_MAGENTA)debug     →  ${RESET}Compile with debug flags."
	@echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"

#* ---- Messages ----
entry_message:
	@echo "$(GREEN)${BOLD}Compiling ${NAME}$(RESET)"
	@echo "$(YELLOW)$(INFO) ${SRC_COUNT} files$(RESET)"

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

#* ---- Phony -------------------------------------------------------------------
.PHONY: all clean fclean re help run valgrind debug