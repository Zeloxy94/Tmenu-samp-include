/*
	Test File
	Author: Tr0Y
*/
#include <a_samp>
#include <zcmd>
#include <Tmenu>

#define SKIN_MENU 		1500
#define WEAPON_MENU 	1501

public OnMenuResponse(playerid, menuid, option) {
    switch(menuid) {
        case SKIN_MENU: {
            switch(option) {
                case 0: SetPlayerSkin(playerid, 230);
                case 1: SetPlayerSkin(playerid, 244);
            }
        }
        case WEAPON_MENU: {
            switch(option) {
                case 0: {
					GivePlayerWeapon(playerid, 24, 500);
					SendClientMessage(playerid, -1, "Weapon Pack 1");
				}
                case 1:{
					GivePlayerWeapon(playerid, 31, 500);
					SendClientMessage(playerid, -1, "Weapon Pack 2");
				}
            }
        }
    }
    return 1;
}

CMD:skins(playerid) {
    Menu_Create(playerid, SKIN_MENU, "Skin Selection");
    Menu_AddOption(playerid, "Skin 1");
    Menu_AddOption(playerid, "Skin 2");
    Menu_Show(playerid);
    return 1;
}
CMD:weapons(playerid) {
    Menu_Create(playerid, WEAPON_MENU, "Weapon Menu");
    Menu_AddOption(playerid, "Weapon Pack 1");
    Menu_AddOption(playerid, "~r~Weapon Pack 2");
    Menu_AddOption(playerid, "Weapon Pack 3");
    Menu_Show(playerid);
    return 1;
}
