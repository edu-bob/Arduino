// Simple program to verify that an Arduino is working
void setup()
{
  pinMode(13,OUTPUT);
}
void loop()
{
  digitalWrite(13, 1);
  delay(333);
  digitalWrite(13,0);
  delay(333);
}

