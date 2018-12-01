//Definimos los puertos usados en el Arduino
const int boton = 4;
const int led = 2;
int estado = LOW;

void setup() {

  //Distinguimos los puertos de entrada y salida y valor inicial del led
  pinMode(led, OUTPUT);
  pinMode(boton, INPUT);
  digitalWrite(led, LOW);

}

void loop() {

  //Estas son las condiciones para encender y apagar el led con el boton
  while (digitalRead(boton) == LOW);
  estado = digitalRead(led);
  digitalWrite(led, !estado);
  while (digitalRead(boton) == HIGH);

}
