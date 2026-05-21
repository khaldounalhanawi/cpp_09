NAME = pp
CC = c++
HEADER =	types.hpp \
			utility.hpp \
			jSequence.hpp

FLAGS = -Wall -Wextra -Werror -std=c++98 -g

SRCS =	main.cpp \
		utility.cpp \
		jSequence.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
