# 0. Main Info
NAME	= jsonReader.a
C_COMP	= c++
C_ARRC	= ar -rc
C_FLAG	= -Wall -Werror -Wextra -std=c++98
C_MDIR	= mkdir -p
C_REMO	= rm -rf
C_PUTS	= printf

# C. Colors
P_WHITE = \033[0m
P_LBLUE = \033[38;5;32m
P_DBLUE = \033[38;5;21m
P_PRPLE = \033[38;5;93m
P_NCYAN = \033[38;5;37m
P_MAGEN = \033[38;5;99m
P_GREEN = \033[38;5;40m
P_LGREN = \033[38;5;42m
P_NWINE = \033[38;5;88m

# 1. Directories
D_HDRS	= -I ./includes/
D_SRCS	= src/
D_OBJS	= obj/

# 2. Sources & Objects
DS_CLAS	=	classes/
N_CLAS	=	JsonNode.cpp	\
			DataNode.cpp	\
			JsonData.cpp	\
			JsonReader.cpp	\

# 3. Source Manipulation
F_SRCS	=	$(addprefix $(D_SRCS)$(DS_CLAS), $(N_CLAS))
N_OBJS	=	$(N_CLAS:.cpp=.opp)
F_OBJS	=	$(addprefix $(D_OBJS), $(N_OBJS))

# 4. Mandatory Rules
#	0. Default
all		: $(NAME)

#	1. Name
$(NAME)		: $(D_OBJS) $(F_OBJS)
	@$(C_PUTS) "\n\t$(P_NCYAN)Finishing $(NAME)..: $(P_LBLUE)$(NAME)$(P_WHITE)\n"
	@$(C_ARRC) -o $@ $(F_OBJS)
	@ranlib $@
	@$(C_PUTS) "$(P_GREEN)Done!$(P_WHITE)\n"

#	2. Object Generation
$(D_OBJS)%.opp	: $(D_SRCS)*/%.cpp
	@$(C_PUTS) "\t$(P_PRPLE)Generating $(NAME)..: %-33.33s\r $(P_WHITE)" $@
	@$(C_COMP) $(C_FLAG) $(D_HDRS) -c $< -o $@

#	3. Objects Directory Creator
$(D_OBJS)	:
	@clear
	@$(C_PUTS) "$(P_LGREN)Starting $(NAME) compilation...$(P_WHITE)"
	@$(C_PUTS) "\n\t$(P_MAGEN)Creating $(NAME) objects directory...$(P_WHITE)\n"
	@$(C_MDIR) $(D_OBJS)

#	4. Clean Objects
clean		:
	@$(C_PUTS) "$(P_NWINE)Cleaning $(NAME) objects...$(P_WHITE)\n"
	@${C_REMO} $(D_OBJS)

#	5. Clean Objects, and Binary
fclean		:
	@$(C_PUTS) "$(P_NWINE)Cleaning $(NAME) objects...$(P_WHITE)\n"
	@${C_REMO} $(D_OBJS)
	@$(C_PUTS) "$(P_NWINE)Deleting $(NAME)...$(P_WHITE)\n"
	@${C_REMO} $(NAME)

#	6. Clean all and redo
re		: fclean all

#	7. Test memory leaks
val		:
	@valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

#	8. Phony
.PHONY: all clean fclean re val



test: re
	@clear
	@c++ main.cpp ./jsonReader.a -o test.out
	@./test.out

valtest: re
	@clear
	@c++ main.cpp ./jsonReader.a -o test.out
	@valgrind --leak-check=full --show-leak-kinds=all ./test.out