#include "OrbRenderer.h"
#include "Display.h"
#include "OrbitFX.h"
#include "OrbitFace.h"
#include <Arduino.h>
#include <math.h>

static OrbState current = ORB_IDLE;

//====================================================
// Animation Engine
//====================================================

static OrbitFX radiusFX(36.0f,0.14f);
static OrbitFX glowFX(48.0f,0.10f);
static OrbitFX highlightFX(24.0f,0.18f);

static OrbitFX xFX(120.0f,0.08f);
static OrbitFX yFX(90.0f,0.08f);

static float rotation = 0.0f;

static bool initialized = false;

//====================================================
// Colors
//====================================================

static uint16_t orbColor = ST77XX_CYAN;

static uint16_t glowColor = ST77XX_DARKGREY;

static uint16_t highlightColor = ST77XX_WHITE;

//====================================================
// Private Helpers
//====================================================

static void updateTargets()
{

    switch(current)
    {

        case ORB_IDLE:

            radiusFX.to(36);
            glowFX.to(48);
            highlightFX.to(24);

            orbColor = ST77XX_CYAN;

            break;

        case ORB_LISTENING:

            radiusFX.to(42);
            glowFX.to(60);
            highlightFX.to(28);

            orbColor = ST77XX_CYAN;

            break;

        case ORB_THINKING:

            radiusFX.to(35);
            glowFX.to(55);
            highlightFX.to(22);

            orbColor = ST77XX_YELLOW;

            break;

        case ORB_SPEAKING:

            radiusFX.to(40);
            glowFX.to(62);
            highlightFX.to(30);

            orbColor = ST77XX_CYAN;

            break;

        case ORB_SLEEP:

            radiusFX.to(28);
            glowFX.to(38);
            highlightFX.to(18);

            orbColor = ST77XX_BLUE;

            break;

        case ORB_ERROR:

            radiusFX.to(38);
            glowFX.to(58);
            highlightFX.to(24);

            orbColor = ST77XX_RED;

            break;

    }

}//====================================================
// Public
//====================================================

void Orb_begin()
{
    if(initialized)
        return;

    radiusFX.set(36);

    glowFX.set(48);

    highlightFX.set(24);

    xFX.set(120);

    yFX.set(90);

    initialized = true;
}

void Orb_setState(OrbState state)
{
    if(current == state)
        return;

    current = state;

    updateTargets();
}

void Orb_update()
{
    if(!initialized)
        return;

    radiusFX.update();

    glowFX.update();

    highlightFX.update();

    xFX.update();

    yFX.update();

    rotation += 0.03f;

    if(rotation > TWO_PI)
        rotation = 0.0f;

    // Breathing while idle

    if(current == ORB_IDLE)
    {
        radiusFX.to(36.0f + sin(rotation) * 1.8f);
    }

    // Listening pulse

    if(current == ORB_LISTENING)
    {
        glowFX.to(58.0f + sin(rotation * 3.0f) * 4.0f);
    }

    // Speaking pulse

    if(current == ORB_SPEAKING)
    {
        radiusFX.to(40.0f + sin(rotation * 5.0f) * 3.0f);

        glowFX.to(62.0f + sin(rotation * 5.0f) * 5.0f);
    }

    // Thinking wobble

    if(current == ORB_THINKING)
    {
        highlightFX.to(22.0f + sin(rotation * 2.0f));
    }

    // Sleep

    if(current == ORB_SLEEP)
    {
        radiusFX.to(28.0f + sin(rotation * 0.4f));
    }

    // Error

    if(current == ORB_ERROR)
    {
        glowFX.to(60.0f + sin(rotation * 8.0f) * 6.0f);
    }
}
void Orb_draw(int x, int y)
{
    auto &tft = Display_getTFT();

    //====================================================
    // Clear Previous Frame
    //====================================================

    tft.fillCircle(
        (int)xFX.value,
        (int)yFX.value,
        72,
        ST77XX_BLACK);

    //====================================================
    // Animated Glow
    //====================================================

    uint16_t glowColor = ST77XX_CYAN;

    switch(current)
    {
        case ORB_ERROR:
            glowColor = ST77XX_RED;
            break;

        case ORB_THINKING:
            glowColor = ST77XX_YELLOW;
            break;

        case ORB_SLEEP:
            glowColor = ST77XX_BLUE;
            break;

        default:
            glowColor = ST77XX_CYAN;
            break;
    }

    for(int i = 8; i > 0; i--)
    {
        tft.drawCircle(
            (int)xFX.value,
            (int)yFX.value,
            (int)glowFX.value - i,
            glowColor);
    }

    //====================================================
    // Orbit Face Image
    //====================================================

    tft.drawRGBBitmap(
        (int)xFX.value - OrbitFaceWidth / 2,
        (int)yFX.value - OrbitFaceHeight / 2,
        OrbitFace,
        OrbitFaceWidth,
        OrbitFaceHeight);

    //====================================================
    // Thinking Indicator
    //====================================================

    if(current == ORB_THINKING)
    {
        int rx =
            (int)xFX.value +
            cos(rotation * 3.0f) *
            (glowFX.value + 8);

        int ry =
            (int)yFX.value +
            sin(rotation * 3.0f) *
            (glowFX.value + 8);

        tft.fillCircle(
            rx,
            ry,
            4,
            ST77XX_YELLOW);
    }

    //====================================================
    // Listening Ring
    //====================================================

    if(current == ORB_LISTENING)
    {
        tft.drawCircle(
            (int)xFX.value,
            (int)yFX.value,
            (int)glowFX.value + 4,
            ST77XX_WHITE);
    }

    //====================================================
    // Speaking Ring
    //====================================================

    if(current == ORB_SPEAKING)
    {
        tft.drawCircle(
            (int)xFX.value,
            (int)yFX.value,
            (int)glowFX.value + 8,
            ST77XX_WHITE);
    }

    //====================================================
    // Error Ring
    //====================================================

    if(current == ORB_ERROR)
    {
        tft.drawCircle(
            (int)xFX.value,
            (int)yFX.value,
            (int)glowFX.value + 8,
            ST77XX_RED);
    }
}