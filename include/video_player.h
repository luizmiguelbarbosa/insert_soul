#ifndef VIDEO_PLAYER_H
#define VIDEO_PLAYER_H

#include "raylib.h"
#include <stdbool.h>

typedef struct VideoPlayer {
    int frameCount;          // total de frames
    int currentFrame;        // índice do frame atual
    float frameTime;         // tempo entre frames (ex: 1/24 para 24 fps)
    float timer;             // contador de tempo para avançar frame

    Music music;             // áudio
    float audioDelay;        // delay antes do áudio
    bool audioPlayed;        // se áudio já começou
} VideoPlayer;

// Inicializa player (buffer de 4 frames)
bool VideoPlayer_Init(VideoPlayer *vp, const char *framesPathFormat, int frameCount, float fps, const char *audioPath, float audioDelay);

// Atualiza player (frames + áudio)
void VideoPlayer_Update(VideoPlayer *vp, float delta);

// Desenha frame atual
void VideoPlayer_Draw(VideoPlayer *vp, int x, int y, int width, int height);

// Libera recursos
void VideoPlayer_Unload(VideoPlayer *vp);

// Retorna true se terminou (último frame e áudio)
bool VideoPlayer_IsFinished(VideoPlayer *vp);

#endif // VIDEO_PLAYER_H
