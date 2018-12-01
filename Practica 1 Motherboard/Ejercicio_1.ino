// Aquí estan definidos los puertos que se van a usar en el Arduino
const int led =  2;   

void setup() {
  // Aquí los puertos los definimos como entradas o salidas
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
}

void loop() {
  // Define el valor que tiene que dar dicho puerto
  digitalWrite(led, HIGH);
}
