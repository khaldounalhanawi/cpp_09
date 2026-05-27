NAME = PmergeMe
CC = c++
FLAGS = -Wall -Wextra -Werror -std=c++98 -I$(HEADER_DIR) -I$(FJ_HEADER_DIR)

HEADER_DIR = ./include
HEADER = $(HEADER_DIR)/utility.hpp
SRCS_DIR = ./src
SRCS =	$(SRCS_DIR)/main.cpp \
		$(SRCS_DIR)/utility.cpp

FJ_HEADER_DIR = ./FordJohnson_algorithm/include
FJ_HEADER =	$(FJ_HEADER_DIR)/types.hpp \
			$(FJ_HEADER_DIR)/jSequence.hpp \
			$(FJ_HEADER_DIR)/mapPairs.hpp \
			$(FJ_HEADER_DIR)/FordJohnsonInsert.hpp \
			$(FJ_HEADER_DIR)/FordJohnsonSort.hpp
FJ_SRCS_DIR = ./FordJohnson_algorithm/
FJ_SRCS =	$(FJ_SRCS_DIR)jSequence.cpp \
			$(FJ_SRCS_DIR)mapPairs.cpp \
			$(FJ_SRCS_DIR)FordJohnsonInsert.cpp \
			$(FJ_SRCS_DIR)FordJohnsonInsert_deque.cpp \
			$(FJ_SRCS_DIR)FordJohnsonSort.cpp \
			$(FJ_SRCS_DIR)FordJohnsonSort_deque.cpp

OBJS_DIR = ./objects
SRC_OBJS_DIR = $(OBJS_DIR)/src
FJ_OBJS_DIR = $(OBJS_DIR)/FordJohnson_algorithm

OBJS = $(patsubst $(SRCS_DIR)/%.cpp, $(SRC_OBJS_DIR)/%.o, $(SRCS))
FJ_OBJS = $(patsubst $(FJ_SRCS_DIR)%.cpp, $(FJ_OBJS_DIR)/%.o, $(FJ_SRCS))

all: $(NAME)

$(NAME): $(OBJS) $(FJ_OBJS)
	$(CC) $(FLAGS) $(OBJS) $(FJ_OBJS) -o $(NAME)

$(SRC_OBJS_DIR)/%.o: $(SRCS_DIR)/%.cpp $(HEADER) $(FJ_HEADER) | $(SRC_OBJS_DIR)
	$(CC) $(FLAGS) -c $< -o $@

$(FJ_OBJS_DIR)/%.o: $(FJ_SRCS_DIR)%.cpp $(HEADER) $(FJ_HEADER) | $(FJ_OBJS_DIR)
	$(CC) $(FLAGS) -c $< -o $@

$(SRC_OBJS_DIR):
	mkdir -p $(SRC_OBJS_DIR)

$(FJ_OBJS_DIR):
	mkdir -p $(FJ_OBJS_DIR)

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
