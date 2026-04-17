#ifndef SPIFFS_UTILS_H
#define SPIFFS_UTILS_H

#include <Arduino.h>
#include <FS.h>
#include <SPIFFS.h>

#define BAUD_RATE 115200
#define MODO_SOBRESCREVER 0
#define MODO_ACRESCENTAR 1

inline bool criarArquivo(const char *nome, const char *conteudo);

inline bool editarArquivo(const char *nome, const char *novoConteudo, uint8_t modo);

inline void lerArquivo(const char *nome);

#endif