#include <stdio.h>
#include <stdlib.h>

void find_subsets(int target, int *numbers, int size, int *current, int curr_size, int start) {
    int sum = 0;
    for (int i = 0; i < curr_size; i++) {
        sum += numbers[current[i]];
    }
    
    if (sum == target && curr_size > 0) {
        for (int i = 0; i < curr_size; i++) {
            fprintf(stdout, "%d", numbers[current[i]]);
            if (i < curr_size - 1) {
                fprintf(stdout, " ");
            }
        }
        fprintf(stdout, "$\n");
    }
    
    for (int i = start; i < size; i++) {
        current[curr_size] = i;
        find_subsets(target, numbers, size, current, curr_size + 1, i + 1);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 0;
    }

    int target = atoi(argv[1]);
    int size = argc - 2;
    
    if (size == 0) {
        return 0;
    }

    int *numbers = malloc(size * sizeof(int));
    if (!numbers) {
        return 1;
    }

    for (int i = 0; i < size; i++) {
        numbers[i] = atoi(argv[i + 2]);
    }

    int *current = malloc(size * sizeof(int));
    if (!current) {
        free(numbers);
        return 1;
    }

    find_subsets(target, numbers, size, current, 0, 0);

    free(numbers);
    free(current);
    return 0;
}