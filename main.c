#include "./include/raylib.h"
#include "./include/system_config.h"
#include "./include/video_player.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int width, height;
    getScreenResolution(&width, &height);

    char language[16];
    getSystemLanguage(language, sizeof(language));

    // Cria a janela primeiro
    InitWindow(width, height, "Insert Your Soul");
    SetWindowState(FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_ALWAYS_RUN);
    SetWindowSize(width, height);
    SetWindowPosition(0, 0);

    SetTargetFPS(60);

    // Desenha tela preta imediatamente para evitar tela branca
    BeginDrawing();
    ClearBackground(BLACK);
    EndDrawing();

    VideoPlayer vp;
    if (!VideoPlayer_Init(&vp, "assets/frames/intro/frame_%04d.png", 120, 24.0f, NULL)) {
        printf("Erro ao inicializar VideoPlayer! Verifique os arquivos.\n");
        CloseWindow();
        return -1;
    }

    float fadeAlpha = 0.0f;
    const float fadeSpeed = 0.01f;

    // Loop principal com fade in
    while (!WindowShouldClose() && !VideoPlayer_IsFinished(&vp)) {
        float delta = GetFrameTime();
        VideoPlayer_Update(&vp, delta);

        BeginDrawing();
        ClearBackground(BLACK);

        // Desenha o vídeo
        VideoPlayer_Draw(&vp, 0, 0, width, height);

        // Fade in
        if (fadeAlpha < 1.0f) {
            fadeAlpha += fadeSpeed;
            if (fadeAlpha > 1.0f) fadeAlpha = 1.0f;
            DrawRectangle(0, 0, width, height, (Color){0, 0, 0, (unsigned char)((1.0f - fadeAlpha) * 255)});
        }

        EndDrawing();
    }

    // Mantém o último frame até apertar ESC
    while (!WindowShouldClose() && !IsKeyPressed(KEY_ESCAPE)) {
        BeginDrawing();
        ClearBackground(BLACK);

        VideoPlayer_Draw(&vp, 0, 0, width, height);

        EndDrawing();
    }

    VideoPlayer_Unload(&vp);
    CloseWindow();

    return 0;
}
