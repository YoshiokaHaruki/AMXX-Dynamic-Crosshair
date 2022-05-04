public stock const PluginName[ ] =			"[API] Addon: Dynamic Crosshair";
public stock const PluginVersion[ ] =		"1.0";
public stock const PluginAuthor[ ] =		"Yoshioka Haruki";

/* ~ [ Includes ] ~ */
#include <amxmodx>
#include <hamsandwich>
#include <api_dynamic_crosshair>

/* ~ [ AMX Mod X ] ~ */
public plugin_init( )
{
	register_plugin( PluginName, PluginVersion, PluginAuthor );

	static const WeaponEntNames[ ][ ] = { 
		"weapon_p228", "weapon_aug", "weapon_elite", "weapon_fiveseven", "weapon_ump45", 
		"weapon_galil", "weapon_famas", "weapon_usp", "weapon_glock18", "weapon_mp5navy", 
		"weapon_m249", "weapon_m4a1", "weapon_tmp", "weapon_deagle", "weapon_sg552", 
		"weapon_ak47", "weapon_p90"
	};

	/* -> HamSandwich -> */
	for ( new i; i < sizeof WeaponEntNames; i++ )
	{
		RegisterHam( Ham_Item_PostFrame, WeaponEntNames[ i ], "Ham_CBasePlayerWeapon__PostFrame_Pre", false );
		RegisterHam( Ham_Weapon_PrimaryAttack, WeaponEntNames[ i ], "Ham_CBasePlayerWeapon__PrimaryAttack_Post", true );
	}
}

/* ~ [ HamSandwich ] ~ */
public Ham_CBasePlayerWeapon__PostFrame_Pre( const pItem )
{
	if ( get_entvar( pItem, var_impulse ) == 0 )
		return HAM_IGNORED;

	UTIL_ResetCrosshair( get_member( pItem, m_pPlayer ), pItem );
	return HAM_IGNORED;
}

public Ham_CBasePlayerWeapon__PrimaryAttack_Post( const pItem )
{
	if ( get_entvar( pItem, var_impulse ) == 0 )
		return;

	UTIL_IncreaseCrosshair( get_member( pItem, m_pPlayer ), pItem );
}
