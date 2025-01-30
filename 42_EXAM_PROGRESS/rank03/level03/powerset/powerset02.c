//#include "powerset.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
void    find_subsets(int target, int *numbers, int size, int *pos, int sub_size, int start, int sum)
{
    int i = 0;
    if (sum == target && sub_size > 0)
    {
        while (i < sub_size)
        {
            printf("%d", numbers[pos[i]]);
            if (i < sub_size - 1)
                printf(" ");
            else
                printf("\n");
            i++;
        }
    }
    i = start;
    while (i < size)
    {
        pos[sub_size] = i;
        find_subsets(target, numbers, size, pos, sub_size + 1, i + 1, sum + numbers[i]);
        i++;
    }
}
int main(int argc, char **argv)
{
    if (argc < 3)
        return (0);
    int target = atoi(argv[1]);
    int size = argc - 2;
    int numbers[size];
    int pos[size];
    int i = 0;
    while (i < size)
    {
        numbers[i] = atoi(argv[i + 2]);
        i++;
    }
    find_subsets(target, numbers, size, pos, 0, 0, 0);
    return (0);
}