#include "./include/raylib.h"
#include "./include/system_config.h"
#include "./include/video_player.h"
#include "./include/menu.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int width, height;
    getScreenResolution(&width, &height);

    InitWindow(width, height, "Insert Your Soul");
    SetWindowState(FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_ALWAYS_RUN);
    SetWindowSize(width, height);
    SetWindowPosition(0, 0);
    SetExitKey(KEY_NULL);
    SetTargetFPS(60);

    // Limpa a tela com preto antes do loop
    BeginDrawing();
    ClearBackground(BLACK);
    EndDrawing();

    HideCursor(); // Esconde o cursor durante a introdução

    // --- INTRO ---
    VideoPlayer vp;
    if (!VideoPlayer_Init(&vp, "assets/frames/intro/frame_%04d.png", 120, 24.0f, NULL)) {
        printf("Erro ao inicializar VideoPlayer! Verifique os arquivos.\n");
        CloseWindow();
        return -1;
    }

    float fadeAlpha = 0.0f;
    const float fadeSpeed = 0.01f;
    bool isIntroPlaying = true;

    while (!WindowShouldClose() && isIntroPlaying) {
        float delta = GetFrameTime();
        VideoPlayer_Update(&vp, delta);

        BeginDrawing();
        ClearBackground(BLACK);
        VideoPlayer_Draw(&vp, 0, 0, width, height);

        if (fadeAlpha < 1.0f) {
            fadeAlpha += fadeSpeed;
            if (fadeAlpha > 1.0f) fadeAlpha = 1.0f;
            DrawRectangle(0, 0, width, height, (Color){0, 0, 0, (unsigned char)((1.0f - fadeAlpha) * 255)});
        }

        EndDrawing();

        if (VideoPlayer_IsFinished(&vp)) {
            isIntroPlaying = false;
            ShowCursor(); // Exibe o cursor quando o vídeo termina
        }
    }

    VideoPlayer_Unload(&vp);

    // --- MENU ---
    Menu_Init(width, height);

    bool exitProgram = false;

    while (!WindowShouldClose() && !exitProgram) {
        // Atualiza e desenha o menu
        MenuAction action = Menu_UpdateDraw();

        switch (action) {
            case MENU_ACTION_START:
                printf("Iniciar jogo clicado!\n");
                break;

            case MENU_ACTION_OPTIONS:
                printf("Opções clicado!\n");
                break;

            case MENU_ACTION_EXIT:
                exitProgram = true; // Sai do programa
                break;

            default:
                break;
        }
    }

    Menu_Unload();
    CloseWindow();
    return 0;
}
