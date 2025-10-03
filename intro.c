#include "intro.h"
#include <math.h>

bool Intro_Play(VideoPlayer *vp, int width, int height, const char *framesPath, int frameCount, float fps, const char *audioPath, float loadingTime) {
    if (!VideoPlayer_Init(vp, framesPath, frameCount, fps, audioPath)) return false;

    HideCursor();

    // Loop do vídeo
    while (!WindowShouldClose() && !VideoPlayer_IsFinished(vp)) {
        float delta = GetFrameTime();
        VideoPlayer_Update(vp, delta);

        BeginDrawing();
        ClearBackground(BLACK);
        VideoPlayer_Draw(vp, 0, 0, width, height);
        EndDrawing();
    }

    // Tela de carregamento com círculo girando no canto inferior direito
    float timer = 1.5f;
    float angle = 0.0f;
    int radius = 25;
    int numDots = 12;
    float speed = 360.0f;

    int centerX = width - 50;
    int centerY = height - 50;

    while (!WindowShouldClose() && timer < loadingTime) {
        float delta = GetFrameTime();
        timer += delta;
        angle += speed * delta;

        BeginDrawing();
        ClearBackground(BLACK);

        for (int i = 0; i < numDots; i++) {
            float a = angle + i * (360.0f / numDots);
            float rad = a * (3.1415926f / 180.0f);
            int dotX = centerX + (int)(radius * cos(rad));
            int dotY = centerY + (int)(radius * sin(rad));
            DrawCircle(dotX, dotY, 4, WHITE);
        }

        EndDrawing();
    }

    ShowCursor();
    VideoPlayer_Unload(vp);
    return true;
}
