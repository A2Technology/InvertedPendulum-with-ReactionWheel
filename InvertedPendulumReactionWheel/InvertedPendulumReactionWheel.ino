#define IN1_L 22
#define IN2_L 23
#define IN1_R 24
#define IN2_R 25
#define PWM_L 6
#define PWM_R 7

#define Main_encoder_1 2
#define Main_encoder_2 3
#define L_encoder_1 18
#define L_encoder_2 8
#define R_encoder_1 19
#define R_encoder_2 9

void L_motor(int rotation, int direct);
void R_motor(int rotation, int direct);
void Main_encoder(void);
void L_encoder(void);
void R_encoder(void);

long Main_value = 0;
long L_value = 0;
long R_value = 0;

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(IN1_L, OUTPUT);
    pinMode(IN2_L, OUTPUT);
    pinMode(IN1_R, OUTPUT);
    pinMode(IN2_R, OUTPUT);

    pinMode(Main_encoder_2, INPUT_PULLUP);
    pinMode(L_encoder_2, INPUT_PULLUP);
    pinMode(R_encoder_2, INPUT_PULLUP);

    digitalWrite(Main_encoder_1, LOW);
    digitalWrite(Main_encoder_2, LOW);
    digitalWrite(L_encoder_1, LOW);
    digitalWrite(L_encoder_2, LOW);
    digitalWrite(R_encoder_1, LOW);
    digitalWrite(R_encoder_2, LOW);

    attachInterrupt(digitalPinToInterrupt(Main_encoder_1), Main_encoder, CHANGE);
    attachInterrupt(digitalPinToInterrupt(L_encoder_1), L_encoder, CHANGE);
    attachInterrupt(digitalPinToInterrupt(R_encoder_1), R_encoder, CHANGE);

    attachInterrupt(digitalPinToInterrupt(Main_encoder_2), Main_encoder, CHANGE);
    attachInterrupt(digitalPinToInterrupt(L_encoder_2), L_encoder, CHANGE);
    attachInterrupt(digitalPinToInterrupt(R_encoder_2), R_encoder, CHANGE);
}

void loop()
{
    R_motor(255, 1);
    L_motor(255, 1);
    
    delay(500);
    Serial.print("Main: ");
    Serial.println(Main_value);
    Serial.print("Left: ");
    Serial.println(L_value);
    Serial.print("Right: ");
    Serial.println(R_value);
    R_motor(0, 1);
    L_motor(0, 1);
    delay(500);
    Serial.print("Main: ");
    Serial.println(Main_value);
    Serial.print("Left: ");
    Serial.println(L_value);
    Serial.print("Right: ");
    Serial.println(R_value);
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
    case 0:
    {
        digitalWrite(IN1_R, LOW);
        digitalWrite(IN2_R, LOW);
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
    case 0:
    {
        digitalWrite(IN1_R, LOW);
        digitalWrite(IN2_R, LOW);
        break;
    }
    
    default:
        Serial.print("Direction must be 1 or -1");
    }
}

void Main_encoder(void)
{
    Main_value++;
}
void L_encoder(void)
{
    L_value++;
}
void R_encoder(void)
{
    R_value++;
}
