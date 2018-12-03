int potPin = 0;
int potLectura = 0;
int led = 3;


void setup()
{
  Serial.begin(9600);
  pinMode(led, OUTPUT);

}

void loop()
{
  potLectura = analogRead(potPin) / 4;
  Serial.println(potLectura);
  delay(10);
  if(potLectura > 220){
    digitalWrite(led, HIGH);
  }
  else{
    digitalWrite(led, LOW);
  }


 
}
