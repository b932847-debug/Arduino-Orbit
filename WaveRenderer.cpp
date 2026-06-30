#include "WaveRenderer.h"
#include "Display.h"

#include <Arduino.h>
#include <math.h>

//====================================================
// Configuration
//====================================================

static const uint8_t SAMPLE_COUNT = 64;

static const float SMOOTHING = 0.15f;

static const int VOICE_THRESHOLD = 1800;

//====================================================
// Audio
//====================================================

static uint8_t micPin = 34;

static int rawSamples[SAMPLE_COUNT];

static float filteredSamples[SAMPLE_COUNT];

static uint8_t head = 0;

static float currentLevel = 0.0f;

static float idleWave = 0.0f;

static bool speaking = false;

//====================================================
// Private Helpers
//====================================================

static float normalize(int sample)
{
    float v = sample / 4095.0f;

    v = (v - 0.5f) * 2.0f;

    if(v > 1.0f)
        v = 1.0f;

    if(v < -1.0f)
        v = -1.0f;

    return v;
}

static void pushSample(int sample)
{
    rawSamples[head] = sample;

    filteredSamples[head] +=
        (sample - filteredSamples[head]) *
        SMOOTHING;

    head++;

    if(head >= SAMPLE_COUNT)
        head = 0;
}

static float sampleAt(int index)
{
    if(index < 0)
        index += SAMPLE_COUNT;

    if(index >= SAMPLE_COUNT)
        index %= SAMPLE_COUNT;

    return normalize(
        (int)filteredSamples[index]);
}

//====================================================
// Public
//====================================================

void Wave_begin(uint8_t pin)
{
    micPin = pin;

    pinMode(micPin, INPUT);

    for(int i = 0; i < SAMPLE_COUNT; i++)
    {
        rawSamples[i] = 0;
        filteredSamples[i] = 0.0f;
    }

    head = 0;

    currentLevel = 0.0f;

    idleWave = 0.0f;

    speaking = false;
}

void Wave_update()
{
    int sample = analogRead(micPin);

    pushSample(sample);

    currentLevel +=
        (sample - currentLevel) *
        0.08f;

    speaking =
        currentLevel >
        VOICE_THRESHOLD;

    idleWave += 0.08f;

    if(idleWave > TWO_PI)
        idleWave = 0.0f;
}

int Wave_level()
{
    return (int)currentLevel;
}

bool Wave_voiceDetected()
{
    return speaking;
}
void Wave_draw(int x, int y, int width, int height)
{
    auto &tft = Display_getTFT();

    // Clear waveform area
    tft.fillRect(
        x,
        y,
        width,
        height,
        ST77XX_BLACK);

    int centerY = y + height / 2;

    int previousX = x;
    int previousY = centerY;

    for(int i = 0; i < width; i++)
    {
        float sample;

        if(speaking)
        {
            int index =
                (head + i * SAMPLE_COUNT / width) %
                SAMPLE_COUNT;

            sample = sampleAt(index);
        }
        else
        {
            sample =
                sin(
                    idleWave +
                    (float)i * 0.18f
                ) * 0.12f;
        }

        int waveY =
            centerY -
            sample *
            (height * 0.42f);

        // Main waveform
        tft.drawLine(
            previousX,
            previousY,
            x + i,
            waveY,
            ST77XX_CYAN);

        // Glow
        tft.drawPixel(
            x + i,
            waveY - 1,
            ST77XX_WHITE);

        tft.drawPixel(
            x + i,
            waveY + 1,
            ST77XX_WHITE);

        previousX = x + i;
        previousY = waveY;
    }

    // Center line
    tft.drawFastHLine(
        x,
        centerY,
        width,
        ST77XX_DARKGREY);
}