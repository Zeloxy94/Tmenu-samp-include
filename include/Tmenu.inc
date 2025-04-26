/*
    TMenu.inc - New Type of TextDraw Menu
*/

#if defined _Tmenu_included
    #endinput
#endif
#define _Tmenu_included

#include <a_samp>

#define MENU_BG_X          79.0
#define MENU_BG_Y          146.0
#define OPTION_X           14.0
#define OPTION_Y           172.0
#define OPTION_SPACING     20.0
#define MAX_MENU_OPTIONS   8
#define INVALID_MENU_ID    -1

enum E_MENU_DATA {
    Text:menuBackground,
    Text:menuOptions[MAX_MENU_OPTIONS],
    PlayerText:menuHeader,
    mOptionCount,
    mSelection,
    bool:mIsOpen,
    mMenuID
};
new gPlayerMenu[MAX_PLAYERS][E_MENU_DATA];

forward OnMenuResponse(playerid, menuid, option);

public OnGameModeInit() {
    return 1;
}

public OnPlayerConnect(playerid) {
    for(new i = 0; i < MAX_MENU_OPTIONS; i++) {
        gPlayerMenu[playerid][menuOptions][i] = Text:INVALID_TEXT_DRAW;
    }
    gPlayerMenu[playerid][menuBackground] = Text:INVALID_TEXT_DRAW;
    gPlayerMenu[playerid][menuHeader] = PlayerText:INVALID_TEXT_DRAW;
    gPlayerMenu[playerid][mOptionCount] = 0;
    gPlayerMenu[playerid][mSelection] = 0;
    gPlayerMenu[playerid][mIsOpen] = false;
    gPlayerMenu[playerid][mMenuID] = INVALID_MENU_ID;
    return 1;
}

stock Menu_Create(playerid, menuid, const header[]) {
    if(gPlayerMenu[playerid][menuBackground] != Text:INVALID_TEXT_DRAW) {
        TextDrawDestroy(gPlayerMenu[playerid][menuBackground]);
    }
    if(gPlayerMenu[playerid][menuHeader] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, gPlayerMenu[playerid][menuHeader]);
    }
    for(new i = 0; i < MAX_MENU_OPTIONS; i++) {
        if(gPlayerMenu[playerid][menuOptions][i] != Text:INVALID_TEXT_DRAW) {
            TextDrawDestroy(gPlayerMenu[playerid][menuOptions][i]);
        }
    }
    gPlayerMenu[playerid][menuBackground] = TextDrawCreate(MENU_BG_X, MENU_BG_Y, "_");
    TextDrawFont(gPlayerMenu[playerid][menuBackground], 1);
    TextDrawLetterSize(gPlayerMenu[playerid][menuBackground], 0.6, 20.4);
    TextDrawTextSize(gPlayerMenu[playerid][menuBackground], 298.5, 131.5);
    TextDrawSetOutline(gPlayerMenu[playerid][menuBackground], 1);
    TextDrawSetShadow(gPlayerMenu[playerid][menuBackground], 0);
    TextDrawAlignment(gPlayerMenu[playerid][menuBackground], 2);
    TextDrawColor(gPlayerMenu[playerid][menuBackground], -1);
    TextDrawBackgroundColor(gPlayerMenu[playerid][menuBackground], 255);
    TextDrawBoxColor(gPlayerMenu[playerid][menuBackground], 135);
    TextDrawUseBox(gPlayerMenu[playerid][menuBackground], 1);
    TextDrawSetProportional(gPlayerMenu[playerid][menuBackground], 1);
    TextDrawSetSelectable(gPlayerMenu[playerid][menuBackground], 0);

    new headerText[128];
    format(headerText, sizeof(headerText), "%s", header);
    gPlayerMenu[playerid][menuHeader] = CreatePlayerTextDraw(playerid, MENU_BG_X, MENU_BG_Y, headerText);
    PlayerTextDrawFont(playerid, gPlayerMenu[playerid][menuHeader], 1);
    PlayerTextDrawLetterSize(playerid, gPlayerMenu[playerid][menuHeader], 0.35, 1.2);
    PlayerTextDrawTextSize(playerid, gPlayerMenu[playerid][menuHeader], 101.0, 131.0);
    PlayerTextDrawSetOutline(playerid, gPlayerMenu[playerid][menuHeader], 0);
    PlayerTextDrawSetShadow(playerid, gPlayerMenu[playerid][menuHeader], 1);
    PlayerTextDrawAlignment(playerid, gPlayerMenu[playerid][menuHeader], 2);
    PlayerTextDrawColor(playerid, gPlayerMenu[playerid][menuHeader], -1);
    PlayerTextDrawBackgroundColor(playerid, gPlayerMenu[playerid][menuHeader], 255);
    PlayerTextDrawBoxColor(playerid, gPlayerMenu[playerid][menuHeader], 1097458175);
    PlayerTextDrawUseBox(playerid, gPlayerMenu[playerid][menuHeader], 1);
    PlayerTextDrawSetProportional(playerid, gPlayerMenu[playerid][menuHeader], 1);
    PlayerTextDrawSetSelectable(playerid, gPlayerMenu[playerid][menuHeader], 0);

    gPlayerMenu[playerid][mOptionCount] = 0;
    gPlayerMenu[playerid][mSelection] = 0;
    gPlayerMenu[playerid][mMenuID] = menuid;
    return 1;
}

