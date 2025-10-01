// intro.h
#ifndef INTRO_H
#define INTRO_H

#include "video_player.h"
#include "stdio.h"

bool Intro_Play(VideoPlayer *vp, int width, int height, const char *framesPath, int frameCount, float fps, const char *audioPath, float audioDelay);

#endif
