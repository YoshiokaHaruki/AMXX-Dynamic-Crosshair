# AMXX Dynamic Crosshair
Dynamic Crosshair for Custom Weapons for Counter-Strike 1.6 (Based on ReAPI)

### Requirements
* ReHLDS + ReGameDLL + ReAPI
* AMX Mod X ≥ 1.9.0
* * Tip: Recommend using the latest versions.

### Usage
* Add include on your custom weapon plugin
```Pawn
#include <api_dynamic_crosshair>
```

* When weapon shooting, call stock ```UTIL_IncreaseCrosshair``` in hook ```Ham_Weapon_PrimaryAttack```
* Reset crosshair to default, call stock ```UTIL_ResetCrosshair``` in hook ```Ham_Item_PostFrame```

Example:
```Pawn
// When shooting
UTIL_IncreaseCrosshair( pPlayer, pItem );

// Reset crosshair
UTIL_ResetCrosshair( pPlayer, pItem );
```

You can see how to use it in full here: https://github.com/YoshiokaHaruki/AMXX-Hunter-Killer-X-7
