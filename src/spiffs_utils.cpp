#include "spiffs_utils.h"

const char *TAG_SPIFFS = "SPIFFS";

bool spi_ffs::settingsFileExists()
{
  if (!SPIFFS.begin(true))
  {

#ifdef DEBUG_VALUES
    ESP_LOGE(TAG_SPIFFS, "Error during mount SPIFFS");
#endif

    ESP.restart();
    return false;
  }
  String path = "/" + String(CONFIG_FILE);

  if (SPIFFS.exists(path))
  {

#ifdef DEBUG_VALUES
    ESP_LOGI(TAG_SPIFFS, "%s exists", path);
#endif
    return true;
  }

#ifdef DEBUG_VALUES
  ESP_LOGE(TAG_SPIFFS, "%s not exists", path);
#endif
  return false;
}

bool spi_ffs::createFile(const char *conteudo)
{
  const char *nome = CONFIG_FILE;
  if (!nome || nome[0] == '\0')
  {

#ifdef DEBUG_VALUES
    ESP_LOGE(TAG_SPIFFS, "Invalid name!");
#endif

    return false;
  }

  if (!conteudo)
  {

#ifdef DEBUG_VALUES
    ESP_LOGE(TAG_SPIFFS, "Null content!");
#endif

    return false;
  }

  File f = SPIFFS.open(nome, "w");
  if (!f)
  {

#ifdef DEBUG_VALUES
    ESP_LOGE(TAG_SPIFFS, "Not possible create file! %s", nome);
#endif

    return false;
  }

  size_t n = f.print(conteudo);
  f.close();

  if (n == 0 && strlen(conteudo) > 0)
  {

#ifdef DEBUG_VALUES
    ESP_LOGE(TAG_SPIFFS, "None writed (Is flash memory full?)");
#endif

    return false;
  }

  return true;
}

// inline bool apagarArquivo(const char *nome)
// {
//   if (!nome || nome[0] == '\0')
//   {
//     Serial.println(F("  [ERRO] Nome invalido."));
//     return false;
//   }

//   if (!SPIFFS.exists(nome))
//   {
//     Serial.print(F("  [ERRO] Arquivo '"));
//     Serial.print(nome);
//     Serial.println(F("' nao existe."));
//     return false;
//   }

//   if (!SPIFFS.remove(nome))
//   {
//     Serial.print(F("  [ERRO] Falha ao remover '"));
//     Serial.print(nome);
//     Serial.println(F("'."));
//     return false;
//   }

//   return true;
// }
