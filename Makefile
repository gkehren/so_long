# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/21 15:21:14 by gkehren           #+#    #+#              #
#    Updated: 2022/07/20 17:48:04 by gkehren          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILES:=	so_long parsing_map get_next_line get_next_line_utils check_map so_long_utils render hooks moves ft_itoa
FILES_BONUS:=

NAME:= so_long
BONUS:= so_long_bonus

# ------------------
CC:=clang
SRCPATH:=srcs/
BONUSPATH:=srcs/
HDRPATH:=include/
CCHPATH:=obj/
CCHPATH_BONUS:=obj/
IFLAGS:=-I ${HDRPATH}
CFLAGS:=-Wall -Wextra -Werror -g3 ${IFLAGS} -I minilibx/
# ==================

# ----- Colors -----
BLACK:="\033[1;30m"
RED:="\033[1;31m"
GREEN:="\033[1;32m"
CYAN:="\033[1;35m"
PURPLE:="\033[1;36m"
WHITE:="\033[1;37m"
EOC:="\033[0;0m"
# ==================

# ------ Auto ------
SRC:=$(addprefix $(SRCPATH),$(addsuffix .c,$(FILES)))
OBJ:=$(addprefix $(CCHPATH),$(addsuffix .o,$(FILES)))
# ==================
CCHF:=.cache_exists

all: ${NAME}

${NAME}: ${OBJ}
	@echo ${CYAN} " - Compiling $@" $(RED)
	make -C minilibx
	@${CC} ${CFLAGS} ${SRC} -Lmlx_linux -lmlx_Linux -L minilibx/ -Imlx_linux -lXext -lX11 -lm -lz -o ${NAME}
	@echo $(GREEN) " - OK" $(EOC)

${CCHPATH}%.o: ${SRCPATH}%.c | ${CCHF}
	@echo ${PURPLE} " - Compiling $< into $@" ${EOC}
	@${CC} ${CFLAGS} -Imlx_linux -O3 -c $< -o $@

${BONUS}:
	@echo ${CYAN} " - Compiling $@" $(RED)
	make -C minilibx
	@${CC} ${CFLAGS} ${SRC} -Lmlx_linux -lmlx_Linux -L minilibx/ -Imlx_linux -lXext -lX11 -lm -lz -o ${BONUS}
	@echo $(GREEN) " - OK" $(EOC)

%.c:
	@echo ${RED}"Missing file : $@" ${EOC}

$(CCHF):
	@mkdir $(CCHPATH)
	@touch $(CCHF)

bonus: ${BONUS}

clean:
	@make -C minilibx clean
	@rm -rf ${CCHPATH}
	@rm -f ${CCHF}

fclean:	clean
	@make -C minilibx clean
	@rm -f ${NAME}
	@rm -f ${BONUS}
	@rm -rf ${NAME}.dSYM/
	@rm -rf ${BONUS}.dSYM/

re:	fclean
	@${MAKE} all

.PHONY:	all bonus clean fclean re
