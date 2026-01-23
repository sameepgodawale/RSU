
#include "sim800.h"
#include <HardwareSerial.h>
#include "rsu_config.h"

static HardwareSerial sim(2);

static bool at(const char* cmd, unsigned long t=3000) {
  sim.println(cmd);
  unsigned long s = millis();
  while (millis()-s < t) {
    if (sim.find("OK")) return true;
    if (sim.find("ERROR")) return false;
  }
  return false;
}

bool sim800_init() {
  sim.begin(115200, SERIAL_8N1, 16, 17);
  delay(1000);
  return at("AT") && at("ATE0");
}

bool sim800_http_post(const char* path, const char* json) {
  String url = String(cfg_cms_url()) + path;
  if (!at("AT+HTTPTERM")) {}
  if (!at("AT+HTTPINIT")) return false;
  at("AT+HTTPPARA=\"CID\",1");
  at((String("AT+HTTPPARA=\"URL\",\"")+url+"\"").c_str());
  at((String("AT+HTTPPARA=\"USERDATA\",\"x-api-key: ")+cfg_api_key()+"\"").c_str());
  at("AT+HTTPPARA=\"CONTENT\",\"application/json\"");
  sim.print("AT+HTTPDATA=");
  sim.print(strlen(json));
  sim.println(",5000");
  if (!sim.find("DOWNLOAD")) return false;
  sim.print(json);
  delay(500);
  sim.println();
  at("AT+HTTPACTION=1",10000);
  at("AT+HTTPTERM");
  return true;
}

bool sim800_http_get(const char* path, String& out) {
  String url = String(cfg_cms_url()) + path;
  at("AT+HTTPINIT");
  at((String("AT+HTTPPARA=\"URL\",\"")+url+"\"").c_str());
  at((String("AT+HTTPPARA=\"USERDATA\",\"x-api-key: ")+cfg_api_key()+"\"").c_str());
  at("AT+HTTPACTION=0",10000);
  sim.println("AT+HTTPREAD");
  out = sim.readString();
  at("AT+HTTPTERM");
  return true;
}
