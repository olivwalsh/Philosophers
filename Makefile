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
CC			= cc

OBJ_DIR		= objs/
SRC_DIR		= src/
INC_DIR		= inc/

SRC_FILES	=	main.c \
				error.c

OBJS		= $(addprefix ${OBJ_DIR}, ${SRC_FILES:.c=.o})
INC			= -I./$(INC_DIR)

# Rules
all : $(NAME)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@mkdir -p ${@D}
	$(CC) $(CFLAGS) $(MEM) $(INC) -c $< -o $@

$(NAME) : $(OBJS)
	@echo -n "Compiling Philosophers"
	$(CC) $(CFLAGS) $(MEM) $(INC) $(OBJS) -o $@
	@echo $(GREEN)"\tOK"$(RESET)

clean :
	rm -rf $(OBJ_DIR)

fclean : clean
	rm -f $(NAME)

re : fclean all
	make all

.PHONY : all clean fclean re