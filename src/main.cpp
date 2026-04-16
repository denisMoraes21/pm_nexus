#include <Arduino.h>

const int pinoLED = 23;

// Estado do LED
bool ledLigado = false;

// Função para LIGAR
void ligar() {
  ledLigado = true;
}

// Função para DESLIGAR 
void desligar() {
  ledLigado = false;
  digitalWrite(pinoLED, LOW); // garante que apagou
}

// Função para simular PWM
void pwmManual(int tempoAlto, int tempoBaixo, int repeticoes) {

  // Só executa se estiver ligado
  if (!ledLigado) return;

  for (int i = 0; i < repeticoes; i++) {
    digitalWrite(pinoLED, HIGH);
    delayMicroseconds(tempoAlto);

    digitalWrite(pinoLED, LOW);
    delayMicroseconds(tempoBaixo);
  }
}

void setup() {
  Serial.begin(115200); 
  pinMode(pinoLED, OUTPUT);
}

void loop() {

  // 🔴 DESLIGADO
  desligar();
  delay(2000);

  // 🟢 LIGADO - Baixa intensidade
  ligar();
  pwmManual(200, 800, 5000);

  // 🟡 Média intensidade
  pwmManual(500, 500, 5000);

  // 🔵 Alta intensidade
  pwmManual(800, 200, 5000);

  // 🔴 DESLIGA novamente
  desligar();
  delay(2000);

  // ⚡ BLINK (liga/desliga)
  for (int i = 0; i < 5; i++) {
    ligar();
    digitalWrite(pinoLED, HIGH);
    delay(1000);

    desligar();
    delay(1000);
  }
}