#include <stdlib.h>
#include <stdio.h>

int **solutions = NULL;
int solution_count = 0;

void appendSolution(int *permutation, int permutation_size) {
    int **new_solutions = malloc((solution_count + 1) * sizeof(int *));
    for (int i = 0; i < solution_count; i++) {
        new_solutions[i] = solutions[i];
    }
    new_solutions[solution_count] = malloc((permutation_size + 1) * sizeof(int));
    new_solutions[solution_count][0] = permutation_size;
    for (int i = 0; i < permutation_size; i++) {
        new_solutions[solution_count][i + 1] = permutation[i];
    }
    free(solutions);
    solutions = new_solutions;
    solution_count++;
}

int *createNewPermutation(int *permutation, int permutation_size, int new_elem) {
    int *new_perm = malloc((permutation_size + 1) * sizeof(int));
    for (int i = 0; i < permutation_size; i++) {
        new_perm[i] = permutation[i];
    }
    new_perm[permutation_size] = new_elem;
    return new_perm;
}

int permTotal(int *perm, int perm_size) {
    int res = 0;
    for (int i = 0; i < perm_size; i++) {
        res += perm[i];
    }
    return (res);
}

void recursion(int *set, int set_size, int pos, int *permutation, int permutation_size, int target) {
    if (permutation_size > 0 && permTotal(permutation, permutation_size) == target) {
        appendSolution(permutation, permutation_size);
    }
    for (int i = pos; i < set_size; i++) {
        int *new_permutation = createNewPermutation(permutation, permutation_size, set[i]);
        recursion(set, set_size, i + 1, new_permutation, permutation_size + 1, target);
        free(new_permutation);
    }
}

int main(int ac, char **av) {
    int *set;
    int target;
    int set_size;
    if(ac >= 3) {
        target = atoi(av[1]);
        char **temp = &av[2];
        int i = 0;
        while (temp[i])
            i++;
        set = malloc(sizeof(int) * i);
        set_size = i;
        for (int j = 0; temp[j]; j++) {
            set[j] = atoi(temp[j]);
        }
    }
    else {
        int temp1[10] = {5, 2, 7, 6, 1, 9, 8, 11, 15, 10};
        int *temp2 = malloc(sizeof(int) * 10);
        for (int i = 0; i < 10; i++) {
            temp2[i] = temp1[i];
        }
        set = temp2;
        set_size = 10;
        target = 12;
    }
    recursion(set, set_size, 0, NULL, 0, target);
    for (int i = 0; i < solution_count; i++) {
        for (int j = 1; j <= solutions[i][0]; j++) {
            printf("%d ", solutions[i][j]);
        }
        printf("\n");
        free(solutions[i]);
    }
    free(solutions);
    free(set);
    return 0;
}