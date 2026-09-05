/* Heartware Rev A - XIAO ESP32-C3
   Plays one embedded PCM track over I2S/MAX98357A and fades 5 LEDs.
   Add your locally generated song_data.h before compiling.
*/
#include <Arduino.h>
#include <driver/i2s.h>
#include "song_data.h"

const int LEDS[5] = {D1, D2, D3, D4, D5};
const int PIN_LRC = D6;
const int PIN_BCLK = D7;
const int PIN_DIN = D10;

void setupI2S(){
  i2s_config_t cfg = {};
  cfg.mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX);
  cfg.sample_rate = SONG_SAMPLE_RATE;
  cfg.bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT;
  cfg.channel_format = I2S_CHANNEL_FMT_ONLY_LEFT;
  cfg.communication_format = I2S_COMM_FORMAT_STAND_I2S;
  cfg.dma_buf_count = 8;
  cfg.dma_buf_len = 256;
  cfg.use_apll = false;
  cfg.tx_desc_auto_clear = true;
  i2s_pin_config_t pins = { PIN_BCLK, PIN_LRC, PIN_DIN, I2S_PIN_NO_CHANGE };
  i2s_driver_install(I2S_NUM_0, &cfg, 0, nullptr);
  i2s_set_pin(I2S_NUM_0, &pins);
}

void setup(){
  for(int p: LEDS){ pinMode(p, OUTPUT); analogWrite(p, 0); }
  setupI2S();
  for(int i=0;i<5;i++){ analogWrite(LEDS[i], 70); delay(120); }
  size_t written=0;
  i2s_write(I2S_NUM_0, song_data, song_data_len, &written, portMAX_DELAY);
  for(int i=0;i<5;i++) analogWrite(LEDS[i], 20);
}

void loop(){ delay(1000); }
