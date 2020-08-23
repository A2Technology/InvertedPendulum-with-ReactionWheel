#include <Encoder.h>
#define IN1_L 22
#define IN2_L 23
#define IN1_R 24
#define IN2_R 25
#define PWM_L 6
#define PWM_R 7

#define Main_encoder_1 2
#define Main_encoder_2 3
#define L_encoder_1 18
#define L_encoder_2 19
#define R_encoder_1 20
#define R_encoder_2 21
void L_motor(int rotation, int direct);
void R_motor(int rotation, int direct);
long Main_value = 0;
long L_value = 0;
long R_value = 0;

const int Main_oneRound=4086;
const int LR_oneRound=1600;

// Change these pin numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder Main_encoder(Main_encoder_1, Main_encoder_2);
Encoder L_encoder(L_encoder_2, L_encoder_1);
Encoder R_encoder(R_encoder_2, R_encoder_1);
//   avoid using pins with LEDs attached

void setup() {
  Serial.begin(9600);
   
    pinMode(IN1_L, OUTPUT);
    pinMode(IN2_L, OUTPUT);
    pinMode(IN1_R, OUTPUT);
    pinMode(IN2_R, OUTPUT);
}

long positionLeft  = -999;
long positionRight = -999;
long positionMain =-999;

void loop() {
  
  long newLeft, newRight, newMain;
  newMain=Main_encoder.read();
  newLeft = L_encoder.read();
  newRight = R_encoder.read();
  
  
  if (newLeft != positionLeft || newRight != positionRight||newMain!=positionMain) {
    Serial.print("Main = ");
    Serial.print(newMain);
    Serial.print(", Left = ");
    Serial.print(newLeft);
    Serial.print(", Right = ");
    Serial.print(newRight);
    Serial.println();
    positionLeft = newLeft;
    positionRight = newRight;
    positionMain=newMain;
  }
  // if a character is sent from the serial monitor,
  // reset both back to zero.
  if (Serial.available()) {
    Serial.read();
    Serial.println("Reset all encoder to zero");
    Main_encoder.write(0);
    L_encoder.write(0);
    R_encoder.write(0);
   }
   
}

void L_motor(int rotation, int direct)
{
    analogWrite(PWM_L, rotation);
    switch (direct)
    {
    case 1:
    {
        digitalWrite(IN1_L, LOW);
        digitalWrite(IN2_L, HIGH);
        break;
    }
    case -1:
    {
        digitalWrite(IN1_L, HIGH);
        digitalWrite(IN2_L, LOW);
        break;
    }
    default:
        Serial.print("Direction must be 1 or -1");
    }
}

void R_motor(int rotation, int direct)
{
    analogWrite(PWM_R, rotation);
    switch (direct)
    {
    case 1:
    {
        digitalWrite(IN1_R, LOW);
        digitalWrite(IN2_R, HIGH);
        break;
    }
    case -1:
    {
        digitalWrite(IN1_R, HIGH);
        digitalWrite(IN2_R, LOW);
        break;
    }
    default:
        Serial.print("Direction must be 1 or -1");
    }
}
