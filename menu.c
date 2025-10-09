#include "menu.h"
#include "raylib.h"
#include <stdio.h>
#include <stdbool.h>

static int screenWidth = 0;
static int screenHeight = 0;

// Background
static Texture2D bg;

// Personagem
#define NUM_FRAMES 10
static Texture2D characterFrames[NUM_FRAMES];
static int currentFrame = 0;
static float frameTimer = 0.0f;
static float frameTime = 1.0f / 12.0f; // 12 fps
static bool exitAnimation = false;

// Música
static Music menuMusic;

// Botões
#define BUTTON_COUNT 6
static Rectangle buttons[BUTTON_COUNT];
static const char *buttonText[BUTTON_COUNT] = {
    "New Game", "Continue", "Load Settings", "Credits", "Language", "Voice"
};
static float btnAnim[BUTTON_COUNT];
static Rectangle exitButton;
static float exitAnim = 1.0f;

void Menu_Init(int width, int height) {
    screenWidth = width;
    screenHeight = height;

    // Background
    bg = LoadTexture("assets/bg.png");

    // Personagem
    char path[64];
    for (int i = 0; i < NUM_FRAMES; i++) {
        sprintf(path, "assets/character/frame%d.png", i+1);
        characterFrames[i] = LoadTexture(path);
    }

    // Botões principais
    int buttonWidth = 200;
    int buttonHeight = 50;
    int spacing = 20;
    int startY = 150; // abaixo do título
    int menuX = 50;
    for (int i = 0; i < BUTTON_COUNT; i++) {
        buttons[i] = (Rectangle){menuX, startY + i*(buttonHeight + spacing), buttonWidth, buttonHeight};
        btnAnim[i] = 1.0f;
    }

    // Botão Exit
    exitButton = (Rectangle){menuX, screenHeight - 100, buttonWidth, buttonHeight};

    // Música
    menuMusic = LoadMusicStream("assets/audio/menu_song.ogg");
    SetMusicVolume(menuMusic, 1.0f); // volume máximo
    PlayMusicStream(menuMusic);
}

MenuAction Menu_UpdateDraw(float deltaTime) {
    MenuAction action = MENU_ACTION_NONE;
    Vector2 mouse = GetMousePosition();

    // Atualiza música
    UpdateMusicStream(menuMusic);

    // Atualizar frame do personagem
    frameTimer += deltaTime;
    if (frameTimer >= frameTime) {
        frameTimer -= frameTime;
        currentFrame = (currentFrame + 1) % NUM_FRAMES;
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);

    // Camada 0: Background
    DrawTexture(bg, 0, 0, WHITE);

    // Camada 1: Personagem animado
    int characterX = screenWidth - 300;
    int characterY = screenHeight/2 - characterFrames[currentFrame].height/2;
    DrawTexture(characterFrames[currentFrame], characterX, characterY, WHITE);

    // Camada 2: Título
    DrawText("MEU JOGO", 50, 50, 30, DARKGRAY);

    // Camada 3: Botões principais
    for (int i = 0; i < BUTTON_COUNT; i++) {
        bool hovered = CheckCollisionPointRec(mouse, buttons[i]);
        // Crescimento limitado a 1.1x
        if (hovered && btnAnim[i] < 1.1f) btnAnim[i] += 0.05f;
        if (!hovered && btnAnim[i] > 1.0f) btnAnim[i] -= 0.05f;

        float w = buttons[i].width * btnAnim[i];
        float h = buttons[i].height * btnAnim[i];
        float x = buttons[i].x + (buttons[i].width - w)/2;
        float y = buttons[i].y + (buttons[i].height - h)/2;

        DrawRectangleRec((Rectangle){x, y, w, h}, hovered ? (Color){70,70,70,255} : (Color){50,50,50,255});
        int textWidth = MeasureText(buttonText[i], 20);
        DrawText(buttonText[i], x + (w - textWidth)/2, y + (h - 20)/2, 20, RAYWHITE);

        if (hovered && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            switch(i) {
                case 0: action = MENU_ACTION_START; break;
                case 1: action = MENU_ACTION_CONTINUE; break;
                case 2: action = MENU_ACTION_LOADSETTINGS; break;
                case 3: action = MENU_ACTION_CREDITS; break;
                case 4: action = MENU_ACTION_LANGUAGE; break;
                case 5: action = MENU_ACTION_VOICE; break;
            }
        }
    }

    // Botão Exit
    bool exitHovered = CheckCollisionPointRec(mouse, exitButton);
    if (exitHovered && exitAnim < 1.1f) exitAnim += 0.05f;
    if (!exitHovered && exitAnim > 1.0f) exitAnim -= 0.05f;

    float ew = exitButton.width * exitAnim;
    float eh = exitButton.height * exitAnim;
    float ex = exitButton.x + (exitButton.width - ew)/2;
    float ey = exitButton.y + (exitButton.height - eh)/2;
    DrawRectangleRec((Rectangle){ex, ey, ew, eh}, exitHovered ? (Color){120,0,0,255} : (Color){80,0,0,255});
    int textWidthExit = MeasureText("Exit", 20);
    DrawText("Exit", ex + (ew - textWidthExit)/2, ey + (eh - 20)/2, 20, RAYWHITE);

    if (exitHovered && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
        action = MENU_ACTION_EXIT;
        exitAnimation = true;
    }

    EndDrawing();
    return action;
}

void Menu_Unload(void) {
    UnloadTexture(bg);
    for (int i = 0; i < NUM_FRAMES; i++) UnloadTexture(characterFrames[i]);
    StopMusicStream(menuMusic);
    UnloadMusicStream(menuMusic);
}
