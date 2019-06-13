#include <stdio.h>
#include <string.h> //strlen
#include <stdlib.h>
#include <errno.h>
#include <unistd.h> //close
#include <arpa/inet.h> //close
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros

void update_game_info(char *buffer, char *barreltype, float *posx, float *posy) {

    int i = 2;
    int xcount = 0;
    int ycount = 0;
    char x[10];
    char y[10];
    while(buffer[i] != '/') {
        x[xcount] = buffer[i];
        i++;
        xcount++;
    }
    i++;
    printf("%c", buffer[i]);
    while(buffer[i] != '/') {
        y[ycount] = buffer[i];
        i++;
        ycount++;
    }
    i++;
    *barreltype = buffer[i];
    *posx = (float)atof(x);
    *posy = (float)atof(y);

    printf("--END--");
}

int main() {
    char buffer[1025] = {'1', '/', '5', '3', '5', '.', '1', '5', '6', '/', '6', '1', '5', '.', '6', '6', '6', '6', '6', '/', '0'};
    char barreltype;

    float posx = 0;
    float posy = 0;

    barreltype = '0';

    update_game_info(buffer, &barreltype, &posx, &posy);

    return 0;
}