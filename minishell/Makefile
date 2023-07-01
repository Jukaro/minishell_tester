CC=				clang
CFLAGS=			-g

NAME=			minishell
SRCS=			lol.c
OBJS= 			${SRCS:.c=.o}

YELLOW=\033[38;5;226m
GREEN=\033[38;5;82m
CYAN=\033[38;5;51m
DEFAULT=\033[39m
CLEANL=\r\033[K

%.o: %.c
	@printf "$(CLEANL)$(YELLOW)Compiling objs : $<$(DEFAULT)"
	@${CC} ${CFLAGS} -c $< -o $@

$(NAME): $(OBJS)
	@printf "$(CLEANL)$(GREEN)Done compiling objs$(DEFAULT)\n"
	@printf "$(CLEANL)$(YELLOW)Compiling LIBFT ...$(DEFAULT)"
	@make bonus -C libft -s
	@printf "$(CLEANL)$(GREEN)Done compiling LIBFT$(DEFAULT)\n"
	@printf "$(CLEANL)$(YELLOW)Compiling $@ ...$(DEFAULT)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L./libft -lft -lreadline
	@printf "$(CLEANL)$(GREEN)Done compiling $@$(DEFAULT)\n"

all: $(NAME)

clean:
	@rm -f $(OBJS)
	@make clean -C libft -s

fclean: clean
	@rm -f $(NAME)
	@make fclean -C libft -s

re:		fclean all
