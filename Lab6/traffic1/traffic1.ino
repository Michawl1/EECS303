#define GreenA  10
#define GreenB  11
#define RedA    6
#define RedB    7

#define ON      255
#define OFF     0
#define DIM     32

void setup() 
{
  pinMode(GreenA, OUTPUT);
  pinMode(GreenB, OUTPUT);
  pinMode(RedA, OUTPUT);
  pinMode(RedB, OUTPUT);
}

void loop() 
{
  analogWrite(GreenA, OFF);
  analogWrite(GreenB, OFF);
  analogWrite(RedA, OFF);
  analogWrite(RedB, OFF);
  
  while(1)
  {
    analogWrite(GreenB, ON);
    analogWrite(RedB, OFF);
    analogWrite(GreenA, OFF);
    analogWrite(RedA, ON);

    delay(8000);

    analogWrite(GreenB, DIM);

    delay(2000);

    analogWrite(GreenB, OFF);
    analogWrite(RedB, ON);
    analogWrite(GreenA, ON);
    analogWrite(RedA, OFF);

    delay(8000);

    analogWrite(GreenA, DIM);

    delay(2000);
  }
}
