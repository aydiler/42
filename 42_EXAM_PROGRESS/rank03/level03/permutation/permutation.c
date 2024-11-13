#include <stdlib.h> // Pour malloc, free
#include <string.h> // Pour strlen
#include <stdio.h>  // Pour puts

void swap(char *a, char *b)
{
    char tmp = *a;
    *a = *b;
    *b = tmp;
}

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

void reverse(char *s, int start, int end)
{
    while(start < end)
    {
        swap(&s[start], &s[end]);
        start++;
        end--;
    }
}

int next_permutation(char *s)
{
    int len = strlen(s);
    int i = len - 2;

    // Step 1: Find the first character that is smaller than the next one
    while(i >= 0 && s[i] >= s[i+1])
        i--;

    if(i < 0)
        return 0; // Last permutation reached

    // Step 2: Find the smallest character on right side that's larger than s[i]
    int j = len - 1;
    while(s[j] <= s[i])
        j--;

    // Step 3: Swap these characters
    swap(&s[i], &s[j]);

    // Step 4: Reverse the sequence after position i
    reverse(s, i+1, len-1);

    return 1; // Next permutation generated
}

int main(int argc, char **argv)
{
    if(argc != 2)
        return 1;

    size_t len = strlen(argv[1]);
    if(len == 0)
        return 0;

    char *buffer = argv[1];

    sort_string(buffer);
    puts(buffer); 

    while(next_permutation(buffer))
        puts(buffer);

    return 0;
}
