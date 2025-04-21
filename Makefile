CC = cc
CFLAGS = -Wall -Werror -Wextra
DEBUG_FLAGS = -g
NAME = philo

# Dossiers
SRC_DIR = srcs
OBJ_DIR = objs

# Fichiers sources
SRC = philo.c \
	utils.c \
	initialisation.c \
	instructions.c \
	free.c \

# Ajout des préfixes de dossiers
SRC := $(addprefix $(SRC_DIR)/, $(SRC))
OBJ := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

# Cible principale
all: $(OBJ_DIR) $(NAME)

# Compilation de l'exécutable
$(NAME): $(OBJ)
	@echo "Compiling libraries..."
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "Libraries compiled successfully!"

# Compilation des fichiers objets dans OBJ_DIR
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(DEBUG_FLAGS) -c $< -o $@

# Création du dossier OBJ_DIR si nécessaire
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Nettoyage des fichiers objets et du dossier OBJ_DIR
clean:
	@rm -rf $(OBJ_DIR)

# Nettoyage complet
fclean: clean
	@rm -f $(NAME)

# Rebuild complet
re: fclean all
