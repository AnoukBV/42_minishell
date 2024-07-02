NAME := minishell

LIBS := libft
LIBS_TGT := lib/libft/libft.a

HEAD := headers lib/libft/headers

SRC_DIR := src
SRC_FILES := main.c \
			errors.c \
			shell_prompt.c \
			heredoc/heredoc.c \
			heredoc/heredoc_utils.c \
			parsing/newlines.c \
			parsing/parsing.c \
			parsing/quotes.c \
			parsing/words.c \
			parsing/categorization.c \
			parsing/divide.c \
			parsing/binary_tree_utils.c \
			parsing/redirections.c \
			parsing/expansion.c \
			parsing/check_expansion.c \
			parsing/expand.c \
			parsing/expansion_utils.c \
			parsing/inspect_token.c \
			parsing/create_argv.c \
			parsing/heredoc_expansion.c \
			parsing/fill_pipeline.c \
			parsing/clean_parsing.c \
			parsing/check_syntax.c \
			parsing/ft_esc_split.c \
			parsing/errors_unclosed_ambiguous.c \
			environment/set.c \
			environment/ft_export.c \
			environment/ft_unset.c \
			environment/ft_export_print.c \
			environment/ft_export_utils.c \
			environment/print_env.c \
			environment/transform_envp.c \
			environment/get_env_element.c \
			environment/env_find_key.c \
			environment/free_env_list.c \
			lists_utils/command_utils.c \
			lists_utils/fd_list_utils.c \
			lists_utils/pid_list_utils.c \
			lists_utils/env_list_utils.c \
			execution/pipeline.c \
			execution/exec_utils.c \
			execution/execute.c \
			execution/redirections.c \
			execution/exec_errors.c \
			execution/builtin_exec.c \
			signals/set_signal.c \
			signals/signal_handlers.c \
			builtins/cd.c \
			builtins/pwd.c \
			builtins/echo.c \
			builtins/exit.c \
			builtins/builtin_utils.c 

SRC := $(SRC_FILES:%.c=$(SRC_DIR)/%.c)

BUILD_DIR := .build
OBJ := $(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS := $(OBJ:.o=.d)

INCLUDES_DIR = headers
INCLUDES = -I$(INCLUDES_DIR) \
			-Ilibft

CC := cc
CFLAGS := -Wall -Wextra -Werror -g
PREPFLAGS := $(addprefix -I, $(HEAD)) -MMD -MP
LDFLAGS := -Llib/libft -Lheaders -lreadline -lhistory
LDLIBS := -lft

DIR_DUP = mkdir -p $(@D)

all: $(NAME)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@$(DIR_DUP)
	@$(CC) $(CFLAGS) $(PREPFLAGS) $(INCLUDES) -c -o $@ $<

$(NAME): $(OBJ)
	@make -C lib/libft -s
	@$(CC) $(LDFLAGS) $(OBJ) $(LIBS_TGT) $(LDLIBS) $(INCLUDES) -o $(NAME)
	@echo "\033[1;32m[mandatory compiled]\033[1;00m"

-include $(DEPS)

clean:
	@make -C lib/libft clean
	@rm -rf $(OBJ) $(DEPS) $(BUILD_DIR)
	@echo "\033[1;32m[.o removed]\033[1;00m"

fclean: clean
	@make -C lib/libft fclean
	@rm -rf $(NAME)
	@echo "\033[1;32m[bin removed]\033[1;00m"

re: fclean all

.PHONY: all re fclean clean
