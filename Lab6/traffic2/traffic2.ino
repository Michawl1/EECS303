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

#define STARTUP 100

bool flagA;
bool flagB;

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
  attachInterrupt(digitalPinToInterrupt(ButtonA), buttonA_IRQ, LOW);
  attachInterrupt(digitalPinToInterrupt(ButtonB), buttonB_IRQ, LOW);

  flagA = false;
  flagB = false;

  startBlink();
}

void loop() 
{
  analogWrite(GreenA, OFF);
  analogWrite(GreenB, OFF);
  digitalWrite(RedA, LOW);
  digitalWrite(RedB, LOW);

  while(1)
  {
    if(!flagB && !flagA)
    {
      trafficA(false);
      trafficB(true);
    }

    if(!flagB && !flagA)
    {
      trafficB(false);
      trafficA(true);
    }
    
    if(flagA)
    {
      digitalWrite(PedA, HIGH);
      for(int i = 0; i < 3; i++)
      {
        trafficA(false);
        trafficB(true);
        trafficB(false);
        delay(10000);
      }
      flagA = false;
      digitalWrite(PedA, LOW);
      trafficA(true);
      trafficB(false);
    }
    
    if(flagB)
    {
      digitalWrite(PedB, HIGH);
      for(int i = 0; i < 3; i++)
      {
        trafficB(false);
        trafficA(true);
        trafficA(false);
        delay(10000);
      }
      flagB = false;
      digitalWrite(PedB, LOW);
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

    delay(8000);

    analogWrite(GreenA, DIM);

    delay(2000);
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

    delay(8000);

    analogWrite(GreenB, DIM);

    delay(2000);
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
