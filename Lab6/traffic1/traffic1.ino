#define GreenA  3
#define GreenB  9
#define RedA    10
#define RedB    11

#define ON      255
#define OFF     0
#define DIM     127

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
