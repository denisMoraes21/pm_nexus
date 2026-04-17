#include <Arduino.h>
#include "pin_definition.h"
#include "led_state.h"
#include "led_function.h"

// Estado do LED
bool ledLigado = false;

// Função para simular PWM
void pwmManual(int tempoAlto, int tempoBaixo, int repeticoes, bool ledLigado) {

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
  desligar(ledLigado);
  delay(2000);

  // 🟢 LIGADO - Baixa intensidade
  ligar(ledLigado);
  pwmManual(200, 800, 5000, ledLigado);

  // 🟡 Média intensidade
  pwmManual(500, 500, 5000, ledLigado);

  // 🔵 Alta intensidade
  pwmManual(800, 200, 5000, ledLigado);

  // 🔴 DESLIGA novamente
  desligar(ledLigado);
  delay(2000);

  // ⚡ BLINK (liga/desliga)
  for (int i = 0; i < 5; i++) {
    ligar(ledLigado);
    digitalWrite(pinoLED, HIGH);
    delay(1000);

    desligar(ledLigado);
    delay(1000);
  }
}