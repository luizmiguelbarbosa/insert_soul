#include "include/raylib.h"
#include "include/system.h"
#include "include/video_player.h"
#include "include/intro.h"
#include "include/menu.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int width, height;

    System_Init("Insert Your Soul", &width, &height);

    VideoPlayer vp;
    if (!Intro_Play(&vp, width, height,
                    "assets/frames/intro/frame_%04d.png", 
                    120, 24.0f, "assets/audio/intro_audio.wav", 0.002f)) {
        System_Close();
        return -1;
    }

    // --- MENU ---
    Menu_Init(width, height);
    bool exitProgram = false;

    while (!WindowShouldClose() && !exitProgram) {
        MenuAction action = Menu_UpdateDraw();

        switch (action) {
            case MENU_ACTION_START:   printf("Iniciar jogo clicado!\n"); break;
            case MENU_ACTION_OPTIONS: printf("Opções clicado!\n"); break;
            case MENU_ACTION_EXIT:    exitProgram = true; break;
            default: break;
        }
    }

    Menu_Unload();
    System_Close();
    return 0;
}
