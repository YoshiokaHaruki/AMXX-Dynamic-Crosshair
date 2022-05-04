# AMXX Dynamic Crosshair
Dynamic Crosshair for Custom Weapons for Counter-Strike 1.6 (Based on ReAPI)

The scope will not expand on weapons such as:
* *weapon_mac10*
* *weapon_xm1014*
* *weapon_m3*

It will also not work if the player has a hidden sight or FOV (Field of view) less than 55 (Zoom from *weapon_aug*)

### Requirements
ReHLDS, ReGameDLL, Metamod-r (or Metamod-P), AMX Mod X, ReAPI.
* Tip: Recommend using the latest versions.

### Usage
This plugin will only work with custom weapons, so that the sight with default weapons does not get interrupted.

When installing the plugin, the sight will automatically expand when shots are fired.

### Usage without plugin

In order not to use the plugin, but to use a dynamic sight anyway, it is enough to add include
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
