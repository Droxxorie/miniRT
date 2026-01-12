# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eraad <eraad@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/15 12:06:42 by eraad             #+#    #+#              #
#    Updated: 2026/01/11 01:31:47 by eraad            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#* ==============================================================================
#*                                   BINARY
#* ==============================================================================
NAME        := libft.a

#* ==============================================================================
#*                                   TOOLCHAIN
#* ==============================================================================
CC          := cc
AR          := ar rcs
CFLAGS      := -Wall -Wextra -Werror -MMD -MP
INCLUDES    := -Iinclude

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
#*                                   LAYOUT
#* ==============================================================================
SRC_DIR         := sources
OBJ_DIR         := objects

#* ==============================================================================
#*                                   SOURCES
#* ==============================================================================
SRCS := \
	$(SRC_DIR)/ft_is/ft_isalnum.c \
	$(SRC_DIR)/ft_is/ft_isalpha.c \
	$(SRC_DIR)/ft_is/ft_isascii.c \
	$(SRC_DIR)/ft_is/ft_isdigit.c \
	$(SRC_DIR)/ft_is/ft_isprint.c \
	$(SRC_DIR)/ft_is/ft_iswhitespace.c \

SRCS += \
	$(SRC_DIR)/ft_lst/ft_lstadd_back.c \
	$(SRC_DIR)/ft_lst/ft_lstadd_front.c \
	$(SRC_DIR)/ft_lst/ft_lstclear.c \
	$(SRC_DIR)/ft_lst/ft_lstdelone.c \
	$(SRC_DIR)/ft_lst/ft_lstiter.c \
	$(SRC_DIR)/ft_lst/ft_lstlast.c \
	$(SRC_DIR)/ft_lst/ft_lstmap.c \
	$(SRC_DIR)/ft_lst/ft_lstnew.c \
	$(SRC_DIR)/ft_lst/ft_lstsize.c \

SRCS += \
	$(SRC_DIR)/ft_mem/ft_bzero.c \
	$(SRC_DIR)/ft_mem/ft_calloc.c \
	$(SRC_DIR)/ft_mem/ft_memchr.c \
	$(SRC_DIR)/ft_mem/ft_memcmp.c \
	$(SRC_DIR)/ft_mem/ft_memcpy.c \
	$(SRC_DIR)/ft_mem/ft_memmove.c \
	$(SRC_DIR)/ft_mem/ft_memset.c \
	$(SRC_DIR)/ft_mem/ft_realloc.c \

SRCS += \
	$(SRC_DIR)/ft_put/ft_putchar_fd.c \
	$(SRC_DIR)/ft_put/ft_putendl_fd.c \
	$(SRC_DIR)/ft_put/ft_putnbr_fd.c \
	$(SRC_DIR)/ft_put/ft_putstr_fd.c \

SRCS += \
	$(SRC_DIR)/ft_str/ft_strchr.c \
	$(SRC_DIR)/ft_str/ft_strdup.c \
	$(SRC_DIR)/ft_str/ft_striteri.c \
	$(SRC_DIR)/ft_str/ft_strjoin.c \
	$(SRC_DIR)/ft_str/ft_strlcat.c \
	$(SRC_DIR)/ft_str/ft_strlcpy.c \
	$(SRC_DIR)/ft_str/ft_strlen.c \
	$(SRC_DIR)/ft_str/ft_strmapi.c \
	$(SRC_DIR)/ft_str/ft_strncmp.c \
	$(SRC_DIR)/ft_str/ft_strnstr.c \
	$(SRC_DIR)/ft_str/ft_strrchr.c \
	$(SRC_DIR)/ft_str/ft_strtrim.c \
	$(SRC_DIR)/ft_str/ft_substr.c \
	
SRCS += \
	$(SRC_DIR)/gnl/get_next_line.c \
	$(SRC_DIR)/gnl/consume_gnl.c \

SRCS += \
	$(SRC_DIR)/maths/ft_abs.c \
	$(SRC_DIR)/maths/ft_fabs.c \
	$(SRC_DIR)/maths/ft_pow.c \
	$(SRC_DIR)/maths/ft_argmax.c \
	$(SRC_DIR)/maths/ft_max.c \
	$(SRC_DIR)/maths/ft_min.c \
	$(SRC_DIR)/maths/ft_argmin.c \

SRCS += \
	$(SRC_DIR)/printf/ft_printaddr_fd.c \
	$(SRC_DIR)/printf/ft_printchar_fd.c \
	$(SRC_DIR)/printf/ft_printdbl.c \
	$(SRC_DIR)/printf/ft_printf.c \
	$(SRC_DIR)/printf/ft_printhex_fd.c \
	$(SRC_DIR)/printf/ft_printnbr_fd.c \
	$(SRC_DIR)/printf/ft_printstr_fd.c \
	$(SRC_DIR)/printf/ft_printunbr_fd.c \
	
SRCS += \
	$(SRC_DIR)/utils/ft_atodbl.c \
	$(SRC_DIR)/utils/ft_atoi.c \
	$(SRC_DIR)/utils/ft_count_words.c \
	$(SRC_DIR)/utils/ft_dbltoa.c \
	$(SRC_DIR)/utils/ft_intlen.c \
	$(SRC_DIR)/utils/ft_itoa.c \
	$(SRC_DIR)/utils/ft_split.c \
	$(SRC_DIR)/utils/ft_tolower.c \
	$(SRC_DIR)/utils/ft_toupper.c \
	$(SRC_DIR)/utils/ft_free_str_array.c \
	$(SRC_DIR)/utils/ft_free_2d_str_array.c \

OBJS := $(SRCS:%=$(OBJ_DIR)/%.o)

DEPS      := $(OBJS:.o=.d)
SRC_COUNT := $(words $(SRCS))

#* ==============================================================================
#*                                   RULES
#* ==============================================================================
all: $(NAME)

$(NAME): $(OBJS)
	@rm -f $(COUNT_FILE)
	@echo ""
	@$(AR) $@ $(OBJS)
	@echo "$(MAGENTA)${BOLD}${NAME} created!\n$(RESET)"

$(OBJ_DIR)/%.c.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@count=$$(cat $(COUNT_FILE) 2>/dev/null || echo 0); \
	count=$$((count + 1)); \
	echo $$count > $(COUNT_FILE); \
	$(call progress_bar,$$count,$(SRC_COUNT),$(NAME),$<)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

#* ==============================================================================
#* PROGRESS BAR
#* ==============================================================================

CURRENT_FILE = 0

define progress_bar
	if [ $(1) -eq 1  ] ; then printf "$(CYAN)Building $(3)...\n$(GREEN)${BOLD}Compiling ${3}\n$(YELLOW)$(INFO) ${2} files$(RESET)\n" ; fi; \
	percent=$$(( $(1) * 100 / $(2) )); \
	progress=$$(( $(1) * 50 / $(2) )); \
	printf "\r\033[K$(WHITE)"; \
	for i in $$(seq 1 $$progress); do printf "█"; done; \
	for i in $$(seq $$((progress + 1)) 50); do printf "░"; done; \
	printf " %d%% $(RESET)" $$percent;
endef

COUNT_FILE := .make_count

#* ==============================================================================
#*                                   DEPENDENCIES
#* ==============================================================================
-include $(DEPS)

.PHONY: all clean fclean re entry_message
