# Colors
RED			= "\033[1;31m"
GREEN		= "\033[1;32m"
RESET		= "\033[m"

ifeq ($(DMEM),1)
MEM 		= -fsanitize=address -g
endif

# Variables
NAME		= philo
CFLAGS		= -Wall -Wextra -Werror
CC			= cc -pthread

OBJ_DIR		= objs/
SRC_DIR		= src/
INC_DIR		= inc/

SRC_FILES	=	main.c \
				parse.c \
				init.c \
				utils.c \
				error.c \
				philo.c \
				exit.c

OBJS		= $(addprefix ${OBJ_DIR}, ${SRC_FILES:.c=.o})
INC			= -I./$(INC_DIR)

# Rules
all : $(NAME)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@mkdir -p ${@D}
	$(CC) $(CFLAGS) $(MEM) $(INC) -c $< -o $@

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(MEM) $(INC) $(OBJS) -o $@
	@echo -n "Compiling Philosophers"
	@echo $(GREEN)"\tOK"$(RESET)

clean :
	rm -rf $(OBJ_DIR)

fclean : clean
	rm -f $(NAME)

re : fclean all
	make all

.PHONY : all clean fclean re