#include <Arduino.h>
#include "pin_definition.h"

// Função para LIGAR
void ligar(bool ledLigado)
{
  ledLigado = true;
}

// Função para DESLIGAR
void desligar(bool ledLigado)
{
  ledLigado = false;
  digitalWrite(pinoLED, LOW); // garante que apagou
}

// Função para simular PWM
void pwmManual(int tempoAlto, int tempoBaixo, int repeticoes, bool ledLigado)
{

  // Só executa se estiver ligado
  if (!ledLigado)
    return;

  for (int i = 0; i < repeticoes; i++)
  {
    digitalWrite(pinoLED, HIGH);
    delayMicroseconds(tempoAlto);

    digitalWrite(pinoLED, LOW);
    delayMicroseconds(tempoBaixo);
  }
}
