//Definimos los puertos del led y el boton
const int led =  2;
const int boton = 4;

//Definimos variable y su estado inicial
int contador = 0;


void setup()
{
  Serial.begin(9600);

  //Distinguimos las entradas y salidas y estado inical del led
  pinMode(boton, INPUT);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
}


void loop()
{

  //Esta condición sirve como función antirebote para el boton
  while ( digitalRead(boton) == HIGH )
  {

    if ( digitalRead(boton) == LOW )
    {
      contador++;
      Serial.println(contador);
      delay (100);
      break;
    }
  }

  //Estas son las condiciones van cumpliendose dependiendo de las veces que se pulsa el boton

  //Esta condición enciende el led
  while (contador == 1)
  {
    digitalWrite(led, HIGH);
    break;
  }

  //Esta condición hace un parpadeo lento en el led
  while (contador == 2)
  {
    digitalWrite(led, HIGH);
    delay(1000);
    digitalWrite(led, LOW);
    delay(1000);
    break;

  }

  //Esta condición hace un parpadeo rapido en el led
  while (contador == 3)
  {
    digitalWrite(led, HIGH);
    delay (200);
    digitalWrite(led, LOW);
    delay (200);
    break;
  }

  //Esta condición se cumple al pulsar 4 veces el boton, apaga el led y pone el contador a 0
  while (contador == 4)
  {
    digitalWrite(led, LOW);
    contador = 0;
    break;
  }
}
