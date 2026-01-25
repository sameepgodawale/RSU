
#include "heartbeat.h"
#include "sim800.h"

unsigned long lastHb = 0;

void heartbeat_init() {
  lastHb = millis();
}

void heartbeat_poll() {
  if (millis() - lastHb < HEARTBEAT_MS) return;
  lastHb = millis();
  sim800_http_post("/rsu/heartbeat", "{\"status\":\"ok\"}");
}
