#ifndef SYSTEM_CONFIG_H
#define SYSTEM_CONFIG_H

// Obtém a resolução da tela do sistema
void getScreenResolution(int *width, int *height);

// Obtém a linguagem do sistema (abreviação, ex: "en", "pt")
void getSystemLanguage(char *lang, int size);

#endif
