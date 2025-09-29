#include "./include/raylib.h"
#include "./include/system_config.h"

int main(void) {
    // Detecta a resolução do monitor
    int width, height;
    getScreenResolution(&width, &height);

    // Detecta a linguagem do sistema
    char language[16];
    getSystemLanguage(language, sizeof(language));

    // Inicializa a janela
    InitWindow(width, height, "Insert Your Soul");

    // Force fullscreen sem bordas (esconde barra de tarefas)
    SetWindowState(FLAG_WINDOW_UNDECORATED | FLAG_FULLSCREEN_MODE);

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
