#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 28000
#define HEIGHT 27000
#define PLAYER 'P'
#define COLLECTABLE 'C'
#define EXIT 'E'
#define TREE '1'  // Arbres sont représentés par des murs
#define GROUND '0'  // Sols

int num_collectibles = 10;  // Nombre de collectibles aléatoires

// Fonction pour générer une valeur aléatoire dans une plage donnée
int rand_range(int min, int max) {
    return min + rand() % (max - min + 1);
}

// Fonction pour initialiser la map avec des arbres et sols
void init_map(char **game_map) {
    int i, j;

    // Initialiser le générateur de nombres aléatoires
    srand(time(NULL));

    // Remplir la carte avec des murs (bordures)
    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            // Bordure de la carte, murs autour
            if (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1) {
                game_map[i][j] = TREE;  // Mur sur les bords
            }
            else if (rand_range(1, 4) == 1) {  // 1 arbre pour 4 sols
                game_map[i][j] = TREE;  // Arbre (mur) à l'intérieur
            } else {
                game_map[i][j] = GROUND;  // Sol
            }
        }
    }

    // Placer la position du joueur
    int player_x = rand_range(1, WIDTH - 2);
    int player_y = rand_range(1, HEIGHT - 2);
    game_map[player_y][player_x] = PLAYER;

    // Placer la sortie (E)
    int exit_x = rand_range(1, WIDTH - 2);
    int exit_y = rand_range(1, HEIGHT - 2);
    game_map[exit_y][exit_x] = EXIT;

    // Placer des collectibles (C)
    int placed_collectibles = 0;
    while (placed_collectibles < num_collectibles) {
        int x = rand_range(1, WIDTH - 2);
        int y = rand_range(1, HEIGHT - 2);
        
        // Placer un collectable seulement sur une case vide (sol)
        if (game_map[y][x] == GROUND) {
            game_map[y][x] = COLLECTABLE;
            placed_collectibles++;
        }
    }
}

// Fonction pour sauvegarder la map dans un fichier .ber
void save_map_to_file(char **game_map, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Erreur d'ouverture du fichier");
        return;
    }

    // Écrire la map dans le fichier
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            fputc(game_map[i][j], file);
        }
        fputc('\n', file);  // Nouvelle ligne après chaque rangée
    }

    fclose(file);
}

int main() {
    // Allocation dynamique de la mémoire pour la carte
    char **game_map = (char **)malloc(HEIGHT * sizeof(char *));
    if (!game_map) {
        perror("Erreur d'allocation mémoire pour la carte");
        return 1;
    }

    for (int i = 0; i < HEIGHT; i++) {
        game_map[i] = (char *)malloc(WIDTH * sizeof(char));
        if (!game_map[i]) {
            perror("Erreur d'allocation mémoire pour une ligne de la carte");
            return 1;
        }
    }

    // Initialiser la map
    init_map(game_map);

    // Sauvegarder la map dans un fichier .ber
    save_map_to_file(game_map, "./maps/50x1000.ber");

    printf("La map a été sauvegardée dans 'maps/'.\n");

    // Libération de la mémoire allouée
    for (int i = 0; i < HEIGHT; i++) {
        free(game_map[i]);
    }
    free(game_map);

    return 0;
}
