int potPin=0;
int potLectura=0;
int ledV=3;
int ledR=4;
int ledA=5;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledV, OUTPUT);
  pinMode(ledR, OUTPUT);
  pinMode(ledA, OUTPUT);
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
  potLectura=analogRead(potPin)/4;
  if (potLectura < 2){
    analogWrite(ledV,potLectura);
    delay(10);
  } 
  if (potLectura >=2 && potLectura <4){
    analogWrite(ledR, potLectura);
    delay(10);
  }
  else {
    analogWrite(ledA,potLectura);
    delay(10);
  }
  Serial.println(potLectura);
  delay(10);

}
