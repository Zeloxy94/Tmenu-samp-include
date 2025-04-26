# TMenu.inc - New TextDraw Menu
![SA-MP Version](https://img.shields.io/badge/SA--MP-0.3.7%2B-blue)

A new type of textdraw menu with full player-specific control and dynamic customization.

## 📋 Functions
- **Menu_Create(playerid, menuid, const header[])**
- **Menu_AddOption(playerid, const text[])**
- **Menu_Show(playerid)**
- **Menu_Hide(playerid)**

## 🔄 Callbacks
- **OnMenuResponse(playerid, menuid, option)**

## 📥 Installation
1. Download `TMenu.inc`
2. Place in `pawno/includes` directory
3. Include in your gamemode:
``` pawn
#include <TMenu>
```

