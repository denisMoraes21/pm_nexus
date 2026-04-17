#include "led_state.h"
#include <Arduino.h>
#include "pin_definition.h"


// Função para LIGAR
void ligar(bool ledLigado) {
  ledLigado = true;
}

// Função para DESLIGAR 
void desligar(bool ledLigado) {
  ledLigado = false;
  digitalWrite(pinoLED, LOW); // garante que apagou
}