#define ButtonA 2
#define ButtonB 3
#define PedA    4
#define PedB    5

#define GreenA  10
#define GreenB  11
#define RedA    6
#define RedB    7

#define ON      255
#define OFF     0
#define DIM     32

#define StateA        0
#define StateADim     1
#define StateAOverlap 2
#define StateB        3
#define StateBDim     4
#define StateBOverlap 5
#define Ped           6

#define LONG  8000 / 4
#define SHORT 2000 / 4

#define STARTUP 100

bool flagA;
bool flagB;

int state;
int prevState;

void setup() 
{
  pinMode(GreenA, OUTPUT);
  pinMode(GreenB, OUTPUT);
  pinMode(RedA, OUTPUT);
  pinMode(RedB, OUTPUT);

  pinMode(PedA, OUTPUT);
  pinMode(PedB, OUTPUT);

  pinMode(ButtonA, CHANGE);
  pinMode(ButtonB, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ButtonA), buttonA_IRQ, HIGH);
  attachInterrupt(digitalPinToInterrupt(ButtonB), buttonB_IRQ, HIGH);

  flagA = false;
  flagB = false;

  state = StateA;

  startBlink();
}

void loop() 
{    
  analogWrite(GreenA, OFF);
  analogWrite(GreenB, OFF);
  digitalWrite(RedA, HIGH);
  digitalWrite(RedB, HIGH);
  
  while(1)
  {    
    
    switch(state)
    {
      case StateA:
        if(!flagA && !flagB)
        {
          state = StateADim;
        }
        else
        {
          state = Ped;
        }
        analogWrite(GreenA, ON);
        digitalWrite(RedA, LOW);
        delay(LONG);
        break;
        
      case StateADim:
        state = StateAOverlap;
        analogWrite(GreenA, DIM);
        delay(SHORT);
        break;
        
      case StateAOverlap:
        if(!flagA && !flagB)
        {
          state = StateB;
        }
        else
        {
          state = Ped;
        }
        analogWrite(GreenA, OFF);
        digitalWrite(RedA, HIGH);
        analogWrite(GreenB, OFF);
        digitalWrite(RedB, HIGH);
        delay(SHORT);
        break;
        
      case StateB:
        if(!flagA && !flagB)
        {
          state = StateBDim;
        }
        else
        {
          state = Ped;
        }
        analogWrite(GreenB, ON);
        digitalWrite(RedB, LOW);
        delay(LONG);
        break;
        
      case StateBDim:
        state = StateBOverlap;
        prevState = state;
        analogWrite(GreenB, DIM);
        delay(SHORT);
        break;
        
      case StateBOverlap:
        if(!flagA && !flagB)
        {
          state = StateA;
        }
        else
        {
          state = Ped;
        }
        analogWrite(GreenA, OFF);
        digitalWrite(RedA, HIGH);
        analogWrite(GreenB, OFF);
        digitalWrite(RedB, HIGH);
        delay(SHORT);
        break;
        
      case Ped:
          if(flagA)
          {
            digitalWrite(PedA, HIGH);
            for(int i = 0; i < 3; i++)
            {
              trafficA(false);
              trafficB(true);
              trafficB(false);
              delay(LONG);
              delay(SHORT);
            }
            flagA = false;
            digitalWrite(PedA, LOW);
            if(!flagB)
            {
              state = StateB;
            }
          }
          else if(flagB)
          {
            digitalWrite(PedB, HIGH);
            for(int i = 0; i < 3; i++)
            {
              trafficB(false);
              trafficA(true);
              trafficA(false);
              delay(LONG);
              delay(SHORT);
            }
            flagB = false;
            digitalWrite(PedB, LOW); 
            if(!flagA)
            {   
              state = StateA;
            }
          }
      }
  }
}

void startBlink()
{
  digitalWrite(RedA, HIGH);
  delay(STARTUP);
  digitalWrite(RedA, LOW);

  analogWrite(GreenA, ON);
  delay(STARTUP);
  analogWrite(GreenA, OFF);

  digitalWrite(PedA, HIGH);
  delay(STARTUP);
  digitalWrite(PedA, LOW);

  digitalWrite(RedB, HIGH);
  delay(STARTUP);
  digitalWrite(RedB, LOW);

  analogWrite(GreenB, ON);
  delay(STARTUP);
  analogWrite(GreenB, OFF);

  digitalWrite(PedB, HIGH);
  delay(STARTUP);
  digitalWrite(PedB, LOW);
  
  delay(STARTUP);
  delay(STARTUP);
  delay(STARTUP);
}

void trafficA(bool flag)
{
  if(flag)
  {
    analogWrite(GreenA, ON);
    digitalWrite(RedA, LOW);

    delay(LONG);

    analogWrite(GreenA, DIM);

    delay(SHORT);
  }
  else
  {
    analogWrite(GreenA, OFF);
    digitalWrite(RedA, HIGH);
  }
}

void trafficB(bool flag)
{
  if(flag)
  {
    analogWrite(GreenB, ON);
    digitalWrite(RedB, LOW);

    delay(LONG);

    analogWrite(GreenB, DIM);

    delay(SHORT);
  }
  else
  {
    analogWrite(GreenB, OFF);
    digitalWrite(RedB, HIGH);
  }
}

void buttonA_IRQ()
{
  flagA = true;
}

void buttonB_IRQ()
{
  flagB = true;
}
