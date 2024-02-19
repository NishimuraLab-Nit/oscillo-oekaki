#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pigpio.h>
#include <unistd.h>

int axis_x[8] = {21, 20, 16, 12, 1, 7, 8, 24};
int axis_y[8] = {26, 19, 13, 6, 5, 11, 9, 10};

void ochiX(int x) {
    for (int i = 0; i <= 7; i++) {
        gpioWrite(axis_x[i], (x & 1U));
        x = x >> 1;
    }
}

void ochiY(int y) {
    for (int i = 0; i <= 7; i++) {
        gpioWrite(axis_y[i], (y & 1U));
        y = y >> 1;
    }
}

void Paint() {
    FILE *fp;
    char fname[] = "";

    printf("ファイル名:");
    scanf("%s", fname);

    char path[100];
    snprintf(path, sizeof path, "data/%s", fname);
    printf("%s \n", path);

    fp = fopen(path, "r");
    if (fp == NULL) {
        printf("%s file not open!\n", fname);
    }

    int elements = 0;  // number of elements

    fscanf(fp, "%d", &elements);
    fscanf(fp, "%d", &elements);

    int arr[elements][3];
    for (int i = 0; i < elements; ++i) {
        fscanf(fp, "%d %d %d", &arr[i][0], &arr[i][1], &arr[i][2]);
    }

    for (;;) {
        for (int i = 0; i < elements; ++i) {
            ochiY(255 - arr[i][2]);
            for (int g = arr[i][0]; g <= arr[i][1]; g++) {
                ochiX(g);
            }
        }
    }

    fclose(fp);
}

int main(void) {
    if(gpioInitialise() < 0) return 1;

    // x axis
    for(int i = 0; i < 8; i++){
        gpioSetMode(axis_x[i], PI_OUTPUT);
    }

    // y axis
    for(int i = 0; i < 8; i++){
        gpioSetMode(axis_y[i], PI_OUTPUT);
    }

    Paint();

    return 0;
}