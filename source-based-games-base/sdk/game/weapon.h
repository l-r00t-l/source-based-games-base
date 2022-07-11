#pragma once
#include "classes.h"
// #include "../interfaces/classes/i_client_entity.h"
// #include "../netvar-manager/netvar_manager.h"
// #include "../utils/utils.h"
#include "enums.h"
#include "entity.h"
#include "../sdk.hpp"
class c_base_entity;

// #define GET_VFUNC( type, function_name, index, ...) \
// auto function_name { \
// return g_utils.call_vfunc< type >( this, index )( this, __VA_ARGS__ ); \
// };

#define GET_NETVAR(name, var, ...) \
std::add_lvalue_reference_t<__VA_ARGS__> name() \
{ \
	static const uint32_t offset = c_netvars::get()->m_database[g_utils.compile_time(var)]; \
	return *reinterpret_cast<std::add_pointer_t<__VA_ARGS__>>(uint32_t(this) + offset); \
}

#define GET_OFFSET(name, offset, ...) \
std::add_lvalue_reference_t<__VA_ARGS__> name() \
{ \
	return *reinterpret_cast<std::add_pointer_t<__VA_ARGS__>>(uint32_t(this) + offset); \
}

#define GET_VFUNC(name, index, ...) \
__VA_ARGS__ name() \
{ \
	return g_utils.call_vfunc<__VA_ARGS__>(this, index); \
}


class c_base_attributable_item : public c_base_entity
{
public:
//	GET_NETVAR(uint64_t, get_original_owner_xuid, "DT_BaseAttributableItem->m_OriginalOwnerXuidLow");
// 	GET_NETVAR(int, get_original_owner_xuid_low, _("DT_BaseAttributableItem"), _("m_OriginalOwnerXuidLow"));
// 	GET_NETVAR(int, get_original_owner_xuid_high, _("DT_BaseAttributableItem"), _("m_OriginalOwnerXuidHigh"));
// 	GET_NETVAR(int, get_fallback_stat_trak, _("DT_BaseAttributableItem"), _("m_nFallbackStatTrak"));
// 	GET_NETVAR(int, get_fallback_paint_kit, _("DT_BaseAttributableItem"), _("m_nFallbackPaintKit"));
// 	GET_NETVAR(int, get_fallback_seed, _("DT_BaseAttributableItem"), _("m_nFallbackSeed"));
// 	GET_NETVAR(float, get_fallback_wear, _("DT_BaseAttributableItem"), _("m_flFallbackWear"));
// 	GET_NETVAR(bool, is_initialized, _("DT_BaseAttributableItem"), _("m_bInitialized"));
// 	GET_NETVAR(int, get_entity_level, _("DT_BaseAttributableItem"), _("m_iEntityLevel"));
// 	GET_NETVAR(int, get_account_id, _("DT_BaseAttributableItem"), _("m_iAccountID"));
// 	GET_NETVAR(int, get_item_id_low, _("DT_BaseAttributableItem"), _("m_iItemIDLow"));
// 	GET_NETVAR(int, get_item_id_high, _("DT_BaseAttributableItem"), _("m_iItemIDHigh"));
// 	GET_NETVAR(int, get_entity_quality, _("DT_BaseAttributableItem"), _("m_iEntityQuality"));
// 	GET_NETVAR(char, get_custom_name, _("DT_BaseAttributableItem"), _("m_szCustomName"));
// 	GET_NETVAR(short, get_idx, _("DT_BaseAttributableItem"), _("m_iItemDefinitionIndex"));

