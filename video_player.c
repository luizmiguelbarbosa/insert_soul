#include "video_player.h"
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 4

static Texture2D buffer[BUFFER_SIZE];
static char **framePaths;

bool VideoPlayer_Init(VideoPlayer *vp, const char *framesPathFormat, int frameCount, float fps, const char *audioPath, float audioDelay) {
    vp->frameCount = frameCount;
    vp->currentFrame = 0;
    vp->frameTime = 1.0f / fps;
    vp->timer = 0.0f;
    vp->audioDelay = audioDelay;
    vp->audioPlayed = false;

    // Aloca caminhos
    framePaths = (char**)malloc(sizeof(char*) * frameCount);
    for (int i = 0; i < frameCount; i++) {
        framePaths[i] = (char*)malloc(256);
        sprintf(framePaths[i], framesPathFormat, i + 1);
    }

    // Carrega apenas o primeiro frame
    Image img = LoadImage(framePaths[0]);
    if (!img.data) {
        printf("Erro ao carregar frame %s\n", framePaths[0]);
        return false;
    }
    buffer[0] = LoadTextureFromImage(img);
    UnloadImage(img);

    // Zera os outros do buffer
    for (int i = 1; i < BUFFER_SIZE; i++) buffer[i] = (Texture2D){0};

    // Inicializa áudio
    if (audioPath != NULL) {
        vp->music = LoadMusicStream(audioPath);
    } else {
        vp->music = (Music){0};
        vp->audioPlayed = true;
    }

    return true;
}

void VideoPlayer_Update(VideoPlayer *vp, float delta) {
    vp->timer += delta;

    // Áudio
    if (!vp->audioPlayed) {
        vp->audioDelay -= delta;
        if (vp->audioDelay <= 0.0f) {
            PlayMusicStream(vp->music);
            vp->audioPlayed = true;
        }
    }
    if (vp->audioPlayed) UpdateMusicStream(vp->music);

    // Frames
    while (vp->timer >= vp->frameTime) {
        vp->timer -= vp->frameTime;

        int oldIndex = vp->currentFrame % BUFFER_SIZE;
        vp->currentFrame++;

        // Descarrega frame antigo
        if (vp->currentFrame > 0 && vp->currentFrame - 1 < vp->frameCount) {
            UnloadTexture(buffer[oldIndex]);
        }

        // Carrega próximo frame se existir
        int nextFrame = vp->currentFrame + BUFFER_SIZE - 1;
        if (nextFrame < vp->frameCount) {
            Image img = LoadImage(framePaths[nextFrame]);
            if (!img.data) {
                printf("Erro ao carregar frame %s\n", framePaths[nextFrame]);
                continue;
            }
            buffer[oldIndex] = LoadTextureFromImage(img);
            UnloadImage(img);
        }
    }
}

void VideoPlayer_Draw(VideoPlayer *vp, int x, int y, int width, int height) {
    if (vp->currentFrame >= vp->frameCount) return;

    int idx = vp->currentFrame % BUFFER_SIZE;
    Texture2D tex = buffer[idx];

    float scaleX = (float)width / tex.width;
    float scaleY = (float)height / tex.height;
    float scale = (scaleX < scaleY) ? scaleX : scaleY;

    int drawWidth = tex.width * scale;
    int drawHeight = tex.height * scale;
    int offsetX = (width - drawWidth) / 2;
    int offsetY = (height - drawHeight) / 2;

    DrawTexturePro(tex,
                   (Rectangle){0,0,tex.width,tex.height},
                   (Rectangle){offsetX,offsetY,drawWidth,drawHeight},
                   (Vector2){0,0}, 0.0f, WHITE);
}

void VideoPlayer_Unload(VideoPlayer *vp) {
    for (int i = 0; i < BUFFER_SIZE; i++) {
        if (buffer[i].id != 0) UnloadTexture(buffer[i]);
    }

    for (int i = 0; i < vp->frameCount; i++) free(framePaths[i]);
    free(framePaths);

    if (vp->audioPlayed) StopMusicStream(vp->music);
    UnloadMusicStream(vp->music);
}

bool VideoPlayer_IsFinished(VideoPlayer *vp) {
    return (vp->currentFrame >= vp->frameCount - 1 && (!vp->audioPlayed || !IsMusicStreamPlaying(vp->music)));
}
