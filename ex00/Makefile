NAME = btc
CC = c++
FLAGS = -Wall -Wextra -Werror -std=c++98 -I$(HEADER_DIR) -I$(SM_HEADER_DIR)

HEADER_DIR = ./include
HEADER =	$(HEADER_DIR)/buildDataBase.hpp \
			$(HEADER_DIR)/types.hpp \
			$(HEADER_DIR)/validateDate.hpp \

SRCS_DIR = ./src
SRCS =	$(SRCS_DIR)/main.cpp \
		$(SRCS_DIR)/buildDataBase.cpp \
		$(SRCS_DIR)/validateDate.cpp

SM_HEADER_DIR = ./stringManipulation/include
SM_HEADER =	$(SM_HEADER_DIR)/types_str.hpp \
			$(SM_HEADER_DIR)/stringManipulation.hpp

SM_SRCS_DIR = ./stringManipulation
SM_SRCS =	$(SM_SRCS_DIR)/stringManipulation.cpp

OBJS_DIR = ./objects
SRC_OBJS_DIR = $(OBJS_DIR)/src
SM_OBJS_DIR = $(OBJS_DIR)/stringManipulation

OBJS = $(patsubst $(SRCS_DIR)/%.cpp, $(SRC_OBJS_DIR)/%.o, $(SRCS))
SM_OBJS = $(patsubst $(SM_SRCS_DIR)%.cpp, $(SM_OBJS_DIR)/%.o, $(SM_SRCS))

all: $(NAME)

$(NAME): $(OBJS) $(SM_OBJS)
	$(CC) $(FLAGS) $(OBJS) $(SM_OBJS) -o $(NAME)

$(SRC_OBJS_DIR)/%.o: $(SRCS_DIR)/%.cpp $(HEADER) $(SM_HEADER) | $(SRC_OBJS_DIR)
	$(CC) $(FLAGS) -c $< -o $@

$(SM_OBJS_DIR)/%.o: $(SM_SRCS_DIR)%.cpp $(HEADER) $(SM_HEADER) | $(SM_OBJS_DIR)
	$(CC) $(FLAGS) -c $< -o $@

$(SRC_OBJS_DIR):
	mkdir -p $(SRC_OBJS_DIR)

$(SM_OBJS_DIR):
	mkdir -p $(SM_OBJS_DIR)

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
