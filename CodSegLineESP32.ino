// Pines de sensores
const int sensorIzq = 21;
const int sensorDer = 19;

// Pines del puente H
const int IN1 = 22;
const int IN2 = 23;
const int IN3 = 2;
const int IN4 = 4;
const int ENA = 5;    // PWM manual
const int ENB = 18;   // PWM manual

// Variables de PWM
const int periodoPWM = 16666; // ~60 Hz
int dutyENA = 255; // Valor de 0 a 255
int dutyENB = 255;

void setup() {
  pinMode(sensorIzq, INPUT);
  pinMode(sensorDer, INPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
}

void loop() {
  int valIzq = digitalRead(sensorIzq);
  int valDer = digitalRead(sensorDer);

  // Invertimos la lógica
  if (valIzq == 0 && valDer == 0) {
    avanzar();
  }
  else if (valIzq == 1 && valDer == 0) {
    girarDerecha();
  }
  else if (valIzq == 0 && valDer == 1) {
    girarIzquierda();
  }
  else {
    detener();
  }

  // Generación PWM manual
  int tiempoHighENA = map(dutyENA, 0, 255, 0, periodoPWM);
  int tiempoHighENB = map(dutyENB, 0, 255, 0, periodoPWM);

  // Pulso para ENA
  digitalWrite(ENA, HIGH);
  delayMicroseconds(tiempoHighENA);
  digitalWrite(ENA, LOW);
  delayMicroseconds(periodoPWM - tiempoHighENA);

  // Pulso para ENB
  digitalWrite(ENB, HIGH);
  delayMicroseconds(tiempoHighENB);
  digitalWrite(ENB, LOW);
  delayMicroseconds(periodoPWM - tiempoHighENB);
}

// Funciones de movimiento
void avanzar() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  dutyENA = 255;
  dutyENB = 255;
}

void girarIzquierda() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  dutyENA = 0;
  dutyENB = 255;
}

void girarDerecha() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  dutyENA = 255;
  dutyENB = 0;
}

void detener() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  dutyENA = 0;
  dutyENB = 0;
}