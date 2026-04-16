
#include <Arduino.h>

// ================================
// 📌 Definição de pinos e PWM
// ================================
const int pinoLED = 23;     // Pino onde o LED está conectado

// ================================
// 💡 Níveis de intensidade
// ================================
const int desligado = 0;
const int baixo     = 85;   // ~33%
const int medio     = 170;  // ~66%
const int alto      = 255;  // 100%

// ================================
// ⏱️ Tempo de blink (segundos)
// ================================
int tempoBlink = 2;

void liga() {
  analogWrite(pinoLED, alto);
}

void desliga() {
  analogWrite(pinoLED, desligado);
}  

// ================================
// ⚙️ Setup (inicialização)
// ================================
void setup() {
}


// ================================
// 🔁 Loop principal
// ================================
void loop() {

  // 🔴 LED DESLIGADO
  // controlarLED(desligado);
  delay(2000);

  // 🟢 BAIXA INTENSIDADE
  // controlarLED(baixo);
  delay(2000);

  // 🟡 MÉDIA INTENSIDADE
  // controlarLED(medio);
  delay(2000);

  // 🔵 ALTA INTENSIDADE
  // controlarLED(alto);
  delay(2000);

  // ⚡ MODO PISCANDO (BLINK)
  for (int i = 0; i < 5; i++) {

    // controlarLED(alto);                 // Liga forte
    delay(tempoBlink * 1000);           // Espera X segundos

    // controlarLED(desligado);            // Desliga
    delay(tempoBlink * 1000);           // Espera X segundos
  }
}
