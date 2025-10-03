#include "menu.h"
#include "raylib.h"
#include <stdio.h>

static int screenWidth = 0;
static int screenHeight = 0;

void Menu_Init(int width, int height) {
    screenWidth = width;
    screenHeight = height;
}

MenuAction Menu_UpdateDraw(void) {
    MenuAction action = MENU_ACTION_NONE;

    BeginDrawing();
    ClearBackground((Color){30,30,30,255}); // fundo cinza escuro

    int buttonWidth = 200;
    int buttonHeight = 50;
    int spacing = 20;
    int startY = screenHeight / 2 - (buttonHeight * 3 + spacing * 2) / 2;
    int centerX = screenWidth / 2 - buttonWidth / 2;

    // Botão Iniciar
    Rectangle startBtn = { (float)centerX, (float)startY, (float)buttonWidth, (float)buttonHeight };
    if (CheckCollisionPointRec(GetMousePosition(), startBtn)) {
        DrawRectangleRec(startBtn, (Color){70,70,70,255});
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) action = MENU_ACTION_START;
    } else DrawRectangleRec(startBtn, (Color){50,50,50,255});
    DrawText("Iniciar", centerX + 60, startY + 15, 20, RAYWHITE);

    // Botão Opções
    Rectangle optionsBtn = { (float)centerX, (float)(startY + buttonHeight + spacing), (float)buttonWidth, (float)buttonHeight };
    if (CheckCollisionPointRec(GetMousePosition(), optionsBtn)) {
        DrawRectangleRec(optionsBtn, (Color){70,70,70,255});
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) action = MENU_ACTION_OPTIONS;
    } else DrawRectangleRec(optionsBtn, (Color){50,50,50,255});
    DrawText("Opções", centerX + 60, startY + buttonHeight + spacing + 15, 20, RAYWHITE);

    // Botão Sair
    Rectangle exitBtn = { (float)centerX, (float)(startY + (buttonHeight + spacing) * 2), (float)buttonWidth, (float)buttonHeight };
    if (CheckCollisionPointRec(GetMousePosition(), exitBtn)) {
        DrawRectangleRec(exitBtn, (Color){70,70,70,255});
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) action = MENU_ACTION_EXIT;
    } else DrawRectangleRec(exitBtn, (Color){50,50,50,255});
    DrawText("Sair", centerX + 80, startY + (buttonHeight + spacing) * 2 + 15, 20, RAYWHITE);

    EndDrawing();
    return action;
}

void Menu_Unload(void) {
    // Se houver recursos a liberar, adicionar aqui
}
