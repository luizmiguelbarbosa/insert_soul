
#include "./include/raylib.h"
#include "./include/system_config.h"

int main(void) {
    int width, height;
    getScreenResolution(&width, &height);

    char language[16];
    getSystemLanguage(language, sizeof(language));

    InitWindow(width, height, "Insert Your Soul");
    SetWindowState(FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_ALWAYS_RUN);
    SetWindowSize(width, height);
    SetWindowPosition(0, 0);

    SetTargetFPS(60);

    // Variável para controlar a opacidade do fade-in (1.0 = preto, 0 = transparente)
    float fadeAlpha = 1.0f;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText(TextFormat("Res: %dx%d, Lang: %s", width, height, language), 50, 50, 20, LIGHTGRAY);

        // Desenha o fade-in (retângulo preto com alpha)
        if (fadeAlpha > 0.0f) {
            DrawRectangle(0, 0, width, height, (Color){0, 0, 0, (unsigned char)(fadeAlpha * 255)});
            fadeAlpha -= 0.02f;  // ajusta a velocidade do fade
            if (fadeAlpha < 0) fadeAlpha = 0;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
