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
#define DIM     127

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

  pinMode(ButtonA, INPUT_PULLUP);
  pinMode(ButtonB, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ButtonA), buttonA_IRQ, LOW);
  attachInterrupt(digitalPinToInterrupt(ButtonB), buttonB_IRQ, LOW);

  flagA = false;
  flagB = false;
}

void loop() 
{
  analogWrite(GreenA, OFF);
  analogWrite(GreenB, OFF);
  digitalWrite(RedA, LOW);
  digitalWrite(RedB, LOW);

  int counter = 0;
  
  while(1)
  {
    if(!flagB && !flagA)
    {
      trafficA(false);
      trafficB(true);
      trafficB(false);
      trafficA(true);
    }
    else if(flagA)
    {
      if(counter == 2)
      {
        counter = 0;
      }
    }
    else if(flagB)
    {
      if(counter == 2)
      {
        counter = 0;
      }
    }
  }
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
  digitalWrite(PedA, HIGH);
  trafficA(false);

  for(int i = 0; i < 3; i++)
  {
    trafficB(true);
    trafficB(false);
    delay(10000);
  }
  
  digitalWrite(PedA, LOW);
}

void buttonB_IRQ()
{
  flagB = true;
}
