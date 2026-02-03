#include "wifi_mgr.h"
#include <WiFi.h>
#include "rsu_config.h"

void wifi_init() {
  if (strlen(cfg_wifi_ssid()) == 0) return;

  WiFi.mode(WIFI_STA);
  WiFi.begin(cfg_wifi_ssid(), cfg_wifi_pass());

  Serial.print("[WiFi] Connecting");
  unsigned long start = millis();

  while (WiFi.status() != WL_CONNECTED && millis() - start < 8000) {
    delay(500);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n[WiFi] Connected");
    Serial.print("[WiFi] IP: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\n[WiFi] Failed (fallback only)");
  }
}

bool wifi_ready() {
  return WiFi.status() == WL_CONNECTED;
}
