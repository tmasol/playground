int buzzer = A2;
void setup ()
{
  pinMode (buzzer, OUTPUT) ;
}
void loop ()
{
  unsigned char i, j ;
  while (1)
  {
    for (i = 0; i <80; i++) // When a frequency sound
    {
      analogWrite (buzzer, 255) ; //send tone
      delay (1500) ;
    }
  }
}
