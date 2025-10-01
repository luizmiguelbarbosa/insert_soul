#ifndef MENU_H
#define MENU_H

typedef enum {
    MENU_ACTION_NONE = 0,
    MENU_ACTION_START,
    MENU_ACTION_OPTIONS,
    MENU_ACTION_EXIT
} MenuAction;

void Menu_Init(int width, int height);
MenuAction Menu_UpdateDraw(void);
void Menu_Unload(void);

#endif // MENU_H