	GET_NETVAR(get_original_owner_xuid, "CBaseAttributableItem->m_OriginalOwnerXuidLow", uint64_t);
	GET_NETVAR(get_original_owner_xuid_low, "CBaseAttributableItem->m_OriginalOwnerXuidLow", int);
	GET_NETVAR(get_original_owner_xuid_high, "CBaseAttributableItem->m_OriginalOwnerXuidHigh", int);
	GET_NETVAR(get_fallback_stat_trak, "CBaseAttributableItem->m_nFallbackStatTrak", int);
	GET_NETVAR(get_fallback_paint_kit, "CBaseAttributableItem->m_nFallbackPaintKit", int);
	GET_NETVAR(get_fallback_seed, "CBaseAttributableItem->m_nFallbackSeed", int);
	GET_NETVAR(get_fallback_wear, "CBaseAttributableItem->m_flFallbackWear", float);
	GET_NETVAR(is_initialized, "CBaseAttributableItem->m_bInitialized", bool);
	GET_NETVAR(get_entity_level, "CBaseAttributableItem->m_iEntityLevel", int);
	GET_NETVAR(get_account_id, "CBaseAttributableItem->m_iAccountID", int);
	GET_NETVAR(get_item_id_low, "CBaseAttributableItem->m_iItemIDLow", int);
	GET_NETVAR(get_item_id_high, "CBaseAttributableItem->m_iItemIDHigh", int);
	GET_NETVAR(get_entity_quality, "CBaseAttributableItem->m_iEntityQuality", int);
	GET_NETVAR(get_custom_name, "CBaseAttributableItem->m_szCustomName", char);
	GET_NETVAR(get_index, "CBaseAttributableItem->m_iItemDefinitionIndex", short);

};

class c_weapon : public c_base_attributable_item
{
public:
// 	GET_NETVAR(float, get_last_shot_time, _("DT_WeaponCSBase"), _("m_fLastShotTime"));
// 	GET_NETVAR(int, get_ammo, _("DT_BaseCombatWeapon"), _("m_iClip1"));
// 	GET_NETVAR(c_base_handle, get_owner, _("DT_BaseCombatWeapon"), _("m_hOwner"));
// 	GET_NETVAR(c_base_handle, get_weapon_world_model, _("DT_BaseCombatWeapon"), _("m_hWeaponWorldModel"));
// 	GET_NETVAR(float, get_next_primary_attack, _("DT_BaseCombatWeapon"), _("m_flNextPrimaryAttack"));
// 	GET_NETVAR(float, get_next_secondary_attack, _("DT_BaseCombatWeapon"), _("m_flNextSecondaryAttack"));
// 	GET_NETVAR(int, world_dropped_model_index, _("DT_BaseCombatWeapon"), _("m_iWorldDroppedModelIndex"));
// 	GET_NETVAR(bool, get_pin_pulled, _("DT_BaseCSGrenade"), _("m_bPinPulled"));
// 	GET_NETVAR(float, get_throw_time, _("DT_BaseCSGrenade"), _("m_fThrowTime"));
// 	GET_NETVAR(int, get_zoom_level, _("DT_WeaponCSBaseGun"), _("m_zoomLevel"));
// 	GET_NETVAR(float, get_post_pone_fire_ready_time, _("DT_WeaponCSBase"), _("m_flPostponeFireReadyTime"));
// 	GET_NETVAR(float, get_recoil_index, _("DT_WeaponCSBase"), _("m_flRecoilIndex"));
// 	GET_NETVAR(float, get_accuracy_penalty, _("DT_WeaponCSBase"), _("m_fAccuracyPenalty"));
// 	GET_NETVAR(float, get_throw_strength, _("DT_BaseCSGrenade"), _("m_flThrowStrength"));
// 	GET_NETVAR(int, get_clip1, _("DT_BaseCombatWeapon"), _("m_iClip1"));
// 	GET_NETVAR(int, get_clip2, _("DT_BaseCombatWeapon"), _("m_iClip2"));
// 	GET_NETVAR(float, get_postpone_fire_ready_time, _("DT_WeaponCSBase"), _("m_flPostponeFireReadyTime"));
// 	GET_OFFSET(c_handle < c_base_player >, get_thrower, 0x29B0);
// 	GET_VFUNC(void(__thiscall*)(void*), update_accuracy_penalty(), 484);
// 	GET_VFUNC(float(__thiscall*)(void*), get_spread(), 453);
// 	GET_VFUNC(float(__thiscall*)(void*), get_inaccuracy(), 483);
// 	GET_VFUNC(c_weapon_info*(__thiscall*)(void*), get_weapon_data(), 461);

