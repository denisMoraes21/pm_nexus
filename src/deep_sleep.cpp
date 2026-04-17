#include "esp_sleep.h"
#include <Arduino.h>
#include "deep_sleep.h"

void deep_sleep(int TEMPO_SLEEP){
    Serial.println("ESP32 ATIVO");

    // Aqui você coloca o que quiser executar durante os 10 segundos
    // Exemplo: ligar um LED
    pinMode(2, OUTPUT);
    digitalWrite(2, HIGH);

    // Desliga o LED antes de dormir
    digitalWrite(2, LOW);

    Serial.println("Entrando em Deep Sleep por 5 segundos...");

    // Configura o tempo de wakeup (em microssegundos)
    esp_sleep_enable_timer_wakeup(TEMPO_SLEEP * 1000000);

    // Entra em deep sleep
    esp_deep_sleep_start();
}