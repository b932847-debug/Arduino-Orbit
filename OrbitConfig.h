#pragma once

//======================================================
// Orbit OS Beta 3 Configuration
// Uncomment ONE option from each section.
//======================================================

//-------------------------
// General
//-------------------------
#define ORBIT_VERSION "Beta 3"
#define ORBIT_NAME    "Orbit"

#define SCREEN_WIDTH  240
#define SCREEN_HEIGHT 320

//-------------------------
// AI Backend
//-------------------------
#define AI_GEMINI
//#define AI_OPENAI
//#define AI_OLLAMA

//-------------------------
// Speech-to-Text
//-------------------------
#define STT_GOOGLE
//#define STT_OPENAI
//#define STT_WHISPER_LOCAL
//#define STT_VOSK

//-------------------------
// Text-to-Speech
//-------------------------
#define TTS_GOOGLE
//#define TTS_OPENAI
//#define TTS_ELEVENLABS
//#define TTS_PIPER

//-------------------------
// Wake Word
//-------------------------
//#define WAKEWORD_PORCUPINE
//#define WAKEWORD_OPENWAKEWORD
//#define WAKEWORD_CUSTOM

//-------------------------
// Cellular Modem
//-------------------------
#define CELLULAR_A7670
//#define CELLULAR_SIM7600
//#define CELLULAR_SIM7080
//#define CELLULAR_BG95

//-------------------------
// Touch Controller
//-------------------------
#define TOUCH_GT911
//#define TOUCH_FT6236
//#define TOUCH_CST816
//#define TOUCH_XPT2046

//-------------------------
// Audio Output
//-------------------------
#define AUDIO_MAX98357A
//#define AUDIO_PCM5102A
//#define AUDIO_INTERNAL_DAC

//-------------------------
// Connectivity
//-------------------------
#define WIFI_ENABLED
#define OTA_ENABLED
#define BATTERY_MONITOR
#define GPS_ENABLED

//======================================================
// Hardware Pins
// Edit these once your wiring is finalized.
//======================================================

// UART (A7670)
#define CELL_TX_PIN 17
#define CELL_RX_PIN 16
//#define CELL_PWRKEY_PIN 4
//#define CELL_RESET_PIN 5

// I2C (GT911)
#define I2C_SDA_PIN 21
#define I2C_SCL_PIN 22
//#define TOUCH_INT_PIN 39
//#define TOUCH_RST_PIN 38

// I2S (MAX98357A)
//#define I2S_BCLK_PIN 26
//#define I2S_LRC_PIN 25
//#define I2S_DOUT_PIN 27

// Microphone
#define MIC_PIN 34

// Battery Monitor
//#define BATTERY_PIN 35
