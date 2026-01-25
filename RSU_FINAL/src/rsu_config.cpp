
#include "rsu_config.h"
#include <Preferences.h>

static Preferences p;
static String key, url;

void cfg_init() {
  p.begin("rsu", false);
  key = p.getString("key", "CHANGE_ME");
  url = p.getString("url", "https://cms.vercel.app/api");
}

const char* cfg_api_key(){ return key.c_str(); }
const char* cfg_cms_url(){ return url.c_str(); }

void cfg_set_api_key(const char* k){
  key = k;
  p.putString("key", key);
}
