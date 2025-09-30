#include "./include/raylib.h"
#include "./include/system_config.h"

int main(void) {
    // Detecta a resolução do monitor
    int width, height;
    getScreenResolution(&width, &height);

    // Detecta a linguagem do sistema
    char language[16];
    getSystemLanguage(language, sizeof(language));

    InitWindow(width, height, "Insert Your Soul");

    // Remove maximizado, usa tamanho exato e sem bordas
    SetWindowState(FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_ALWAYS_RUN);

    SetWindowSize(width, height);
    SetWindowPosition(0, 0);

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText(TextFormat("Res: %dx%d, Lang: %s", width, height, language), 50, 50, 20, LIGHTGRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
