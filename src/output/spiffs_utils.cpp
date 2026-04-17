#include <Arduino.h>
#include <FS.h>
#include <SPIFFS.h>

#define BAUD_RATE          115200
#define MODO_SOBRESCREVER  0
#define MODO_ACRESCENTAR   1

inline bool criarArquivo(const char* nome, const char* conteudo) {
  if (!nome || nome[0] == '\0') {
    Serial.println(F("  [ERRO] Nome invalido."));
    return false;
  }

  if (!conteudo) {
    Serial.println(F("  [ERRO] Conteudo nulo."));
    return false;
  }

  File f = SPIFFS.open(nome, "w");
  if (!f) {
    Serial.print(F("  [ERRO] Nao foi possivel criar '"));
    Serial.print(nome);
    Serial.println(F("'."));
    return false;
  }

  size_t n = f.print(conteudo);
  f.close();

  if (n == 0 && strlen(conteudo) > 0) {
    Serial.println(F("  [AVISO] Nenhum byte gravado (flash cheia?)."));
    return false;
  }

  return true;
}

inline bool editarArquivo(const char* nome, const char* novoConteudo, uint8_t modo) {
  if (!nome || nome[0] == '\0') {
    Serial.println(F("  [ERRO] Nome invalido."));
    return false;
  }

  if (!novoConteudo) {
    Serial.println(F("  [ERRO] Conteudo nulo."));
    return false;
  }

  if (!SPIFFS.exists(nome)) {
    Serial.print(F("  [ERRO] Arquivo '"));
    Serial.print(nome);
    Serial.println(F("' nao encontrado."));
    return false;
  }

  if (modo == MODO_ACRESCENTAR) {
    File f = SPIFFS.open(nome, "a");
    if (!f) {
      Serial.print(F("  [ERRO] Nao foi possivel abrir '"));
      Serial.print(nome);
      Serial.println(F("' para append."));
      return false;
    }

    size_t n = f.print(novoConteudo);
    f.close();

    if (n == 0 && strlen(novoConteudo) > 0) {
      Serial.println(F("  [AVISO] Nenhum byte acrescentado (flash cheia?)."));
      return false;
    }

    return true;
  }

  if (modo == MODO_SOBRESCREVER) {
    File f = SPIFFS.open(nome, "w");
    if (!f) {
      Serial.print(F("  [ERRO] Nao foi possivel abrir '"));
      Serial.print(nome);
      Serial.println(F("' para sobrescrita."));
      return false;
    }

    size_t n = f.print(novoConteudo);
    f.close();

    if (n == 0 && strlen(novoConteudo) > 0) {
      Serial.println(F("  [AVISO] Nenhum byte gravado (flash cheia?)."));
      return false;
    }

    return true;
  }

  Serial.print(F("  [ERRO] Modo invalido: "));
  Serial.println(modo);
  return false;
}

inline bool apagarArquivo(const char* nome) {
  if (!nome || nome[0] == '\0') {
    Serial.println(F("  [ERRO] Nome invalido."));
    return false;
  }

  if (!SPIFFS.exists(nome)) {
    Serial.print(F("  [ERRO] Arquivo '"));
    Serial.print(nome);
    Serial.println(F("' nao existe."));
    return false;
  }

  if (!SPIFFS.remove(nome)) {
    Serial.print(F("  [ERRO] Falha ao remover '"));
    Serial.print(nome);
    Serial.println(F("'."));
    return false;
  }

  return true;
}

inline void lerArquivo(const char* nome) {
  if (!SPIFFS.exists(nome)) {
    Serial.println(F("  [Arquivo nao encontrado]"));
    return;
  }

  File f = SPIFFS.open(nome, "r");
  if (!f) {
    Serial.println(F("  [Erro ao abrir para leitura]"));
    return;
  }

  Serial.println(F("  -- conteudo --"));
  while (f.available()) {
    Serial.write(f.read());
  }
  Serial.println(F("  --------------"));
  f.close();
}

inline void sep() {
  Serial.println(F("------------------------------------"));
}