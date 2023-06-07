### VARIABLES ###
NAME		:=	RPN

SRC			:=	main.cpp RPN.cpp
INC			:=	RPN.hpp
OBJDIR		:=	objs
CXXFLAGS	:= -Wall -Wextra -Werror -std=c++98 -g
CXX			:= c++

### AUTO VARIABLES ###

OBJ		:=	$(addprefix $(OBJDIR)/, $(SRC:.cpp=.o))
DEPS	:=	$(OBJ:.o=.d)

### RULES ###

all: $(NAME)

run: $(NAME)
	./$(NAME)

$(NAME): $(OBJ)
	$(CXX) $^ -o $@

$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

-include $(DEPS)

$(OBJDIR):
	mkdir -p $@

### CLEAN UP ###

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

### PHONY ###

.PHONY: all clean fclean re
