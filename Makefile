.DEFAULT_GOAL := all

SERVER := server
CLIENT := client

CFLAGS := -Wall -Wextra -Werror -Ift_printf
LDFLAGS := -Lft_printf -lftprintf

S_SRC := server.c
C_SRC := client.c
S_OBJ := $(S_SRC:.c=.o)
C_OBJ := $(C_SRC:.c=.o)

.PHONY:		all clean fclean re

$(S_OBJ):	$(S_SRC)
			$(CC) $(CFLAGS) $< -c

$(C_OBJ):	$(C_SRC)
			$(CC) $(CFLAGS) $< -c

$(SERVER):	$(S_OBJ)
			$(MAKE) -C ft_printf bonus
			$(CC) $(S_OBJ) -o $(SERVER) $(LDFLAGS)

$(CLIENT):	$(C_OBJ)
			$(MAKE) -C ft_printf bonus
			$(CC) $(C_OBJ) -o $(CLIENT) $(LDFLAGS)

all:		$(SERVER) $(CLIENT)

clean:
			$(RM) -f $(S_OBJ) $(C_OBJ)

fclean:		clean
			$(RM) -f $(CLIENT) $(SERVER)

re:			fclean all
