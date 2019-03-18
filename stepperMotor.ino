#define STEPPER_PIN_1 0
#define STEPPER_PIN_2 1
#define STEPPER_PIN_3 2
#define STEPPER_PIN_4 4
int step_number = 0;
boolean dir = false;// false=clockwise,true=counter clockwise
int start_motor;
int counter = 0;
void pciSetup(byte pin)
{
  *digitalPinToPCMSK(pin) |= bit (digitalPinToPCMSKbit(pin));  // enable pin
  PCIFR  |= bit (digitalPinToPCICRbit(pin)); // clear any outstanding interrupt
  PCICR  |= bit (digitalPinToPCICRbit(pin)); // enable interrupt for the group
}

ISR (PCINT0_vect){
  if(digitalRead(13)){
    start_motor = 1;
  }
  if(digitalRead(10)){
    start_motor = 0;
  }
}

void motor(){
  if(counter >=500){
    counter=0;
  
    dir= !dir;
  }
    if (start_motor == 1 && counter <=500){
        counter ++;
    switch(step_number){
    case 0:
    digitalWrite(STEPPER_PIN_1,LOW);
    digitalWrite(STEPPER_PIN_2,LOW);
    digitalWrite(STEPPER_PIN_3,LOW);
    digitalWrite(STEPPER_PIN_4,HIGH);
    break;
    case 1:
    digitalWrite(STEPPER_PIN_1,LOW);
    digitalWrite(STEPPER_PIN_2,LOW);
    digitalWrite(STEPPER_PIN_3,HIGH);
    digitalWrite(STEPPER_PIN_4,HIGH);
    break;
    case 2:
    digitalWrite(STEPPER_PIN_1,LOW);
    digitalWrite(STEPPER_PIN_2,LOW);
    digitalWrite(STEPPER_PIN_3,HIGH);
    digitalWrite(STEPPER_PIN_4,LOW);
    break;
    case 3:
    digitalWrite(STEPPER_PIN_1,LOW);
    digitalWrite(STEPPER_PIN_2,HIGH);
    digitalWrite(STEPPER_PIN_3,HIGH);
    digitalWrite(STEPPER_PIN_4,LOW);
    break;
    case 4:
    digitalWrite(STEPPER_PIN_1,LOW);
    digitalWrite(STEPPER_PIN_2,HIGH);
    digitalWrite(STEPPER_PIN_3,LOW);
    digitalWrite(STEPPER_PIN_4,LOW);
    break;
    case 5:
    digitalWrite(STEPPER_PIN_1,HIGH);
    digitalWrite(STEPPER_PIN_2,HIGH);
    digitalWrite(STEPPER_PIN_3,LOW);
    digitalWrite(STEPPER_PIN_4,LOW);
    break;
    case 6:
    digitalWrite(STEPPER_PIN_1,HIGH);
    digitalWrite(STEPPER_PIN_2,LOW);
    digitalWrite(STEPPER_PIN_3,LOW);
    digitalWrite(STEPPER_PIN_4,LOW);
    break;
    case 7:
    digitalWrite(STEPPER_PIN_1,HIGH);
    digitalWrite(STEPPER_PIN_2,LOW);
    digitalWrite(STEPPER_PIN_3,LOW);
    digitalWrite(STEPPER_PIN_4,HIGH);
    break;
    default:
    digitalWrite(STEPPER_PIN_1,LOW);
    digitalWrite(STEPPER_PIN_2,LOW);
    digitalWrite(STEPPER_PIN_3,LOW);
    digitalWrite(STEPPER_PIN_4,LOW);
    break;  
  }

if(dir){
  step_number++;
}
else{
  step_number--;
}
if(step_number>7){
  step_number=0;
}
if(step_number<0){
  step_number=7;
}
delayMicroseconds(1500); 
  }
  else if (start_motor == 0){
    digitalWrite(STEPPER_PIN_1,LOW);
    digitalWrite(STEPPER_PIN_2,LOW);
    digitalWrite(STEPPER_PIN_3,LOW);
    digitalWrite(STEPPER_PIN_4,LOW);
  }
}

void setup() {
  pinMode(STEPPER_PIN_1,OUTPUT);
  pinMode(STEPPER_PIN_2,OUTPUT);
  pinMode(STEPPER_PIN_3,OUTPUT);
  pinMode(STEPPER_PIN_4,OUTPUT);
  pciSetup(13);
  pciSetup(10);
}

void loop() {
  motor();
}
