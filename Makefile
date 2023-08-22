
## BUILD DETAILS

##CHANGE COMPILER AND MAKE

NAME 		=		fdf

CC 			= 		cc -g
## -Wall Wextra Werror
FLAGS 		= 		-Wall -Werror -Wextra
ADD_LIB 	= 		-L./$(LIB_PATH) -lft
MLX_LIB		=		-Lmlx_linux -lmlx_Linux -L/usr/lib -lmlx -lXext -lX11 -lm -lz
RM 			=		rm
MAKE		=		make

## FOLDER PATH ##
INC_PATH	=		incs
INC_MLX 	=		-I/usr/include -Imlx_linux
SRC_PATH	=		srcs
OBJ_PATH	=		objs

LIB_PATH	=		libft
LIB_INC_P	=		incs

## SOURCE LIBRARIES
LIBFT		=		libft.a

## SOURCE FILES ##
FILES		=		fdf_main.c							\
					fdf_mlx.c							\
					fdf_map_parsing.c					\
					fdf_setup.c							\
					fdf_pixel_utils.c					\
					fdf_add_to_libft.c					\
					fdf_xiaolinwu.c						\
					fdf_xiaolinwu_utils.c				\
					fdf_lb_clipping.c					\
					fdf_lb_utils.c						\
					fdf_key_manager.c					\
					fdf_key_manager2.c					\
					fdf_print_utils.c					\
					fdf_draw.c							\
					fdf_error_msg.c

SRCS		:= 		$(addprefix $(SRC_PATH)/, $(FILES))

OBJS		=		$(patsubst $(SRC_PATH)/%.c,$(OBJ_PATH)/%.o,$(SRCS))

INCS		= 		-I$(INC_PATH) $(INC_MLX) -I$(LIB_PATH)/$(LIB_INC_P)

all: $(NAME)

$(NAME): message $(LIBFT) $(OBJS)
	@$(CC) $(FLAGS) $(OBJS) $(INCS) -o $(NAME) $(ADD_LIB) $(LIB_PATH)/$(LIBFT) $(MLX_LIB)
	@echo Program $(NAME) ready!!

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(LIBFT):
	@echo Preparing Libft....
	@$(MAKE) -C $(LIB_PATH)

message:
	@echo Building program....

clean:
	@echo Removing object files.....
	@if [ -d "$(OBJ_PATH)" ]; then \
        rm -rf $(OBJ_PATH); \
    fi
	@make clean -C $(LIB_PATH)
	@echo Objects successfully deleted!

fclean: clean
	@echo Deleting libft.a...
	@if [ -n "$(wildcard  $(NAME))" ]; then \
        $(RM) $(NAME); \
    fi
	@if [ -n "$(wildcard  $(LIB_PATH)/$(LIBFT))" ]; then \
        $(RM) $(LIB_PATH)/$(LIBFT); \
    fi
	@echo Done!!

re: fclean all

.PHONY: clean fclean re message bonus

##COLOUR

CLR_RMV		:= \033[0m
RED		    := \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m
