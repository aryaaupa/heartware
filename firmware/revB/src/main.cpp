#include <Arduino.h>
#include <Wire.h>
#include <LittleFS.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_LIS3DH.h>
#include <AudioFileSourceLittleFS.h>
#include <AudioGeneratorMP3.h>
#include <AudioOutputI2S.h>
#include "song_envelope.h"

constexpr uint8_t PIN_TOUCH = D0;
constexpr uint8_t PIN_LED = D1;
constexpr uint8_t PIN_BCLK = D2;
constexpr uint8_t PIN_LRCLK = D3;
constexpr uint8_t PIN_DOUT = D4;
constexpr uint8_t PIN_SDA = D5;
constexpr uint8_t PIN_SCL = D6;
constexpr uint8_t PIN_IMU_INT = D7;
constexpr size_t LED_COUNT = 12;
constexpr uint16_t TOUCH_DEBOUNCE_MS = 450;
constexpr uint32_t IDLE_DIM_MS = 15000;

Adafruit_NeoPixel pixels(LED_COUNT, PIN_LED, NEO_GRB + NEO_KHZ800);
Adafruit_LIS3DH lis;
AudioGeneratorMP3 *mp3 = nullptr;
AudioFileSourceLittleFS *file = nullptr;
AudioOutputI2S *audioOut = nullptr;

bool playing = false;
uint32_t playbackStartMs = 0;
uint32_t lastTouchMs = 0;
uint32_t lastInteractionMs = 0;

static uint32_t warmColor(uint8_t level, uint8_t phase) {
  uint8_t r = level;
  uint8_t g = (uint16_t(level) * (55 + (phase % 20))) / 255;
  uint8_t b = (uint16_t(level) * 18) / 255;
  return pixels.Color(r, g, b);
}

static void renderEnvelope(uint8_t energy) {
  const float norm = energy / 255.0f;
  const uint8_t lit = 1 + uint8_t(norm * (LED_COUNT - 1));
  const uint8_t base = 10 + uint8_t(norm * 150);
  for (size_t i = 0; i < LED_COUNT; ++i) {
    uint8_t distance = abs(int(i) - int((millis() / 90) % LED_COUNT));
    uint8_t shimmer = (distance < 2) ? 35 : 0;
    uint8_t intensity = (i < lit) ? min(255, base + shimmer) : 4;
    pixels.setPixelColor(i, warmColor(intensity, i));
  }
  pixels.show();
}

static void allOff() {
  pixels.clear();
  pixels.show();
}

static void stopSong() {
  if (mp3) mp3->stop();
  playing = false;
  allOff();
}

static bool startSong() {
  stopSong();
  if (!LittleFS.exists("/song.mp3")) {
    Serial.println("No /song.mp3 in LittleFS. Run tools/prepare_audio.py locally, then uploadfs.");
    return false;
  }
  delete mp3;
  delete file;
  delete audioOut;
  mp3 = new AudioGeneratorMP3();
  file = new AudioFileSourceLittleFS("/song.mp3");
  audioOut = new AudioOutputI2S();
  audioOut->SetPinout(PIN_BCLK, PIN_LRCLK, PIN_DOUT);
  audioOut->SetGain(0.34f);
  if (!mp3->begin(file, audioOut)) return false;
  playbackStartMs = millis();
  lastInteractionMs = millis();
  playing = true;
  return true;
}

static void bootAnimation() {
  for (size_t i = 0; i < LED_COUNT; ++i) {
    pixels.setPixelColor(i, warmColor(80, i));
    pixels.show();
    delay(35);
  }
  delay(120);
  allOff();
}

static bool touched() {
  static uint32_t baseline = 0;
  uint32_t v = touchRead(PIN_TOUCH);
  if (baseline == 0) baseline = v;
  baseline = (baseline * 31 + v) / 32;
  bool active = (v + max<uint32_t>(8, baseline / 7)) < baseline;
  if (active && millis() - lastTouchMs > TOUCH_DEBOUNCE_MS) {
    lastTouchMs = millis();
    return true;
  }
  return false;
}

void setup() {
  Serial.begin(115200);
  delay(250);
  pixels.begin();
  pixels.setBrightness(180);
  allOff();

  Wire.begin(PIN_SDA, PIN_SCL);
  pinMode(PIN_IMU_INT, INPUT);
  if (lis.begin(0x18, &Wire) || lis.begin(0x19, &Wire)) {
    lis.setRange(LIS3DH_RANGE_4_G);
    lis.setDataRate(LIS3DH_DATARATE_10_HZ);
    Serial.println("LIS3DH online");
  } else {
    Serial.println("LIS3DH not detected; audio/touch still available");
  }

  if (!LittleFS.begin(true)) Serial.println("LittleFS mount failed");
  bootAnimation();
  lastInteractionMs = millis();
}

void loop() {
  if (touched()) {
    if (playing) stopSong();
    else startSong();
  }

  if (playing && mp3) {
    if (mp3->isRunning()) {
      if (!mp3->loop()) stopSong();
      uint32_t elapsedMs = millis() - playbackStartMs;
      uint32_t idx = (uint64_t(elapsedMs) * SONG_ENV_HZ) / 1000ULL;
      uint8_t e = idx < SONG_ENV_LEN ? SONG_ENV[idx] : 32;
      renderEnvelope(e);
    } else {
      stopSong();
    }
  } else if (millis() - lastInteractionMs > IDLE_DIM_MS) {
    allOff();
  }

  if (!playing && digitalRead(PIN_IMU_INT)) {
    lastInteractionMs = millis();
    for (size_t i = 0; i < LED_COUNT; ++i) pixels.setPixelColor(i, warmColor(18, i));
    pixels.show();
  }

  delay(2);
}
