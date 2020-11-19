#include <AFMotor.h>
#include <IRremote.h>
#define power 0xFFA25D
#define right
#define left
#define backward
#define forward
#define temps 500
#define moteur_droite
#define moteur_gauche
#define speed 200
int run=1
AF_DCMotor droite(moteur_droite,MOTOR12_64KHZ);
AF_DCMotor gauche(moteur_gauche,MOTOR12_64KHZ);
IRrecv irrecv(IR);
decode_results results;


void setup(){
    irrecv.enableIRIn();
    droite.setSpeed(speed);
    gauche.setSpeed(speed);
}


void loop(){

}
void recherche_IR(){
    if(irrecv.decode(&results)){
        switch(results.value){
            case power:
                run=-run;
                break;
            case right:
                if (run==1)right_dir();
                break;
            case left:
                if (run==1)left_dir();
                break;
            case backward:
                if (run==1)backward_dir();
                break;
            case forward:
                if (run==1)forward_dir();
                break;
        }
        if(results.value!=0xFFFFFF)stop();
        irrecv.resume();
}
void stop(){
    droite.run(RELEASE);
    gauche.run(RELEASE);
    delay(temps);
}
void right_dir(){
    if(run==1){
        droite.run(BACKWARD);
        gauche.run(FORWARD);
        delay(temps);
    }
}
void left_dir(){
    if(run==1){
        droite.run(FORWARD);
        gauche.run(BACKWARD);
        delay(temps);
    }
}
void forward_dir(){
    if(run==1){
        droite.run(FORWARD);
        gauche.run(FORWARD);
        delay(temps);
    }
}
void backward_dir(){
    if(run==1){
        droite.run(BACKWARD);
        gauche.run(BACKWARD);
        delay(temps);
    }
}
