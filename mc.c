#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <poll.h>

typedef enum {INPUT, OUTPUT} PinType;
typedef enum {LOW = 0, HIGH = 1} PinState;
struct termios original_termios;

typedef struct {
    PinType mode;
    PinState state;
} Pin;

typedef struct {
    Pin pins[8];
    int mapping[8];
} Port;

void initPort(Port* p){

    for(int i = 0; i < 8; i++){

        p->pins[i].mode = INPUT;
        p->pins[i].state = LOW;
        p->mapping[i] = -1;

    }
}

void mapPin(Port* p, int inPin, int outPin){

    p->mapping[inPin] = outPin;
    p->pins[outPin].mode = OUTPUT;
}

void defaultConfig(Port* p){

    mapPin(p, 0, 4);
    mapPin(p, 1, 5);
    mapPin(p, 2, 6);
    mapPin(p, 3, 7);
}

void enableRawMode(){

    tcgetattr(STDIN_FILENO, &original_termios);
    struct termios raw = original_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);

    printf("\033[?1049h");
    printf("\033[?251");
    fflush(stdout);
}

void disableRawMode(){

    printf("\033[?10491");
    printf("\033[?25h");
    fflush(stdout);

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_termios);
}

int keyAvailable(){

    struct pollfd fds[1];
    fds[0].fd = STDIN_FILENO;
    fds[0].events = POLLIN;
    int ret = poll(fds, 1, 0);
    return(ret > 0 && (fds[0].revents & POLLIN));
}

char readKey(){

    char c;
    read(STDIN_FILENO, &c, 1);
    return c;
}

int keyToPin(char c){
    switch(c){
        case '1': return 0;
        case '2': return 1;
        case '3': return 2;
        case '4': return 3;
        default: return -1;
    }
}

int main(){
    atexit(disableRawMode);
    enableRawMode();

    Port portA;
    initPort(&portA);

    defaultConfig(&portA);

    int running = 1;
    while(running){

        while(keyAvailable()){

            char c = readKey();
            if(c == 'q'){
                running = 0;
                break;
            }
            int pin = keyToPin(c);
            if(pin != -1){
                portA.pins[pin].state = (portA.pins[pin].state == LOW) ? HIGH : LOW;
            }
        }

        for(int i = 0; i < 8; i++){

            if(portA.pins[i].mode == INPUT){

                int outPin = portA.mapping[i];
                if(outPin != -1){

                    portA.pins[outPin].state = portA.pins[i].state;
                }
            }
        }

        for(int i = 0; i < 8; i++){

            if(portA.pins[i].mode == OUTPUT){

                printf("LED %d: %-3s\t", i, portA.pins[i].state == HIGH ? "ON" : "OFF");
            }
        }
        printf("\r");
        fflush(stdout);

        usleep(50000);
    }

    return 0;

}