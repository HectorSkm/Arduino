#include <LiquidCrystal_SR.h>
#include <Stepper.h>
#include <IRremote.h>
#define COLS 16
#define ROWS 2
const int stepsPorRevolucion = 200;
LiquidCrystal_SR lcd (6, 5, 3);
Stepper miMotor(stepsPorRevolucion, 10, 11, 12, 13);
int ledrojo = 2;
int ledazul = 7;
int ledverde = 4;
int receptor = 8;
int buzzer = 9;
int stepCont = 0;
IRrecv irrecv(receptor);
decode_results codigo;
int clave[4];
int numRand[4];
int i = 0;
int valido = 0;
bool pase = false;
int intentos = 0;
int retardo = 5;        // Tiempo de retardo en milisegundos (Velocidad del Motor)
int dato_rx = 0;            // valor recibido en grados
int numero_pasos = 0;   // Valor en grados donde se encuentra el motor


void mando(int &i) {
  do {
  } while (!irrecv.decode(&codigo));
  if (irrecv.decode(&codigo)) {
    if (codigo.value == 0xFF30CF) {
      Serial.print("1");
      lcd.print("1");
      clave[i] = 1;
    }
    else if (codigo.value == 0xFF18E7) {
      Serial.print("2");
      lcd.print("2");
      clave[i] = 2;
    }
    else if (codigo.value == 0xFF7A85) {
      Serial.print("3");
      lcd.print("3");
      clave[i] = 3;
    }
    else if (codigo.value == 0xFF10EF) {
      Serial.print("4");
      lcd.print("4");
      clave[i] = 4;
    }
    else if (codigo.value == 0xFF38C7) {
      Serial.print("5");
      lcd.print("5");
      clave[i] = 5;
    }
    else if (codigo.value == 0xFF5AA5) {
      Serial.print("6");
      lcd.print("6");
      clave[i] = 6;
    }
    else if (codigo.value == 0xFF42BD) {
      Serial.print("7");
      lcd.print("7");
      clave[i] = 7;
    }
    else if (codigo.value == 0xFF4AB5) {
      Serial.print("8");
      lcd.print("8");
      clave[i] = 8;
    }
    else if (codigo.value == 0xFF52AD) {
      Serial.print("9");
      lcd.print("9");
      clave[i] = 9;
    }
    else if (codigo.value == 0xFF6897) {
      Serial.print("0");
      lcd.print("0");
      clave[i] = 0;
    }
    else {
      Serial.print("X");
    }

    delay(800);
    irrecv.resume();
  }
}

void comparar() {
  for (int i = 0; i < 4; i++) {
    if (clave[i] == numRand[i]) {
      valido++;
    }
  }
}

void alarma() {
  for (int t = 0; t < 6; t++) {
    analogWrite(buzzer, 100);
    digitalWrite(ledazul, HIGH);
    digitalWrite(ledrojo, LOW);
    delay(250);
    analogWrite(buzzer, 25);
    digitalWrite(ledrojo, HIGH);
    digitalWrite(ledazul, LOW);
    delay(250);
  }
  analogWrite(buzzer, 0);
  digitalWrite(ledrojo, LOW);
  digitalWrite(ledazul, LOW);
}

void abrir() {
  dato_rx = 180;   // Convierte Cadena de caracteres a Enteros
  delay(retardo);
  dato_rx = (dato_rx * 1.4222222222); // Ajuste de 512 vueltas a los 360 grados


  while (dato_rx > numero_pasos) { // Girohacia la izquierda en grados
    paso_izq();
    numero_pasos = numero_pasos + 1;
  }
  while (dato_rx < numero_pasos) { // Giro hacia la derecha en grados
    paso_der();
    numero_pasos = numero_pasos - 1;
  }
  apagado();         // Apagado del Motor para que no se caliente
}

void cerrar() {
  dato_rx = -180;   // Convierte Cadena de caracteres a Enteros
  delay(retardo);
  dato_rx = (dato_rx * 1.4222222222); // Ajuste de 512 vueltas a los 360 grados


  while (dato_rx > numero_pasos) { // Girohacia la izquierda en grados
    paso_izq();
    numero_pasos = numero_pasos + 1;
  }
  while (dato_rx < numero_pasos) { // Giro hacia la derecha en grados
    paso_der();
    numero_pasos = numero_pasos - 1;
  }
  apagado();         // Apagado del Motor para que no se caliente
}