stock Menu_AddOption(playerid, const text[]) {
    if(gPlayerMenu[playerid][mOptionCount] >= MAX_MENU_OPTIONS) return 0;

    new idx = gPlayerMenu[playerid][mOptionCount];
    new Float:yPos = OPTION_Y + (idx * OPTION_SPACING);
    new optionText[128];

    format(optionText, sizeof(optionText), "%s", text);
    gPlayerMenu[playerid][menuOptions][idx] = TextDrawCreate(OPTION_X, yPos, optionText);

    TextDrawFont(gPlayerMenu[playerid][menuOptions][idx], 1);
    TextDrawLetterSize(gPlayerMenu[playerid][menuOptions][idx], 0.35, 1.2);
    TextDrawTextSize(gPlayerMenu[playerid][menuOptions][idx], 101.5, 22.5);
    TextDrawSetOutline(gPlayerMenu[playerid][menuOptions][idx], 0);
    TextDrawSetShadow(gPlayerMenu[playerid][menuOptions][idx], 0);
    TextDrawBoxColor(gPlayerMenu[playerid][menuOptions][idx], 0x414141FF);
    TextDrawUseBox(gPlayerMenu[playerid][menuOptions][idx], 1);

    gPlayerMenu[playerid][mOptionCount]++;
    return 1;
}

stock Menu_Show(playerid) {
    if(gPlayerMenu[playerid][mOptionCount] == 0) return 0;

    TextDrawShowForPlayer(playerid, gPlayerMenu[playerid][menuBackground]);
    PlayerTextDrawShow(playerid, gPlayerMenu[playerid][menuHeader]);

    for(new i = 0; i < gPlayerMenu[playerid][mOptionCount]; i++) {
        TextDrawShowForPlayer(playerid, gPlayerMenu[playerid][menuOptions][i]);
    }

    TextDrawBoxColor(gPlayerMenu[playerid][menuOptions][0], 0x416385FF);
    TextDrawShowForPlayer(playerid, gPlayerMenu[playerid][menuOptions][0]);

    gPlayerMenu[playerid][mIsOpen] = true;
    return 1;
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
    if(gPlayerMenu[playerid][mIsOpen]) {
        if(newkeys & KEY_UP) {
            new oldSelection = gPlayerMenu[playerid][mSelection];
            TextDrawBoxColor(gPlayerMenu[playerid][menuOptions][oldSelection], 0x414141FF);
            TextDrawShowForPlayer(playerid, gPlayerMenu[playerid][menuOptions][oldSelection]);

            gPlayerMenu[playerid][mSelection] = (oldSelection + 1 + gPlayerMenu[playerid][mOptionCount]) % gPlayerMenu[playerid][mOptionCount];

            new newSelection = gPlayerMenu[playerid][mSelection];
            TextDrawBoxColor(gPlayerMenu[playerid][menuOptions][newSelection], 0x416385FF);
            TextDrawShowForPlayer(playerid, gPlayerMenu[playerid][menuOptions][newSelection]);
        }
        else if(newkeys & KEY_DOWN) {
            new oldSelection = gPlayerMenu[playerid][mSelection];
            TextDrawBoxColor(gPlayerMenu[playerid][menuOptions][oldSelection], 0x414141FF);
            TextDrawShowForPlayer(playerid, gPlayerMenu[playerid][menuOptions][oldSelection]);

            gPlayerMenu[playerid][mSelection] = (oldSelection - 1) % gPlayerMenu[playerid][mOptionCount];

            new newSelection = gPlayerMenu[playerid][mSelection];
            TextDrawBoxColor(gPlayerMenu[playerid][menuOptions][newSelection], 0x416385FF);
            TextDrawShowForPlayer(playerid, gPlayerMenu[playerid][menuOptions][newSelection]);
        }
        else if(newkeys & KEY_SECONDARY_ATTACK) {
            CallLocalFunction("OnMenuResponse", "iii", playerid, gPlayerMenu[playerid][mMenuID], gPlayerMenu[playerid][mSelection]);
            Menu_Hide(playerid);
        }
    }
    #if defined TMenu_OnPlayerKeyStateChange
        return TMenu_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
    #else
        return 1;
    #endif
}

stock Menu_Hide(playerid) {
    TextDrawHideForPlayer(playerid, gPlayerMenu[playerid][menuBackground]);
    PlayerTextDrawHide(playerid, gPlayerMenu[playerid][menuHeader]);

    for(new i = 0; i < gPlayerMenu[playerid][mOptionCount]; i++) {
        TextDrawHideForPlayer(playerid, gPlayerMenu[playerid][menuOptions][i]);
    }

    gPlayerMenu[playerid][mIsOpen] = false;
    gPlayerMenu[playerid][mMenuID] = INVALID_MENU_ID;
    return 1;
}

#if defined _ALS_OnPlayerKeyStateChange
    #undef OnPlayerKeyStateChange
#else
    #define _ALS_OnPlayerKeyStateChange
#endif
#define OnPlayerKeyStateChange TMenu_OnPlayerKeyStateChange
forward TMenu_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
public TMenu_OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    return 1;
}
