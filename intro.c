#include "include/intro.h"
#include "include/raylib.h"

bool Intro_Play(VideoPlayer *vp, int width, int height, const char *framesPath, int frameCount, float fps, const char *audioPath, float audioDelay) {
    if (!VideoPlayer_Init(vp, framesPath, frameCount, fps, audioPath, audioDelay)) {
        printf("Erro ao inicializar VideoPlayer!\n");
        return false;
    }

    HideCursor();

    // Desenha primeiro frame antes do loop para evitar travamento
    BeginDrawing();
    ClearBackground(BLACK);
    VideoPlayer_Draw(vp, 0, 0, width, height);
    EndDrawing();

    float fadeAlpha = 0.0f;
    const float fadeSpeed = 0.01f;

    while (!WindowShouldClose() && !VideoPlayer_IsFinished(vp)) {
        float delta = GetFrameTime();
        VideoPlayer_Update(vp, delta);

        BeginDrawing();
        ClearBackground(BLACK);
        VideoPlayer_Draw(vp, 0, 0, width, height);

        if (fadeAlpha < 1.0f) {
            fadeAlpha += fadeSpeed;
            if (fadeAlpha > 1.0f) fadeAlpha = 1.0f;
            DrawRectangle(0,0,width,height,(Color){0,0,0,(unsigned char)((1.0f-fadeAlpha)*255)});
        }

        EndDrawing();
    }

    ShowCursor();
    VideoPlayer_Unload(vp);
    return true;
}
