// intro.c
#include "include/intro.h"
#include "include/raylib.h"

bool Intro_Play(VideoPlayer *vp, int width, int height, const char *framesPath, int frameCount, float fps, const char *audioPath, float audioDelay) {
    if (!VideoPlayer_Init(vp, framesPath, frameCount, fps, audioPath, audioDelay)) {
        printf("Erro ao inicializar VideoPlayer! Verifique os arquivos.\n");
        return false;
    }
    HideCursor();

    float fadeAlpha = 0.0f;
    const float fadeSpeed = 0.01f;
    bool isIntroPlaying = true;

    

    while (!WindowShouldClose() && isIntroPlaying) {
        float delta = GetFrameTime();
        VideoPlayer_Update(vp, delta);

        BeginDrawing();
        ClearBackground(BLACK);
        VideoPlayer_Draw(vp, 0, 0, width, height);

        if (fadeAlpha < 1.0f) {
            fadeAlpha += fadeSpeed;
            if (fadeAlpha > 1.0f) fadeAlpha = 1.0f;
            DrawRectangle(0, 0, width, height, (Color){0,0,0,(unsigned char)((1.0f - fadeAlpha) * 255)});
        }

        EndDrawing();

        if (vp->currentFrame >= vp->frameCount - 1) {
            isIntroPlaying = false;
            ShowCursor();
        }
    }

    VideoPlayer_Unload(vp);
    return true;
}