	GET_NETVAR(get_last_shot_time, "CWeaponCSBase->m_fLastShotTime", float);
	GET_NETVAR(get_ammo, "CWeaponCSBase->", int);
	GET_NETVAR(get_owner, "CWeaponCSBase->m_hOwner", c_base_handle);
	GET_NETVAR(get_weapon_world_model, "CWeaponCSBase->m_hWeaponWorldModel", c_base_handle);
	GET_NETVAR(get_next_primary_attack, "CWeaponCSBase->m_flNextPrimaryAttack", float);
	GET_NETVAR(get_next_secondary_attack, "CWeaponCSBase->m_flNextSecondaryAttack", float);
	GET_NETVAR(world_dropped_model_index, "CWeaponCSBase->m_iWorldDroppedModelIndex", int);
	GET_NETVAR(get_pin_pulled, "CBaseCSGrenade->m_bPinPulled", bool);
	GET_NETVAR(get_throw_time, "CBaseCSGrenade->m_fThrowTime", float);
	GET_NETVAR(get_zoom_level, "CWeaponCSBaseGun-m_zoomLevel", int);
	GET_NETVAR(get_post_pone_fire_ready_time, "CWeaponCSBase->m_flPostponeFireReadyTime", float);
	GET_NETVAR(get_recoil_index, "CWeaponCSBase->m_flRecoilIndex", float);
	GET_NETVAR(get_accuracy_penalty, "CWeaponCSBase->m_fAccuracyPenalty", float);
	GET_NETVAR(get_throw_strength, "CBaseCSGrenade->m_flThrowStrength", float);
	GET_NETVAR(get_clip1, "CBaseCombatWeapon->m_iClip1", int);
	GET_NETVAR(get_clip2, "CBaseCombatWeapon->m_iClip2", int);
	GET_NETVAR(get_postpone_fire_ready_time, "CWeaponCSBase->m_flPostponeFireReadyTime", float);
	GET_OFFSET(get_thrower, 0x29B0, c_handle<c_base_player>);
	//GET_VFUNC(update_accuracy_penalty, 484, void); //crashing
	GET_VFUNC(get_spread, 453, float);
	GET_VFUNC(get_inaccuracy, 483, float);
	GET_VFUNC(get_weapon_data, 461, c_weapon_info*);



	std::string get_name()
	{
		if (this->get_weapon_data())
			return "invalid";

		return { this->get_weapon_data()->m_weapon_name };
	}

	int get_weapon_type()
	{
		if (!this->get_weapon_data())
			return 0;

		return get_weapon_data()->m_weapon_type;
	}

	bool is_smg()
	{
		if (!this)
			return false;

		return get_weapon_type() == weapon_type_submachinegun;
	}

	bool is_grenade()
	{
		if (!this)
			return false;

		return get_weapon_type() == weapon_type_grenade;
	}

	bool is_gun()
	{
		if (!this)
			return false;

		switch (get_weapon_type())
		{
		case weapon_type_grenade:
			return false;
		case weapon_type_knife:
			return false;
		case weapon_c4:
			return false;
		default:
			return true;
		}
	}

	bool is_knife()
	{
		if (!this)
			return false;

		return get_weapon_type() == weapon_type_knife;
	}

	bool is_rifle()
	{
		if (!this)
			return false;

		return get_weapon_type() == weapon_type_rifle;
	}

	bool is_sniper()
	{
		if (!this)
			return false;

		return get_weapon_type() == weapon_type_sniper_rifle;
	}

	bool is_bomb()
	{
		if (!this)
			return false;

		return get_weapon_type() == weapon_type_c4;
	}
};