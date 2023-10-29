
NAME	:= 	libft.a
CC		:= 	gcc
AR		:= 	ar rcs
CFLAGS	:= 	-Wall -Werror -Wextra
DFLAGS	:=	-MMD -MP
LIBSRC 	:= 	libft
INC		:= 	-I $(addprefix 	$(LIBSRC)/, includes)
OUTDIR 	:= 	obj
SRC		:= 	ft_itoa.c				\
			ft_atoi.c	 			\
			ft_calloc.c				\
			ft_bzero.c				\
			ft_putnbr_fd.c			\
			ft_putstr_fd.c			\
			ft_putendl_fd.c			\
			ft_putchar_fd.c			\
			ft_memset.c				\
			ft_memcpy.c				\
			ft_memmove.c			\
			ft_memcmp.c				\
			ft_memchr.c				\
			ft_strlen.c 			\
			ft_strchr.c				\
			ft_strnstr.c 			\
			ft_strcmp.c 			\
			ft_strncmp.c 			\
			ft_strlcpy.c			\
			ft_strcat.c 			\
			ft_strncat.c 			\
			ft_strlcat.c			\
			ft_strstr.c 			\
			ft_strdup.c				\
			ft_strrchr.c 			\
			ft_substr.c 			\
			ft_strjoin.c			\
			ft_split.c				\
			ft_strmapi.c 			\
			ft_striteri.c			\
			ft_strtrim.c 			\
			ft_isalnum.c			\
			ft_isalpha.c			\
			ft_isascii.c			\
			ft_isdigit.c			\
			ft_tolower.c 			\
			ft_toupper.c 			\
			ft_isprint.c			\
			ft_lstnew.c 			\
			ft_lstadd_front.c		\
			ft_lstadd_back.c		\
			ft_lstsize.c 			\
			ft_lstlast.c 			\
			ft_lstmap.c 			\
			ft_lstclear.c			\
			ft_lstdelone.c			\
			ft_lstiter.c 			\
			$(addprefix 	ft_printf/, 	ft_flags.c 			\
											utils_1.c 			\
											utils_2.c 			\
											utils_3.c 			\
											utils_4.c 			\
											ft_print_ptr_pct.c	\
											ft_print_str_char.c \
											ft_print_hex.c 		\
											ft_print_uint.c	 	\
											ft_print_int.c  	\
											ft_dprintf.c	 	\
											ft_printf.c	 		) \
			$(addprefix 	ft_getline/, 	ft_getline.c 	\
											ft_getline_utils1.c 	\
											ft_getline_utils2.c 	)
OBJ		:= $(SRC:.c=.o)
RM		:= rm -rf

all		: $(NAME)

$(OUTDIR)/%.o	: $(LIBSRC)/%.c 
	$(CC) $(DFLAGS) $(CFLAGS) $(INC) -o $@ -c $<

$(NAME) : 	$(OUTDIR) $(addprefix $(OUTDIR)/, $(OBJ))
	$(AR) $@ $(addprefix $(OUTDIR)/, $(OBJ))

$(OUTDIR)	:
	@mkdir -p $(addprefix $@/, ft_printf)
	@mkdir -p $(addprefix $@/, ft_getline)

.PHONY	: all clean fclean re

clean	:
	$(RM) $(OUTDIR)

fclean	: clean
	$(RM) $(NAME)

re		: fclean
	make all

-include	$(addprefix $(OUTDIR)/,$(SRC:.c=.d)))
