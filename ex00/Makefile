# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: na-kannan <na-kannan@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/01 00:00:00 by na-kannan          #+#    #+#              #
#    Updated: 2025/01/01 00:00:00 by na-kannan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME		= easyfind

# Compiler and flags
CXX			= c++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98
RM			= rm -f

# Source files
SRCS		= main.cpp

# Object files
OBJS		= $(SRCS:.cpp=.o)

# Header files
HEADERS		= easyfind.hpp

# Colors for output
GREEN		= \033[0;32m
YELLOW		= \033[0;33m
RED			= \033[0;31m
RESET		= \033[0m

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(YELLOW)Linking $(NAME)...$(RESET)"
	@$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) compiled successfully!$(RESET)"

%.o: %.cpp $(HEADERS)
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@$(RM) $(OBJS)
	@echo "$(GREEN)✓ Object files cleaned!$(RESET)"

fclean: clean
	@echo "$(RED)Removing $(NAME)...$(RESET)"
	@$(RM) $(NAME)
	@echo "$(GREEN)✓ Everything cleaned!$(RESET)"

re: fclean all

# Test rule
test: all
	@echo "$(YELLOW)Running $(NAME)...$(RESET)"
	@./$(NAME)

.PHONY: all clean fclean re test
