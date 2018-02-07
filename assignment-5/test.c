#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define maxLevel 5

int levelGen() {
    double r = (double)rand() / RAND_MAX;
    int level = (int)log2(1.0/r) + 1;
    return fmin(level, maxLevel);
}

int levelGen2() {
    int level = 1;
    while (rand() % 2 == 0 && level < maxLevel) {
        level++;
    }
    return level;
}

int main() {
    srand(time(NULL));
    printf("levelGen\n");
    int i;
    double avg;
    for (i = 0; i < 100000; i++) {
        avg += levelGen();
    }
    printf("average 1: %f\n", avg/1000.0);
    printf("levelGen2\n");
    avg = 0;
    for (i = 0; i < 100000; i++) {
        avg += levelGen2();
    }
    printf("average 2: %f\n", avg/1000.0);
    printf("\n");
}
