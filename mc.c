typedef enum {INPUT, OUTPUT} PinType;
typedef enum {LOW = 0, HIGH = 1} PinState;


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

    p->pins[inPin] = outPin;
    p-pins[outPin].mode = OUTPUT;
}

int main(){

    Port portA;
    initPort(&portA);



}