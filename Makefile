# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acarle-m <acarle-m@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/21 18:00:59 by cben-bar          #+#    #+#              #
#    Updated: 2022/09/22 01:51:51 by cben-bar         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

SRCSDIR		=	./srcs/

SRCS 		=	$(SRCSDIR)parse_to_exec/struct.c
SRCS		+=	$(SRCSDIR)parsing/check_consec_pipe.c	
SRCS		+=	$(SRCSDIR)parsing/check_empty_line.c	
SRCS		+=	$(SRCSDIR)parsing/check_first_pipe.c	
SRCS		+=	$(SRCSDIR)parsing/check_last_chev.c		
SRCS		+=	$(SRCSDIR)parsing/check_last_pipe.c		
SRCS		+=	$(SRCSDIR)parsing/check_multi_chev.c	
SRCS		+=	$(SRCSDIR)parsing/check_multi_node_chev.c
SRCS		+=	$(SRCSDIR)parsing/check_no_file_name.c
SRCS		+=	$(SRCSDIR)parsing/check_quote.c
SRCS		+=	$(SRCSDIR)parsing/cleaner.c
SRCS		+=	$(SRCSDIR)parsing/cut_redir.c
SRCS		+=	$(SRCSDIR)parsing/dispatch_var.c
SRCS		+=	$(SRCSDIR)parsing/dollar.c
SRCS		+=	$(SRCSDIR)parsing/dollar2.c
SRCS		+=	$(SRCSDIR)parsing/dollar3.c
SRCS		+=	$(SRCSDIR)parsing/fill_var.c
SRCS		+=	$(SRCSDIR)parsing/first_check.c
SRCS		+=	$(SRCSDIR)parsing/flaggeur_file_name.c
SRCS		+=	$(SRCSDIR)parsing/flaggeur_redir.c
SRCS		+=	$(SRCSDIR)parsing/ident_cmd.c
SRCS		+=	$(SRCSDIR)parsing/parse.c	
SRCS		+=	$(SRCSDIR)parsing/parsing.c	
SRCS		+=	$(SRCSDIR)parsing/printer_error.c
SRCS		+=	$(SRCSDIR)parsing/quote_supp.c
SRCS		+=	$(SRCSDIR)parsing/re_flaggeur.c
SRCS		+=	$(SRCSDIR)parsing/set_pars.c
SRCS		+=	$(SRCSDIR)parsing/set_var.c
SRCS		+=	$(SRCSDIR)parsing/split_block.c
SRCS		+=	$(SRCSDIR)parsing/supp_empty_node.c
SRCS		+=	$(SRCSDIR)parsing/tote.c
SRCS		+=	$(SRCSDIR)parsing/universal_flaggeur.c
SRCS		+=	$(SRCSDIR)exec/exec.c
SRCS		+=	$(SRCSDIR)exec/execcmd.c
SRCS		+=	$(SRCSDIR)exec/exit_status.c
SRCS		+=	$(SRCSDIR)exec/redirection.c
SRCS		+=	$(SRCSDIR)utils/add_back.c
SRCS		+=	$(SRCSDIR)utils/exec_add_back.c
SRCS		+=	$(SRCSDIR)utils/exec_last.c
SRCS		+=	$(SRCSDIR)utils/exec_split.c
SRCS		+=	$(SRCSDIR)utils/ft_itoa.c
SRCS		+=	$(SRCSDIR)utils/ft_split_it.c
SRCS		+=	$(SRCSDIR)utils/ft_strcmp.c
SRCS		+=	$(SRCSDIR)utils/ft_strcpy.c
SRCS		+=	$(SRCSDIR)utils/ft_strdup.c
SRCS		+=	$(SRCSDIR)utils/ft_strjoin.c
SRCS		+=	$(SRCSDIR)utils/ft_strlen.c
SRCS		+=	$(SRCSDIR)utils/ft_utils.c
SRCS		+=	$(SRCSDIR)utils/init.c
SRCS		+=	$(SRCSDIR)utils/init_exec.c
SRCS		+=	$(SRCSDIR)utils/lst_last.c
SRCS		+=	$(SRCSDIR)utils/lst_size.c
SRCS		+=	$(SRCSDIR)utils/signal.c
SRCS		+=	$(SRCSDIR)utils/utils2.c
SRCS		+=	$(SRCSDIR)utils/utils.c
SRCS		+=	$(SRCSDIR)utils/free_memory.c
SRCS		+=	$(SRCSDIR)utils/get_path.c
SRCS		+=	$(SRCSDIR)utils/ft_atoi.c
SRCS		+=	$(SRCSDIR)utils/shell.c
SRCS		+=	$(SRCSDIR)utils/tcattrtermios.c
SRCS		+=	$(SRCSDIR)minishell_main.c
SRCS		+=	$(SRCSDIR)builtin/cd.c
SRCS		+=	$(SRCSDIR)builtin/echo.c
SRCS		+=	$(SRCSDIR)builtin/env.c
SRCS		+=	$(SRCSDIR)builtin/envp_utils.c
SRCS		+=	$(SRCSDIR)builtin/exit.c
SRCS		+=	$(SRCSDIR)builtin/export.c
SRCS		+=	$(SRCSDIR)builtin/pwd.c
SRCS		+=	$(SRCSDIR)builtin/export_utils.c
SRCS		+=	$(SRCSDIR)builtin/unset.c
SRCS		+=	$(SRCSDIR)parse_to_exec/here_doc.c
SRCS		+=	$(SRCSDIR)parse_to_exec/redirection2.c
SRCS		+=	$(SRCSDIR)parse_to_exec/redir_lst.c
SRCS		+=	$(SRCSDIR)exec/fdrestore.c
SRCS		+=	$(SRCSDIR)builtin/sort_ascii.c

OBJS 		=	${SRCS:.c=.o}

HEADER		=	-I includes -I ~/.brew/opt/readline/include #-I includes -I ${HOME}/libreadline/include

CC 			=	gcc

CFLAGS 		=	-Wall -Wextra -Werror

LIBS		=	-L ~/.brew/opt/readline/lib -lreadline #-L ${HOME}/libreadline/lib -lreadline

OBJSDIR		=	./objs/

DEPS		=	#./includes/minishell.h

OBJS		=	$(SRCS:$(SRCSDIR)%.c=$(OBJSDIR)%.o)

all		:	${NAME}

odcam		:
			${MAKE} ${OBJS} -j
			${MAKE} ${NAME}

${NAME}		:	${OBJS} ${DEPS} Makefile
			$(CC) $(OBJS) ${CFLAGS} $(HEADER) -o $(NAME) $(LIBS)

$(OBJS)		:	$(OBJSDIR)%.o	:	$(SRCSDIR)%.c ${DEPS} Makefile
			@mkdir -p $(OBJSDIR)
			@mkdir -p $(OBJSDIR)builtin
			@mkdir -p $(OBJSDIR)exec
			@mkdir -p $(OBJSDIR)parse_to_exec
			@mkdir -p $(OBJSDIR)parsing
			@mkdir -p $(OBJSDIR)utils
			${CC} ${CFLAGS} ${HEADER} -c $< -o $@

clean		:
			@rm -rf ${OBJSDIR}

makeclean	:	${NAME} clean

fclean		: 	clean
			@rm -rf ${NAME}

re			:	fclean all

.PHONY		:	all clean fclean re
