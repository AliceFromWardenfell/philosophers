NAME		:= philo
HDRS		:= philo.h

CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror -pthread -g

SRCS_DIR	:= sources
HDRS_DIR	:= headers
vpath %.c	$(SRCS_DIR)
vpath %.h	$(HDRS_DIR)
INCLUDES	:= -I$(HDRS_DIR)

SRCS		:= main.c \
			parser.c \
			philosophers.c \
			dinner.c \
			pathologist.c \
			killer.c \
			error.c \
			utils.c \
			ft_atoi.c

OBJS_DIR	:= .objects
OBJS		:= $(SRCS:%.c=$(OBJS_DIR)/%.o)

all:
					@echo "$(BOLD)Creating/updating '$(NAME)':$(DEF)"
					@$(MAKE) --no-print-directory $(NAME)

$(NAME):			$(OBJS)
					@echo "$(BOLD)Linking files...$(DEF)"
					@$(CC) $(OBJS) $(CFLAGS) $(INCLUDES) -o $@
					@echo "$(BOLD)'$(NAME)' has been created/updated.$(DEF)"

$(OBJS_DIR)/%.o:	%.c $(HDRS) | $(OBJS_DIR)
					@echo "Assembling $<..."
					@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_DIR):
					@mkdir -p $@
					@echo "$(BOLD)Directory '$(OBJS_DIR)' has been created.$(DEF)"

clean:
					@rm -rf $(OBJS)
					@echo "$(NAME): $(BOLD)Object files have been cleaned.$(DEF)"

fclean:				clean
					@rm -rf $(NAME)
					@echo "$(BOLD)'$(NAME)' has been cleaned.$(DEF)"

re:					fclean all

.PHONY:				all clean fclean re

BOLD	:= \033[1m
DEF		:= \033[0;39m