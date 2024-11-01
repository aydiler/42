#include <stdlib.h> // Pour malloc, free
#include <string.h> // Pour strlen
#include <stdio.h>  // Pour puts

/* Fonction pour échanger deux caractères */
void swap(char *a, char *b)
{
    char tmp = *a;
    *a = *b;
    *b = tmp;
}

/* Fonction pour trier la chaîne par ordre alphabétique (Bubble Sort) */
void sort_string(char *s)
{
    int len = strlen(s);
    for(int i = 0; i < len - 1; i++)
    {
        for(int j = 0; j < len - i - 1; j++)
        {
            if(s[j] > s[j+1])
                swap(&s[j], &s[j+1]);
        }
    }
}

/* Fonction pour inverser une partie de la chaîne */
void reverse(char *s, int start, int end)
{
    while(start < end)
    {
        swap(&s[start], &s[end]);
        start++;
        end--;
    }
}

/* Fonction pour générer la prochaine permutation lexicographique */
int next_permutation(char *s)
{
    int len = strlen(s);
    int i = len - 2;

    // Trouver le premier caractère qui est plus petit que celui qui le suit
    while(i >= 0 && s[i] >= s[i+1])
        i--;

    if(i < 0)
        return 0; // Dernière permutation atteinte

    // Trouver le premier caractère à droite de s[i] qui est plus grand que s[i]
    int j = len - 1;
    while(s[j] <= s[i])
        j--;

    // Échanger s[i] et s[j]
    swap(&s[i], &s[j]);

    // Inverser la séquence après la position i
    reverse(s, i+1, len-1);

    return 1; // Permutation suivante générée
}

int main(int argc, char **argv)
{
    if(argc != 2)
        return 1;

    size_t len = strlen(argv[1]);
    if(len == 0)
        return 0;

    char *buffer = argv[1]; // Chaîne à permuter

    sort_string(buffer); // Trie la chaîne pour commencer par la première permutation lexicographique
    puts(buffer);        // Affiche la première permutation

    // Génère et affiche toutes les permutations suivantes
    while(next_permutation(buffer))
        puts(buffer);

    return 0;
}
