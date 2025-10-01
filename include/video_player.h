#ifndef VIDEO_PLAYER_H
#define VIDEO_PLAYER_H

#include "raylib.h"

typedef struct VideoPlayer {
    Texture2D *frames;       // array de frames (texturas)
    int frameCount;          // total de frames
    int currentFrame;        // índice do frame atual
    float frameTime;         // tempo entre frames (ex: 1/24 para 24 fps)
    float timer;             // contador de tempo para avançar frame

    Music music;             // áudio
} VideoPlayer;

// Inicializa o player, carregando frames do diretório e o áudio
bool VideoPlayer_Init(VideoPlayer *vp, const char *framesPathFormat, int frameCount, float fps, const char *audioPath);

// Atualiza (baseado no delta time)
void VideoPlayer_Update(VideoPlayer *vp, float delta);

// Atualiza sincronizando diretamente pelo áudio
void VideoPlayer_UpdateSync(VideoPlayer *vp);

// Renderiza o frame atual na tela (pos, width, height)
void VideoPlayer_Draw(VideoPlayer *vp, int x, int y, int width, int height);

// Libera recursos
void VideoPlayer_Unload(VideoPlayer *vp);

// Retorna true se terminou (último frame e áudio terminou)
bool VideoPlayer_IsFinished(VideoPlayer *vp);

#endif // VIDEO_PLAYER_H
