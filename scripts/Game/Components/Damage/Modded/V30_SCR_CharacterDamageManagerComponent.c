modded class SCR_CharacterDamageManagerComponent
{
	bool IsArmorBluntDamageEnabled(notnull SCR_CharacterHitZone charHitZone)
	{
		SCR_ArmoredClothItemData localArmorData = GetArmorData(charHitZone);
		if (!localArmorData)
			return false;

		return localArmorData.m_bBluntDamageEnabled;
	};
	float GetArmorBluntDamageThreshold(notnull SCR_CharacterHitZone charHitZone, EDamageType damageType)
	{
		SCR_ArmoredClothItemData localArmorData = GetArmorData(charHitZone);
		if (!localArmorData)
			return 0.0;

		foreach (EDamageType protectedType : localArmorData.m_aProtectedDamageTypes)
		{
			if (damageType == protectedType)
				return localArmorData.m_fBluntDamageThreshold;
		};

		return 0.0;
	};
	float GetArmorBluntDamageMultiplier(notnull SCR_CharacterHitZone charHitZone, EDamageType damageType)
	{
		SCR_ArmoredClothItemData localArmorData = GetArmorData(charHitZone);
		if (!localArmorData)
			return 0.5;

		foreach (EDamageType protectedType : localArmorData.m_aProtectedDamageTypes)
		{
			if (damageType == protectedType)
				return localArmorData.m_fBluntDamageMultiplier;
		};

		return 0.5;
	};
	override void UpdateArmorDataMap(notnull SCR_ArmoredClothItemData armorAttr, bool remove)
	{
		foreach (string hitZoneName : armorAttr.m_aProtectedHitZones)
		{
			SCR_CharacterHitZone hitZone = SCR_CharacterHitZone.Cast(GetHitZoneByName(hitZoneName));
			if (hitZone)
			{
				if (remove)
				{
					RemoveArmorData(hitZone);
					continue;
				}

				SCR_ArmoredClothItemData armoredClothItemData;
				armoredClothItemData = new SCR_ArmoredClothItemData(
					armorAttr.m_eProtection,
					armorAttr.m_aProtectedHitZones,
					armorAttr.m_aProtectedDamageTypes,
					armorAttr.m_MaterialResourceName,
					V30_BluntDamageData.From(armorAttr)
				);

				InsertArmorData(hitZone, armoredClothItemData);
			}
		}
	}
}
