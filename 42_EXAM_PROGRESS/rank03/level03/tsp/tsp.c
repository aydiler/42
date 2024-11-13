#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#define MAX_CITIES 11

typedef struct {
    float x;
    float y;
} Point;

// Parse integer from string
int parse_int(char **str) {
    int result = 0;
    
    // Skip whitespace
    while (**str == ' ' || **str == '\t')
        (*str)++;
    
    while (**str >= '0' && **str <= '9') {
        result = result * 10 + (**str - '0');
        (*str)++;
    }
    return result;
}

// Parse a line containing two integers separated by comma
int parse_coordinates(char *line, float *x, float *y) {
    char *ptr = line;
    
    *x = (float)parse_int(&ptr);
    
    // Skip whitespace and comma
    while (*ptr == ' ' || *ptr == '\t')
        ptr++;
    if (*ptr != ',')
        return 0;
    ptr++;
    while (*ptr == ' ' || *ptr == '\t')
        ptr++;
    
    *y = (float)parse_int(&ptr);
    return 1;
}

float distance(Point p1, Point p2) {
    float dx = p2.x - p1.x;
    float dy = p2.y - p1.y;
    return sqrtf(dx * dx + dy * dy);
}

float find_shortest_path(Point *cities, int n, int current, int visited, float current_dist, float *min_dist, int start) {
    if (visited == ((1 << n) - 1)) {
        float total_dist = current_dist + distance(cities[current], cities[start]);
        if (total_dist < *min_dist)
            *min_dist = total_dist;
        return total_dist;
    }

    float min_path = INFINITY;
    for (int i = 0; i < n; i++) {
        if (!(visited & (1 << i))) {
            float new_dist = current_dist + distance(cities[current], cities[i]);
            if (new_dist < *min_dist) {
                float path_dist = find_shortest_path(cities, n, i, visited | (1 << i), 
                                                   new_dist, min_dist, start);
                if (path_dist < min_path)
                    min_path = path_dist;
            }
        }
    }
    return min_path;
}

int main() {
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    
    Point *cities = malloc(MAX_CITIES * sizeof(Point));
    if (!cities) {
        write(2, "Memory allocation failed\n", 23);
        return 1;
    }

    int n = 0;
    float x, y;
    
    while (n < MAX_CITIES && (read = getline(&line, &len, stdin)) != -1) {
        // Remove newline if present
        if (read > 0 && line[read-1] == '\n')
            line[read-1] = '\0';
        
        if (parse_coordinates(line, &x, &y)) {
            cities[n].x = x;
            cities[n].y = y;
            n++;
        }
    }

    if (line) {
        free(line);
    }

    if (n == 0) {
        printf("0.00\n");
        free(cities);
        return 0;
    }

    float min_dist = INFINITY;
    float overall_min = INFINITY;
    
    for (int start = 0; start < n; start++) {
        min_dist = INFINITY;
        float dist = find_shortest_path(cities, n, start, 1 << start, 0, &min_dist, start);
        if (dist < overall_min)
            overall_min = dist;
    }

    printf("%.2f\n", overall_min);
    
    free(cities);
    return 0;
}