#include <Arduino.h>
#include "spiffs_utils.h"

void setup() {
  Serial.begin(BAUD_RATE);
  while (!Serial) { ; }

  Serial.println(F("=== GERENCIADOR DE ARQUIVOS SPIFFS ==="));

  if (!SPIFFS.begin(true)) {
    Serial.println(F("[ERRO] Falha ao montar SPIFFS. Execucao interrompida."));
    while (true) { ; }
  }
  Serial.println(F("SPIFFS montado com sucesso.\n"));

  sep();
  Serial.println(F("[1] Criando '/dados.txt'..."));
  criarArquivo("/dados.txt", "Linha inicial.\n");
  lerArquivo("/dados.txt");

  sep();
  Serial.println(F("[2] Acrescentando conteudo..."));
  editarArquivo("/dados.txt", "Segunda linha.\n", MODO_ACRESCENTAR);
  lerArquivo("/dados.txt");

  sep();
  Serial.println(F("[3] Sobrescrevendo conteudo..."));
  editarArquivo("/dados.txt", "Conteudo novo.\n", MODO_SOBRESCREVER);
  lerArquivo("/dados.txt");

  sep();
  Serial.println(F("[4] Apagando '/dados.txt'..."));
  apagarArquivo("/dados.txt");
  lerArquivo("/dados.txt");

  sep();
  Serial.println(F("[5] Erros intencionais:"));
  editarArquivo("/naoexiste.txt", "Teste.", MODO_ACRESCENTAR);
  apagarArquivo("/fantasma.txt");

  sep();
  Serial.println(F("Fim da demonstracao."));
}

void loop() {
}