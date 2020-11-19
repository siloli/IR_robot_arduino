#include <IRremote.h>

#include <AFMotor.h>

#define power 0xE318261B
#define right 0x20FE4DBB
#define left 0x52A3D41F
#define backward 0xA3C8EDDB
#define forward 0x511DBB
#define set_up 0xEE886D7F
#define temps 5000
#define moteur_droite 1
#define moteur_gauche 2
#define motor_speed 255
#define IR 13

int is_running = 1;
long unsigned dump_IR = 0;
AF_DCMotor droite(moteur_droite);
AF_DCMotor gauche(moteur_gauche);
IRrecv irrecv(IR);
decode_results results;

void setup() {
  irrecv.enableIRIn();
  droite.setSpeed(motor_speed);
  gauche.setSpeed(motor_speed);
  Serial.begin(9600);
    Serial.println("en avant mon capitaine");
  droite.run(FORWARD);
  gauche.run(FORWARD);
  delay(temps);
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    switch (results.value) {
      case power:
        Serial.println("Power changement");
        is_running = -is_running;
        stop();
        break;
      case right:
        if (is_running == 1)right_dir();
        break;
      case left:
        if (is_running == 1)left_dir();
        break;
      case backward:
        if (is_running == 1)backward_dir();
        break;
      case forward:
        if (is_running == 1)forward_dir();
        break;
      default:
        break;
    }
    irrecv.resume();
  }
}

void stop() {
  Serial.println("STOOOP"); 
  Serial.print(is_running);
  droite.run(RELEASE);
  gauche.run(RELEASE);
}


void right_dir() {
  Serial.println("à droite, touuute");
  droite.run(BACKWARD);
  gauche.run(FORWARD);
  delay(temps);

}
void left_dir() {
  Serial.println("à babord moussaillon");
  droite.run(FORWARD);
  gauche.run(BACKWARD);
  delay(temps);
}
void forward_dir() {
  Serial.println("en avant mon capitaine");
  droite.run(FORWARD);
  gauche.run(FORWARD);
  delay(temps);
}
void backward_dir() {
  Serial.println("maaarchee arrieeeeeeeere");
  droite.run(BACKWARD);
  gauche.run(BACKWARD);
  delay(temps);
}
