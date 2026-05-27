NAME = PmergeMe
CC = c++
HEADER =	types.hpp \
			utility.hpp \
			jSequence.hpp \
			mapPairs.hpp \
			FordJohnsonInsert.hpp \
			FordJohnsonSort.hpp

FLAGS = -Wall -Wextra -Werror -std=c++98 -g
# FLAGS =  -std=c++98 -g

SRCS =	main.cpp \
		utility.cpp \
		jSequence.cpp \
		mapPairs.cpp \
		FordJohnsonInsert.cpp \
		FordJohnsonSort.cpp

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
