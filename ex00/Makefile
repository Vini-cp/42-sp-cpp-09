NAME 		:= btc

SRCS		:= main.cpp BitcoinExchange.cpp

OBJ_FOLDER	:= obj

OBJS 		:= $(addprefix ${OBJ_FOLDER}/, ${SRCS:.cpp=.o})

CC := c++
CFLAGS = -Wall -Wextra -Werror -g -std=c++98 -fsanitize=address

.PHONY: all re clean fclean test

all : $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_FOLDER)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	@rm -rf $(OBJ_FOLDER)

fclean : clean
	@rm -f $(NAME)

re : clean all