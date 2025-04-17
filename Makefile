.PHONY : all clean fclean re bonus norminette lmlx

NAME = so_long

# ╭━━━━━━━━━━━━══════════╕出 ❖ BASICS VARIABLES ❖ 力╒═══════════━━━━━━━━━━━━╮ #

CC				:=	cc

CFLAGS			:= -Wall -Wextra -Werror -g3

RM				:=	rm	-rf

SHOW_MSG_CLEAN	=	true

MAKEFLAGS		+=	--no-print-directory

GREY			:=	\033[1;38;5;235m
BROWN			:=	\033[1;38;5;137m
GREEN			:=	\033[38;2;130;255;180m
WHITE			:=	\033[1;37m

RECOMPILED := $(shell [ -f $(NAME) ] && echo 1 || echo 0)

# ╰━━━━━━━━━━━━━━━━════════════════╛出 ❖ 力╘════════════════━━━━━━━━━━━━━━━━╯ #

# ╭━━━━━━━━━━━━══════════╕出 ❖ FILE TREE ❖ 力╒═══════════━━━━━━━━━━━━╮ #

# directories
D_SRC	=	src/
D_INC	=	inc/
D_OBJ	=	.obj/
D_MLX	=	.minilibx/
D_LIB	=	librairies/
D_MAN	=	mandatory_srcs/
D_PAR	=	$(D_SRC)parsing/
D_PRI	=	$(D_SRC)printers/
D_KEY	=	$(D_SRC)input_handler/
D_IMG	=	$(D_SRC)display_handler/

D_SRCS	= $(D_SRC) $(D_PRI) $(D_PAR) $(D_IMG) $(D_KEY)

# file lists
LST_MAN		=	m_map.c				\
				m_bfs.c				\
				m_main.c			\
				m_utils.c			\
				m_optis.c			\
				m_parsing.c			\
				m_printers.c		\
				m_load_img.c		\
				m_display_img.c		\
				m_input_detector.c	

LST_SRC		=	map.c				\
				fix.c				\
				main.c				\
				utils.c				\
				optis.c				\
				animation.c			\
				monsters_handler.c

LST_PRI		=	others.c			\
				err_printers.c		\
				map_printers.c		\
				print_on_window.c	

LST_PAR		=	bfs.c				\
				parsing.c		

LST_IMG		=	load_img.c			\
				display_img.c		

LST_KEY		=	actions.c			\
				input_detector.c	

LST_MINC	=	mandatory_so_long.h

LST_INC		=	utils.h				\
				bonus.h				\
				parsing.h			\
				$(NAME).h			\
				printers.h			\
				ft_printf.h			

LST_SRCS	=	$(LST_SRC) $(LST_PRI) $(LST_PAR) $(LST_IMG) $(LST_KEY)

MINC		=	$(addprefix $(D_MAN), $(LST_MINC))
INC			=	$(addprefix $(D_INC), $(LST_INC))

MOBJ		= $(addprefix $(D_OBJ), $(patsubst $(D_MAN)%.c, %.o, $(addprefix $(D_MAN), $(LST_MAN))))
OBJ			= $(addprefix $(D_OBJ), $(patsubst %.c, %.o, $(LST_SRCS)))

# ╭━━━━━━━━━━━━══════════╕出 ❖ RULES ❖ 力╒═══════════━━━━━━━━━━━━╮ #

all:	$(NAME)

$(D_OBJ):
	@mkdir -p $@

$(NAME):	$(MOBJ) $(MINC) lmlx
	@$(CC) $(CFLAGS) $(MOBJ) -I$(D_MAN) -L$(D_LIB) -lmlx -lXext -lX11 -lftprintf -lgnl -o $@
	@echo "\e[0;32mProgramme créé avec succès ! 🧬\e[0m"

bonus:	$(D_OBJ).bonus

$(D_OBJ).bonus:	$(OBJ) $(INC) lmlx | $(D_OBJ) Makefile
	@$(CC) $(CFLAGS) $(OBJ) -I$(D_INC) -L$(D_LIB) -lmlx -lXext -lX11 -lftprintf -lgnl -o $(NAME)
	@$(MAKE) signature
	@touch $(D_OBJ).bonus

$(D_OBJ)%.o:	$(D_MAN)%.c $(MINC) $(D_MLX)mlx.h $(D_MLX)mlx_int.h | $(D_OBJ) Makefile
	$(CC) $(CFLAGS) -I$(D_MAN) -I$(D_MLX) -c $< -o $@

vpath %.c $(D_SRCS)

$(D_OBJ)%.o:	%.c $(INC) $(D_MLX)mlx.h $(D_MLX)mlx_int.h | $(D_OBJ) Makefile
	$(CC) $(CFLAGS) -I$(D_INC) -I$(D_MLX) -c $< -o $@

lmlx:	$(D_MLX)
	@$(MAKE) -s -w -C $(D_MLX) 2>/dev/null
	@mv $(D_MLX)libmlx.a $(D_LIB)libmlx.a
	@echo "\e[0;36mArchive Minilibx créée avec succès ! 🌅\e[0m"

clean:
ifeq ($(SHOW_MSG_CLEAN), true)
	@echo "\e[0;36mJ'ai enlevé tous les objets relatifs à $(NAME) 🧹\e[0m"
endif
	@$(MAKE) -s -w -C $(D_MLX) clean
	@$(RM) $(D_OBJ)

fclean:
	@$(MAKE) -s -w -C $(D_MLX) clean
	@$(MAKE) -s SHOW_MSG_CLEAN=false clean
	@$(RM) $(NAME) .bonus $(D_LIB)libmlx.a
	@echo "\e[0;34mExecutable de $(NAME) nettoyé 🧼\e[0m"

re:
	@$(MAKE) fclean
	@$(MAKE) all
	@echo "\e[0;32mProgramme $(NAME) recréé avec succès ! 🫡\e[0m"

norminette:
	norminette $(D_SRC) $(D_INC) $(D_MAN)

MAP := $(word 2, $(MAKECMDGOALS))

%:
	@:

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./so_long maps/$(MAP)

signature:
	@echo "$(GREY) ⠀⠀⠀⠀⠀⠀⠀⣀⣀"
	@echo "⠀⠀⠀⠀⠀⠀⣰⣿⣿⣿⣿⣦$(WHITE)⣀⣀⣀                                                                  $(BROWN)_$(WHITE)"
	@echo "⠀⠀$(GREEN)╭───$(GREY)⢿⣿⠟⠋⠉$(WHITE)⠀⠀⠀⠀⠉⠑⠢⣄$(GREEN)━━━━━━━━━━━┉══════════╕$(WHITE) 🫧🍁 ❖ ケイン ❖ 🧸🎀 $(GREEN)╒══════════┉━━━━━$(BROWN)\\\`*-.$(GREEN)━━━━━━╾────────╮"
	@echo "⠀⠀$(GREEN)│ ⠀$(WHITE)⢠⠞⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀$(GREY)⠙⢿⣿⣿⣦⡀$(WHITE)                                                         $(BROWN))  _\`-.$(GREEN)            │"
	@echo "⠀$(GREY)⣀$(GREEN)│$(WHITE) ⢀⡏$(GREY)⠀⢀⣴⣶⣶⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⣿⣿⠇$(WHITE)                                                        $(BROWN).  : \`. .$(GREEN)           │"
	@echo "$(GREY)⣾⣿⣿⣦$(WHITE)⣼⡀⠀$(GREY)⢺⣿⣿⡿⠃⠀⠀⠀⠀⣠⣤⣄⠀⠀⠈⡿⠋ $(WHITE)                                                        $(BROWN): _   '  \$(GREEN)           │"
	@echo "$(GREY)⢿⣿⣿⣿⣿⣇⠀⠤⠌⠁⠀⡀⢲⡶⠄⢸⣏⣿⣿$(WHITE)⠀⠀⠀⡇                                                          $(BROWN); $(WHITE)*$(BROWN)\` _.   \`*-._$(GREEN)     │"
	@echo "$(GREY)⠈⢿⣿⣿⣿⣿⣷⣄⡀⠀⠀⠈⠉⠓⠂⠀⠙⠛⠛$(WHITE)⠠⠀⡸⠁                                                          $(BROWN)\`-.-'          \`-.$(GREEN)  │"
	@echo "$(GREY)⠀⠀⠻⣿⣿⣿⣿⣿⣿⣷⣦⣄⣀$(WHITE)⠀⠀⠀⠀⠑⠀⣠⠞⠁⠀                                                            $(BROWN);       \`       \`.$(GREEN)│"
	@echo "⠀⠀$(GREEN)│$(WHITE)⢸⡏$(GREY)⠉⠛⠛⠛⠿⠿⣿⣿⣿⣿⣿⣿⣿⣿⡄$(WHITE)⠀⠀⠀      🌸 SO_LONG EXECUTABLE CREATED SUCCESSFULLY 🎐         $(BROWN):.       .        \ $(GREEN)"
	@echo "⠀⠀$(GREEN)│$(WHITE)⠸⠀⠀⠀⠀⠀⠀⠀⠀$(GREY)⠈⠉⠛⢿⣿⣿⣿⣿⡄$(WHITE)⠀⠀                                                            $(BROWN). \  .   :   .-'   .$(GREEN)"
	@echo "⠀⠀$(GREEN)│$(WHITE)⢷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀$(GREY)⠈⢻⣿⣿⣿⣿⡀$(WHITE)⠀                                                            $(BROWN)'  \`+.;  ;  '      :$(GREEN)"
	@echo "⠀⠀$(GREEN)│$(WHITE)⢸⣆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀$(GREY)⣿⣿⣿⣿⡇$(WHITE)⠀                                                            $(BROWN):  '  |    ;       ;-.$(GREEN)"
	@echo "⠀⠀$(GREEN)│$(GREY)⢸⣿⣦⣀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣼⡟⠻⠿⠟⠀$(WHITE)⠀                                                            $(BROWN); '   : :\`-:     _.\`* ;$(GREEN)"
	@echo "⠀⠀$(GREEN)│$(GREY)⠀⣿⣿⣿⣿⣶$(WHITE)⠶⠤⠤$(GREY)⢤⣶⣾⣿⣿⡇$(WHITE)                                                                $(BROWN).*' /  .*' ; .*\`- +'\`*'$(GREEN)"
	@echo "⠀⠀$(GREEN)│$(GREY)⠀⠹⣿⣿⣿⠏⠀⠀⠀$(GREY)⠈⢿⣿⣿⡿⠁$(WHITE)                                                                $(BROWN)\`*-*   \`*-*  \`*-*'$(GREEN) │"
	@echo "⠀⠀$(GREEN)╰───────────────╼━━━━━━━━┉══════════════════╛$(WHITE) 🎍 ❖ ⛲ $(GREEN)╘══════════════════┉━━━━━━━━━╾───────────────╯"