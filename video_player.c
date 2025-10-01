#include "include/video_player.h"
#include <stdio.h>
#include <stdlib.h>

bool VideoPlayer_Init(VideoPlayer *vp, const char *framesPathFormat, int frameCount, float fps, const char *audioPath, float audioDelay) {
    vp->frames = (Texture2D *)malloc(sizeof(Texture2D) * frameCount);
    if (!vp->frames) return false;

    vp->frameCount = frameCount;
    vp->currentFrame = 0;
    vp->frameTime = 1.0f / fps;
    vp->timer = 0.0f;

    // Delay do áudio
    vp->audioDelay = audioDelay;
    vp->audioPlayed = false;

    // Carregar frames
    for (int i = 0; i < frameCount; i++) {
        char filename[256];
        sprintf(filename, framesPathFormat, i + 1);  // assume nomes frame_0001.png etc
        Image img = LoadImage(filename);
        if (img.data == NULL) {
            printf("Erro ao carregar frame %s\n", filename);
            for (int j = 0; j < i; j++) {
                UnloadTexture(vp->frames[j]);
            }
            free(vp->frames);
            return false;
        }
        vp->frames[i] = LoadTextureFromImage(img);
        UnloadImage(img);
    }

    // Inicializa áudio mas não toca imediatamente
    if (audioPath != NULL) {
        vp->music = LoadMusicStream(audioPath);
    } else {
        vp->music = (Music){0};
        vp->audioPlayed = true; // sem áudio, considera "já tocado"
    }

    return true;
}

void VideoPlayer_Update(VideoPlayer *vp, float delta) {
    // Atualiza timer dos frames
    vp->timer += delta;
    while (vp->timer >= vp->frameTime) {
        vp->currentFrame++;
        vp->timer -= vp->frameTime;
    }
    if (vp->currentFrame >= vp->frameCount) {
        vp->currentFrame = vp->frameCount - 1; // congela no último frame
    }

    // Atualiza áudio com delay
    if (!vp->audioPlayed) {
        vp->audioDelay -= delta;
        if (vp->audioDelay <= 0.0f) {
            PlayMusicStream(vp->music);
            vp->audioPlayed = true;
        }
    }

    if (vp->audioPlayed) {
        UpdateMusicStream(vp->music);
    }
}

void VideoPlayer_Draw(VideoPlayer *vp, int x, int y, int width, int height) {
    if (vp->currentFrame >= vp->frameCount) return;

    Texture2D tex = vp->frames[vp->currentFrame];

    // Calcula escala para manter aspecto
    float scaleX = (float)width / tex.width;
    float scaleY = (float)height / tex.height;
    float scale = (scaleX < scaleY) ? scaleX : scaleY;

    int drawWidth = tex.width * scale;
    int drawHeight = tex.height * scale;
    int offsetX = (width - drawWidth) / 2;
    int offsetY = (height - drawHeight) / 2;

    DrawTexturePro(tex,
                   (Rectangle){0, 0, tex.width, tex.height},
                   (Rectangle){offsetX, offsetY, drawWidth, drawHeight},
                   (Vector2){0, 0}, 0.0f, WHITE);
}

void VideoPlayer_Unload(VideoPlayer *vp) {
    for (int i = 0; i < vp->frameCount; i++) {
        UnloadTexture(vp->frames[i]);
    }
    free(vp->frames);

    if (vp->audioPlayed) {
        StopMusicStream(vp->music);
    }
    UnloadMusicStream(vp->music);
}

bool VideoPlayer_IsFinished(VideoPlayer *vp) {
    return (vp->currentFrame >= vp->frameCount - 1);
}
