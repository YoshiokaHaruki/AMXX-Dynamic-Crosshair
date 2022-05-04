#if defined _api_dynamic_crosshair_included
	#endinput
#endif
#define _api_dynamic_crosshair_included

#if !defined _reapi_included
    #include <reapi>
#endif

/* -> Dynamic Crosshair <- */
stock UTIL_IncreaseCrosshair( const pPlayer, const pItem, iFakePosition = 13, iFakeWeaponId = CSW_MAC10 )
{
    if ( BIT( get_member( pItem, m_iId ) ) & ( BIT( CSW_MAC10 ) | BIT( CSW_M3 ) | BIT( CSW_XM1014 ) ) )
        return;
    
    if ( get_member( pPlayer, m_iFOV ) < DEFAULT_AUG_SG552_ZOOM || get_member( pPlayer, m_iHideHUD ) & HIDEHUD_CROSSHAIR )
        return;

    static iMsgId_CurWeapon; if ( !iMsgId_CurWeapon ) iMsgId_CurWeapon = get_user_msgid( "CurWeapon" );

    set_msg_block( iMsgId_CurWeapon, BLOCK_ONCE );

    if ( rg_get_iteminfo( pItem, ItemInfo_iSlot ) != 0 )
    {
        new pWeapon = get_member( pPlayer, m_rgpPlayerItems, PRIMARY_WEAPON_SLOT );
        if ( !is_nullent( pWeapon ) && get_member( pWeapon, m_iId ) == iFakeWeaponId )
            iFakePosition = 12, iFakeWeaponId = CSW_XM1014;
    }

    UTIL_WeaponList( MSG_ONE, pPlayer, pItem, .iPosition = iFakePosition, .iWeaponId = iFakeWeaponId );
    UTIL_CurWeapon( MSG_ONE, pPlayer, true, iFakeWeaponId, get_member( pItem, m_Weapon_iClip ) );

    set_member( pItem, m_Weapon_flNextReload, get_gametime( ) + 0.04 );
}

stock UTIL_ResetCrosshair( const pPlayer, const pItem ) 
{
    if ( get_member( pItem, m_Weapon_flNextReload ) && get_member( pItem, m_Weapon_flNextReload ) <= get_gametime( ) ) 
    {
        UTIL_CurWeapon( MSG_ONE, pPlayer, true, get_member( pItem, m_iId ), get_member( pItem, m_Weapon_iClip ) );
        set_member( pItem, m_Weapon_flNextReload, 0.0 );
    }
}

/* -> Weapon List <- */
stock UTIL_WeaponList( const iDest, const pReceiver, const pItem, szWeaponName[ MAX_NAME_LENGTH ] = "", const iPrimaryAmmoType = -2, iMaxPrimaryAmmo = -2, iSecondaryAmmoType = -2, iMaxSecondaryAmmo = -2, iSlot = -2, iPosition = -2, iWeaponId = -2, iFlags = -2 ) 
{
    if ( szWeaponName[ 0 ] == EOS )
        rg_get_iteminfo( pItem, ItemInfo_pszName, szWeaponName, charsmax( szWeaponName ) )

    static iMsgId_Weaponlist; if ( !iMsgId_Weaponlist ) iMsgId_Weaponlist = get_user_msgid( "WeaponList" );

    message_begin( iDest, iMsgId_Weaponlist, .player = pReceiver );
    write_string( szWeaponName );
    write_byte( ( iPrimaryAmmoType <= -2 ) ? get_member( pItem, m_Weapon_iPrimaryAmmoType ) : iPrimaryAmmoType );
    write_byte( ( iMaxPrimaryAmmo <= -2 ) ? rg_get_iteminfo( pItem, ItemInfo_iMaxAmmo1 ) : iMaxPrimaryAmmo );
    write_byte( ( iSecondaryAmmoType <= -2 ) ? get_member( pItem, m_Weapon_iSecondaryAmmoType ) : iSecondaryAmmoType );
    write_byte( ( iMaxSecondaryAmmo <= -2 ) ? rg_get_iteminfo( pItem, ItemInfo_iMaxAmmo2 ) : iMaxSecondaryAmmo );
    write_byte( ( iSlot <= -2 ) ? rg_get_iteminfo( pItem, ItemInfo_iSlot ) : iSlot );
    write_byte( ( iPosition <= -2 ) ? rg_get_iteminfo( pItem, ItemInfo_iPosition ) : iPosition );
    write_byte( ( iWeaponId <= -2 ) ? rg_get_iteminfo( pItem, ItemInfo_iId ) : iWeaponId );
    write_byte( ( iFlags <= -2 ) ? rg_get_iteminfo( pItem, ItemInfo_iFlags ) : iFlags );
    message_end( );
}

/* -> Cur Weapon <- */
stock UTIL_CurWeapon( const iDest, const pReceiver, const bool: bIsActive, const iWeaponId, const iClipAmmo )
{
    static iMsgId_CurWeapon; if ( !iMsgId_CurWeapon ) iMsgId_CurWeapon = get_user_msgid( "CurWeapon" );

    message_begin( iDest, iMsgId_CurWeapon, .player = pReceiver );
    write_byte( bIsActive );
    write_byte( iWeaponId );
    write_byte( iClipAmmo );
    message_end( );
}