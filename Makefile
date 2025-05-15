CLIENT = client
SERVER = server
CLIENT_BONUS = client_bonus
SERVER_BONUS = server_bonus
CC = cc
FLAGS = -Wall -Wextra -Werror
FT_PRINTF = ./ft_printf
FT_PRINTF_SRCS = $(FT_PRINTF)/ft_put_s.c $(FT_PRINTF)/ft_put_c.c $(FT_PRINTF)/ft_printf.c $(FT_PRINTF)/ft_put_d.c $(FT_PRINTF)/ft_put_p.c $(FT_PRINTF)/ft_put_u.c $(FT_PRINTF)/ft_put_x.c
SRCS_CLIENT = client.c $(FT_PRINTF_SRCS)
SRCS_SERVER = server.c $(FT_PRINTF_SRCS)
SRCS_CLIENT_BONUS = client_bonus.c $(FT_PRINTF_SRCS)
SRCS_SERVER_BONUS = server_bonus.c $(FT_PRINTF_SRCS)
OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)
OBJS_SERVER = $(SRCS_SERVER:.c=.o)
OBJS_CLIENT_BONUS = $(SRCS_CLIENT_BONUS:.c=.o)
OBJS_SERVER_BONUS = $(SRCS_SERVER_BONUS:.c=.o)
INCLUDES = -I includes

all: $(CLIENT) $(SERVER)

$(CLIENT): $(OBJS_CLIENT)
	$(CC) $(FLAGS) $(INCLUDES) $(OBJS_CLIENT) -o $(CLIENT)

$(SERVER): $(OBJS_SERVER)
	$(CC) $(FLAGS) $(INCLUDES) $(OBJS_SERVER) -o $(SERVER)

bonus: $(CLIENT_BONUS) $(SERVER_BONUS)

$(CLIENT_BONUS): $(OBJS_CLIENT_BONUS)
	$(CC) $(FLAGS) $(INCLUDES) $(OBJS_CLIENT_BONUS) -o $(CLIENT_BONUS)
	
$(SERVER_BONUS): $(OBJS_SERVER_BONUS)
	$(CC) $(FLAGS) $(INCLUDES) $(OBJS_SERVER_BONUS) -o $(SERVER_BONUS)

clean: 
	rm -f $(OBJS_CLIENT) $(OBJS_SERVER) $(OBJS_CLIENT_BONUS) $(OBJS_SERVER_BONUS)

fclean: clean
	rm -f $(CLIENT) $(SERVER) $(CLIENT_BONUS) $(SERVER_BONUS)

re: fclean all

PHONY: all clean fclean re
