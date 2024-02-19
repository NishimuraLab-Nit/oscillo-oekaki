#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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

void Point(int x, int y) {
    ochiX(x);
    ochiY(y);
    usleep(1);
}

void Draw() {
    FILE *fp = NULL;
    char fname[] = "";
    double frameRate = 0;
    int frameLength = 0;

    printf("ファイル名:");
    scanf("%s", fname);

    printf("Frame Rate:");
    scanf("%lf", &frameRate);
    frameLength = (int)(1000000.0 / frameRate);

    char path[100];
    snprintf(path, sizeof path, "data/%s", fname);
    fp = fopen(path, "r");
    if (fp == NULL) {
        printf("%s file not open!\n", fname);
    }

    int images = 0;  // number of images
    fscanf(fp, "%d", &images);
    for (int i = 0; i < images; i++) {
        int elements = 0;  // number of elements

        clock_t start, end;
        start = clock();

        fscanf(fp, "%d", &elements);

        int arr[elements][3];

        for (int j = 0; j < elements; j++) {
            fscanf(fp, "%d %d %d", &arr[j][0], &arr[j][1], &arr[j][2]);
            if (arr[j][2] != arr[j - 1][2]) {
                ochiY(255 - arr[j][2]);
            }
            for (int g = arr[j][0]; g <= arr[j][1]; g++) {
                ochiX(g);
            }
        }
        Point(i, 0);
        end = clock();
        int t = (int)(((double)(end - start) / CLOCKS_PER_SEC) * 1000000.0);
        if (frameLength > t) {
            usleep(frameLength - t);
        }
    }
    fclose(fp); 
}

int main(void){
    if(gpioInitialise() < 0) return 1;

    // init
    // x axis
    for(int i = 0; i < 8; i++){
        gpioSetMode(axis_x[i], PI_OUTPUT);
    }
    //y axis
    for(int i = 0; i < 8; i++){
        gpioSetMode(axis_y[i], PI_OUTPUT);
    }

    Draw();

    return 0;
}