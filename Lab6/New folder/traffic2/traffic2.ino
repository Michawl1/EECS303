#define BUTTONA 2
#define BUTTONB 3
#define PEDA    4
#define PEDB    5

#define GREENA  10
#define GREENB  11
#define REDA    6
#define REDB    7

#define ON      255
#define OFF     0
#define DIM     32

#define REGTRAFFICA 0
#define REGTRAFFICB 1
#define PEDATRAFFICB 2
#define PEDATRAFFICA 3
#define PEDBTRAFFICA 4
#define PEDBTRAFFICB 5

int current_state = REGTRAFFICA;
boolean apressed = false;
boolean bpressed = false;
void setup() 
{
  pinMode(GREENA, OUTPUT);
  pinMode(GREENB, OUTPUT);
  pinMode(REDA, OUTPUT);
  pinMode(REDB, OUTPUT);
  pinMode(PEDA, OUTPUT);
  pinMode(PEDB, OUTPUT);
  pinMode(BUTTONA, INPUT);
  attachInterrupt(digitalPinToInterrupt(BUTTONA), ButtonAISR, HIGH);
  attachInterrupt(digitalPinToInterrupt(BUTTONB), ButtonBISR, HIGH);
}

void loop() 
{
  reset_lights();
  if(apressed){
    if(current_state == REGTRAFFICA){
      current_state = PEDATRAFFICB;
    }
    else{
      current_state = PEDATRAFFICA;
    }
  }
  else if(bpressed){
    if(current_state == REGTRAFFICA){
      current_state = PEDBTRAFFICB;
    }
    else{
      current_state = PEDBTRAFFICA;
    }
  }
  switch(current_state){
    case REGTRAFFICA:
      reg_traffica();
      current_state = REGTRAFFICB;
      break;
    case REGTRAFFICB:
      reg_trafficb();
      current_state = REGTRAFFICA;
      apressed = false;
      break;
    case PEDATRAFFICB:
      peda_trafficb();
      current_state = REGTRAFFICA;
      apressed = false;
      break;
    case PEDATRAFFICA:
      peda_traffica();
      current_state = REGTRAFFICB;
      break;
    case PEDBTRAFFICA:
      pedb_traffica();
      current_state = REGTRAFFICB;
      bpressed = false;
      break;
    case PEDBTRAFFICB:
      pedb_trafficb();
      current_state = REGTRAFFICA;
      bpressed = false;
      break;
  }
}

void ButtonAISR(){
  apressed = true;
}

void ButtonBISR(){
  bpressed = true;
}

void reg_traffica(){
  analogWrite(GREENA, ON);
  analogWrite(REDB, ON);
  delay(8000);
  analogWrite(GREENA, DIM);
  delay(2000);
  analogWrite(GREENA, OFF);
  analogWrite(REDA, ON);
  delay(1000);
}
void reg_trafficb(){
  analogWrite(GREENB, ON);
  analogWrite(REDA, ON);
  delay(8000);
  analogWrite(GREENB, DIM);
  delay(2000);
  analogWrite(GREENB, OFF);
  analogWrite(REDB, ON);
  delay(1000);
}

void peda_traffica(){
  digitalWrite(PEDA, HIGH);
  analogWrite(REDA, ON);
  analogWrite(REDB, ON);
  delay(11000);
}

void peda_trafficb(){
  digitalWrite(PEDA, HIGH);
  analogWrite(REDA, ON);
  analogWrite(GREENB, ON);
  delay(8000);
  analogWrite(GREENB, DIM);
  delay(2000);
  analogWrite(GREENB, OFF);
  delay(1000);
}

void pedb_traffica(){
  digitalWrite(PEDB, HIGH);
  analogWrite(REDB, ON);
  analogWrite(GREENA, ON);
  delay(8000);
  analogWrite(GREENA, DIM);
  delay(2000);
  analogWrite(GREENA, OFF);
  delay(1000);
}

void pedb_trafficb(){
  digitalWrite(PEDB, HIGH);
  analogWrite(REDA, ON);
  analogWrite(REDB, ON);
  delay(11000);
}
void reset_lights(){
  analogWrite(REDB, OFF);
  analogWrite(GREENB, OFF);
  analogWrite(REDA, OFF);
  analogWrite(GREENA, OFF);
  digitalWrite(PEDA, LOW);
  digitalWrite(PEDB, LOW);
}
