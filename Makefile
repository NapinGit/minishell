NAME1	= minishell
CC = clang
SANITIZE = minishell_sanitize
FLAGS = -Wall -Werror -Wextra -g
FLAGF = -fsanitize=address -g
OBJ_DIR = obj/
SRC_DIR =	$(shell find ./srcs -type d)
SRC	= cd.c cd2.c utils.c echo.c bin_local.c export.c unset.c pwd.c copytools.c copytools2.c redirecttools.c env.c exec.c exitfree.c finddollar.c finddollar2.c finddollarbis.c finddollarbis2.c mymultipipe.c mymultipipetools.c new_env.c parseerror.c redirectindouble.c tools.c firstcut.c secondcut.c bin.c bin2.c builtin.c main.c myprompt.c

OBJ	= $(addprefix $(OBJ_DIR),$(SRC:%.c=%.o))
vpath %.c $(SRC_DIR)

all :	$(NAME1)

$(OBJ_DIR)%.o : %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@

$(NAME1) : $(OBJ)
	@echo "\033[0;34mGenerating prog minishell..."
	$(MAKE) -C ./libft all
	$(CC) $(FLAGS) $(OBJ) -o $(NAME1) -lreadline -L ./libft -lft
	@echo "\033[0m"

clean:
	@echo "\033[0;31mCleaning obj. files..."
	$(MAKE) -C ./libft clean
	rm -rf $(OBJ_DIR)
	@echo "\033[0m"

fclean: clean
	@echo "\033[0;31mRemoving prog minishell..."
	$(MAKE) -C ./libft fclean
	rm -rf $(NAME1)
	rm -rf $(SANITIZE)
	@echo "\033[0m"

sanitize: $(SANITIZE)

$(SANITIZE): $(OBJ)
	@echo "\033[0;33mMake minishell with fsanitize=address -g..."
	$(MAKE) -C ./libft all
	$(CC) $(FLAGS) $(FLAGF) $(OBJ) -o $(SANITIZE) -lreadline -L ./libft -lft
	@echo "\033[0m"

re : fclean all

c : clean

f : fclean

r : re

s : sanitize