void paso_der() {        // Pasos a la derecha
  digitalWrite(13, LOW);
  digitalWrite(12, LOW);
  digitalWrite(11, HIGH);
  digitalWrite(10, HIGH);
  delay(retardo);
  digitalWrite(13, LOW);
  digitalWrite(12, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(10, LOW);
  delay(retardo);
  digitalWrite(13, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(11, LOW);
  digitalWrite(10, LOW);
  delay(retardo);
  digitalWrite(13, HIGH);
  digitalWrite(12, LOW);
  digitalWrite(11, LOW);
  digitalWrite(10, HIGH);
  delay(retardo);
}

void paso_izq() {        // Pasos a la izquierda
  digitalWrite(13, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(11, LOW);
  digitalWrite(10, LOW);
  delay(retardo);
  digitalWrite(13, LOW);
  digitalWrite(12, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(10, LOW);
  delay(retardo);
  digitalWrite(13, LOW);
  digitalWrite(12, LOW);
  digitalWrite(11, HIGH);
  digitalWrite(10, HIGH);
  delay(retardo);
  digitalWrite(13, HIGH);
  digitalWrite(12, LOW);
  digitalWrite(11, LOW);
  digitalWrite(10, HIGH);
  delay(retardo);
}

void apagado() {         // Apagado del Motor
  digitalWrite(13, LOW);
  digitalWrite(12, LOW);
  digitalWrite(11, LOW);
  digitalWrite(10, LOW);
  dato_rx = 0;
  numero_pasos = 0;
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledrojo, OUTPUT);
  pinMode(ledverde, OUTPUT);
  pinMode(ledazul, OUTPUT);
  pinMode(buzzer, OUTPUT);
  digitalWrite(ledverde, LOW);
  digitalWrite(ledrojo, LOW);
  digitalWrite(ledazul, LOW);
  pinMode(13, OUTPUT);    // Pin 11 conectar a IN4
  pinMode(12, OUTPUT);    // Pin 10 conectar a IN3
  pinMode(11, OUTPUT);     // Pin 9 conectar a IN2
  pinMode(10, OUTPUT);     // Pin 8 conectar a IN1
  lcd.begin(COLS, ROWS);
  lcd.home();


}



void loop() {
  // put your main code here, to run repeatedly:
  irrecv.enableIRIn();
  randomSeed(analogRead(A0));
  int random1 = random(0, 9);
  int random2 = random(0, 9);
  int random3 = random(0, 9);
  int random4 = random(0, 9);
  numRand[0] = random1;
  numRand[1] = random2;
  numRand[2] = random3;
  numRand[3] = random4;
  lcd.print("CODIGO: ");
  for (int j = 0; j < 4; j++) {
    lcd.print(numRand[j]);
    Serial.print(numRand[j]);
  }
  Serial.println();
  lcd.setCursor(0, 1);

  do {
    while (i < 4) {
      mando(i);
      i++;
    }
    comparar();
    i = 0;

    if (valido == 4) {
      lcd.clear();
      lcd.print("ACERTADO");
      Serial.println();
      Serial.println("ACERTADO");
      pase = true;
    }
    else if ((valido != 4)) {
      lcd.clear();
      lcd.println("NO ACERTADO");
      lcd.println();
      Serial.println();
      Serial.println("NO ACERTADO");
      delay(1000);
      lcd.clear();
      lcd.print("CODIGO: ");
      for (int j = 0; j < 4; j++) {
        lcd.print(numRand[j]);
        Serial.print(numRand[j]);
      }
      lcd.setCursor(0, 1);
      valido = 0;
      intentos++;
    }
  } while ((!pase) && (intentos < 3));
  if (pase) {
    lcd.clear();
    lcd.print("ABRIENDO");
    Serial.println("ABRIENDO");
    digitalWrite(ledverde, HIGH);
    abrir();
    lcd.clear();
    lcd.print("TIENE 7 SEGUNDOS");
    lcd.setCursor (0, 1);
    lcd.print("PARA ENTRAR");
    digitalWrite(ledverde, LOW);
    delay(7000);
    digitalWrite(ledrojo, HIGH);
    lcd.clear();
    lcd.print("CERRANDO");
    Serial.println("CERRANDO");
    cerrar();
  }
  else {
    lcd.clear();
    lcd.print("ALARMA");
    Serial.println("ALARMA");
    alarma();
    lcd.clear();
    lcd.print("CERRANDO");
    cerrar();
    delay(1000);
    lcd.clear();
    lcd.print("SISTEMA");
    lcd.setCursor (0, 1);
    lcd.print("BLOQUEADO");
    while (!pase) {
    }
  }
  digitalWrite(ledrojo, LOW);
  digitalWrite(ledverde, LOW);
  digitalWrite(ledazul, LOW);
  analogWrite(buzzer, 0);
  valido = 0;
  intentos = 0;
  pase = false;
  delay(5000);
  lcd.clear();

}
