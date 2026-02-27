#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int minDistance(const int *dist, const int *visited, int n) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < n; v++)
        if (!visited[v] && dist[v] <= min)
            min = dist[v], min_index = v;
    return min_index;
}

void dijkstra(int n, int **graph, int src, int *dist, int *visited) {
    dist[src] = 0;
    for (int count = 0; count < n - 1; count++) {
        int u = minDistance(dist, visited, n - 1);
        visited[u] = 1;
        for (int v = 0; v < n; v++)
            if (!visited[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }
}

int main() {
    FILE *input, *output;
    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");
    if (!input || !output)
        return 1;
    int charge, number_of_rooms, transitions;
    fscanf(input, "%d%d%d", &charge, &number_of_rooms, &transitions);

    int *value = (int *) calloc(number_of_rooms, sizeof(int));
    if (!value)
        exit(1);
    int **tomb = (int **) calloc(number_of_rooms, sizeof(int *));
    if (!tomb)
        exit(1);
    for (int i = 0; i < number_of_rooms; i++) {
        tomb[i] = (int *) calloc(number_of_rooms, sizeof(int));
        if (!tomb[i])
            exit(1);
    }
    for (int i = 0; i < transitions; i++) {
        int from, to, damage;
        fscanf(input, "%d%d%d", &from, &to, &damage);
        tomb[from][to] = damage;
    }
    for (int i = 0; i < number_of_rooms; i++)
        fscanf(input, "%d", &value[i]);
    fclose(input);
    int *dist = (int *)malloc(number_of_rooms * sizeof(int));
    if (!dist)
        exit(1);
    int *visited = (int *)calloc(number_of_rooms, sizeof(int));
    if (!visited)
        exit(1);
    for (int i = 0; i < number_of_rooms; i++)
        dist[i] = INT_MAX;
    dijkstra(number_of_rooms, tomb, 0, dist, visited);
    int treasure = 0;
    for (int i = 0; i < number_of_rooms; i++) {
        if (dist[i] <= charge && value[i] > treasure)
            treasure = value[i];
    }
    free(value);
    free(dist);
    free(visited);
    for (int i = 0; i < number_of_rooms; i++)
        free(tomb[i]);
    free(tomb);
    fprintf(output, "%d", treasure);
    fclose(output);
    return 0;
}
