NAME = client
NAME_2 = server

CC = cc
CFLAGS = -Wall -Werror -Wextra
RM = rm -rf

OBJC = client.c
OBJS = server.c
HEDER = minitalk.h

all: $(NAME_2) $(NAME)

$(NAME_2): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@
	
$(NAME): $(OBJC) $(HEDER)
	$(CC) $(CFLAGS) $(OBJC) -o $@
	
clean:
	$(RM) $(NAME) $(NAME_2)

fclean: clean

re: fclean all