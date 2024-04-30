NAME := libft.a

SRC_DIR := src

LIBFT_DIR := libft

GNL_DIR := get_next_line

PRINTF_DIR := ft_printf

SRC_LIBFT_FILES := ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c	ft_memchr.c ft_memcmp.c	ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c	ft_putnbr_fd.c ft_strchr.c ft_strdup.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_substr.c ft_tolower.c	ft_toupper.c ft_strtrim.c ft_strjoin.c ft_split.c ft_striteri.c	ft_strmapi.c ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c get_next_line.c ft_dlclprint.c ft_atod.c ft_dtoa.c ft_isspace.c free_array_2d.c free_array_3d.c ft_superjoin.c ft_arrlen.c ft_megalen.c btree_create_node.c

SRC_PRINTF_FILES := ft_printf.c format_hub.c ft_lib_one.c ft_lib_two.c ft_strchr.c

SRC_LIBFT := $(SRC_LIBFT_FILES:%.c=$(LIBFT_DIR)/%.c)
SRC_PRINTF := $(SRC_PRINTF_FILES:%.c=$(PRINTF_DIR)/%.c)
SRC := $(SRC_LIBFT:%.c=$(SRC_DIR)/%.c) $(SRC_PRINTF:%.c=$(SRC_DIR)/%.c)

BUILD_DIR := .build
OBJ := $(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS := $(OBJ:.o=.d)

CC := cc
CFLAGS := -Wall -Wextra -Werror 
PREPFLAGS := -MMD -MP -I headers
AR := ar
ARFLAGS := -r -c -s

DIR_DUP = mkdir -p $(@D)

all: $(NAME)

$(NAME): $(OBJ)
	@$(AR) $(ARFLAGS) $(NAME) $(OBJ)
	@echo "\033[1;32m[libft compiled]\033[1;00m"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@$(DIR_DUP)
	@$(CC) $(CFLAGS) $(PREPFLAGS) -c -o $@ $<

-include $(DEPS)

clean: 
	@rm -rf $(BUILD_DIR)
	@echo "\033[1;32m[libft .o removed]\033[1;00m"

fclean: clean
	@rm -rf $(NAME)
	@echo "\033[1;32m[libft bin removed]\033[1;00m"

re: fclean all

.PHONY: all clean fclean re
