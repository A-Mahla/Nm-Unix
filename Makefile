# **************************************************************************** #
#                                                                              #
#                                                     :::       :::     :::    #
#    Makefile                                        :+:       :+: :+: :+:     #
#                                                  +:++:+     +:+  +  +:+      #
#    By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+       #
#                                              +#+    +#+   +#+     +#+        #
#    Created: 2023/10/17 02:01:51 by amahla  #+#      #+#  #+#     #+#         #
#    Updated: 2023/11/01 01:05:10 by amahla ###       ########     ########    #
#                                                                              #
# **************************************************************************** #


NAME	= 	ft_nm
CC		:=	gcc
CFLAGS	:=	-Wall -Werror -Wextra
DFLAGS	:=	-MMD -MP
LIBDIR 	:=	libft
INC		:=	-I libft/libft/includes -I inc
LIB		:=	-L libft -lft
OUTDIR 	:=	obj
SRCDIR	:=	src
SRC		:=	$(addprefix $(SRCDIR)/,	nm.c 			\
									file_reader.c	\
									file_parser.c	\
									parse_class32.c	\
									parse_class64.c	\
									)
OBJ		:=	$(SRC:.c=.o)
DEP 	:=	$(SRC:.c=.d)
RM		:=	rm -rf


all		: $(NAME)

$(OUTDIR)/%.o	: %.c 
	$(CC) $(DFLAGS) $(CFLAGS) $(INC) -o $@ -c $<

$(NAME)	: $(OUTDIR)	$(addprefix $(OUTDIR)/, $(OBJ))
	@$(MAKE) -j -C $(LIBDIR) > /dev/null
	$(CC) $(CFLAGS) -o $@ $(addprefix $(OUTDIR)/, $(OBJ)) $(INC) $(LIB)

$(OUTDIR)	:
	@mkdir -p $(addprefix $@/, $(SRCDIR))

.PHONY	: all debug clean fclean re

debug	: CFLAGS=-g3 -Wall -Werror -Wextra
debug	: all

clean	:
	@$(MAKE) clean -C $(LIBDIR) > /dev/null
	$(RM) $(OUTDIR)

fclean	: clean
	@$(MAKE) fclean -C $(LIBDIR) > /dev/null
	$(RM) $(NAME)

re		: fclean
	@$(MAKE) re -j -C $(LIBDIR) > /dev/null
	make all

-include	$(addprefix $(OUTDIR)/, $(DEP)))
