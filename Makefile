# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/05 12:29:27 by gpouyat           #+#    #+#              #
#    Updated: 2019/02/14 17:15:36 by gpouyat          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# .NOTPARALLEL:

.PHONY: all clean fclean re miniclean minifclean minire

C_NO = \033[0m
C_G = \033[0;32m
C_Y = \033[1;33m
C_B = \033[1;34m
C_C = \033[1;36m
C_R = \033[1;31m

SRCS_SERVER			+= /server/main.c /server/handle.c /server/handle_ls.c\
						/server/handle_user.c /server/handle_syst.c /server/handle_pwd.c \
						/server/connections.c /server/handle_pasv.c /server/handle_cwd.c \
						/server/user_right.c /server/mouv.c

SRCS_CLIENT			+= /client/main.c

SRCS_TOOLS			+= /tools/send.c /tools/error.c /tools/ascii_mode.c

SRCS = $(SRCS_SERVER) $(SRCS_CLIENT) $(SRCS_TOOLS)
SRC_SUBDIR = client server tools

###############################################################################

#  Compiler

NAME_SERVER		= server
NAME_CLIENT		= client

CC				= cc
CFLAGS			= -Wall -Wextra -Werror

ifeq ($(DEBUG), yes)
	CFLAGS		+= -D DEBUG -ggdb
endif

ifeq ($(DEV),yes)
    CFLAGS		+= -g3 -Wvla 
endif

ifeq ($(SAN),yes)
    CFLAGS		+= -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls
endif

#The Directories, Source, Includes, Objects and Libraries
INC			= -I includes
SRCS_DIR		= srcs

#Objects
# OBJS = $(addprefix $(OBJS_DIR)/,$(OBJ_NAME))
# OBJS_DIR		= objs
# OBJ = $(SRCS_NAME:.c=.o)# $(SRCS:%.c=$(OBJS_DIR)/%.o)

OBJ_NAME = $(SRCS:.c=.o)
OBJS_DIR	= objs
OBJS = $(addprefix $(OBJS_DIR),$(OBJ_NAME))
OBJS_DIRS = $(addprefix $(OBJS_DIR)/,$(SRC_SUBDIR))

OBJS_SERVER = $(addprefix $(OBJS_DIR),$(SRCS_SERVER:.c=.o))
OBJS_CLIENT = $(addprefix $(OBJS_DIR),$(SRCS_CLIENT:.c=.o))
OBJS_TOOLS = $(addprefix $(OBJS_DIR),$(SRCS_TOOLS:.c=.o))


BUILD_DIR		= $(OBJS_DIRS)

#Utils
RM				= rm -rf
MKDIR			= mkdir -p

#LIB
LIB_PATH		= libft
LIB_NAME		= libft.a
LIB				= $(LIB_PATH)/$(LIB_NAME)

COUNT = 0
TOTAL = 0
PERCENT = 0
$(eval TOTAL=$(shell echo $$(printf "%s" "$(SRCS)" | wc -w)))
###############################################################################


all: $(NAME_SERVER) $(NAME_CLIENT)

$(NAME_SERVER): $(LIB) $(OBJS)
	$(CC) -o $(NAME_SERVER) $(CFLAGS) $(OBJS_SERVER) $(OBJS_TOOLS) $(LIB) 
	@echo
	@echo "[\033[35m----------------------------------------\033[0m]"
	@echo "[\033[36m------- Compilation SERVER Done! -------\033[0m]"
	@echo "[\033[35m----------------------------------------\033[0m]"

$(NAME_CLIENT): $(LIB) $(OBJS)
	$(CC) -o $(NAME_CLIENT) $(CFLAGS) $(OBJS_CLIENT) $(OBJS_TOOLS) $(LIB)
	@echo
	@echo "[\033[35m----------------------------------------\033[0m]"
	@echo "[\033[36m------- Compilation CLIENT Done! -------\033[0m]"
	@echo "[\033[35m----------------------------------------\033[0m]"

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	$(MKDIR) $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<
	$(eval COUNT=$(shell echo $$(($(COUNT)+1))))
	$(eval PERCENT=$(shell echo $$((($(COUNT) * 100 )/$(TOTAL)))))
	@printf "$(C_B)%-8s $(C_NO)" "[$(PERCENT)%]"


$(LIB):
	make DEBUG=$(DEBUG) DEV=$(DEV) SAN=$(SAN) -C $(LIB_PATH)

miniclean:
	@echo "\033[35m$(NAME)  :\033[0m [\033[31mSuppression des .o du projet \033[0m]"
	$(RM) $(OBJS_DIR)

minifclean: miniclean
	@echo "\033[35m$(NAME)  :\033[0m [\033[31mSuppression de $(NAME_CLIENT) et $(NAME_SERVER)\033[0m]"
	$(RM) $(NAME_CLIENT) $(NAME_SERVER)

minire: minifclean all

clean:
	@echo "\033[35m$(NAME)  :\033[0m [\033[31mSuppression des .o\033[0m]"
	$(RM) $(OBJS_DIR)
	make clean -C $(LIB_PATH)

fclean: clean
	@echo "\033[35m$(NAME)  :\033[0m [\033[31mSuppression de $(NAME_CLIENT) et $(NAME_SERVER)\033[0m]"
	$(RM) $(NAME_CLIENT) $(NAME_SERVER)
	make fclean -C $(LIB_PATH)

re: fclean all
