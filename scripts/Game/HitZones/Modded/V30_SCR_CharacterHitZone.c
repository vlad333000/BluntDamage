modded class SCR_CharacterHitZone
{
	override float ComputeEffectiveDamage(notnull BaseDamageContext damageContext, bool isDOT)
	{
		if (!IsArmorBluntDamageEnabled())
			return super.ComputeEffectiveDamage(damageContext, isDOT);

		float rawDamage = damageContext.damageValue;
		if (damageContext.damageValue > 0 && !isDOT)
		{
			float protectionValue = GetArmorProtectionValue(damageContext.damageType);
			rawDamage = Math.Max(damageContext.damageValue - protectionValue, 0);
			float bluntDamage = ComputeBluntDamage(damageContext, isDOT);
			rawDamage += bluntDamage;
			rawDamage += protectionValue;
		}

		BaseDamageContext hack = BaseDamageContext.Cast(damageContext.Clone());
		hack.damageValue = rawDamage;

		return super.ComputeEffectiveDamage(hack, isDOT);
	};

	float ComputeBluntDamage(notnull BaseDamageContext damageContext, bool isDOT)
	{
		float protectionValue = GetArmorProtectionValue(damageContext.damageType);
		float threshold = GetArmorBluntDamageThreshold(damageContext.damageType);
		float penetratedDamage = Math.Max(damageContext.damageValue - protectionValue, 0);
		float nonPenetratedDamage = damageContext.damageValue - penetratedDamage;
		float multiplier = GetArmorBluntDamageMultiplier(damageContext.damageType);
		
		return Math.Max(nonPenetratedDamage - threshold, 0.0) * multiplier;
	};

	bool IsArmorBluntDamageEnabled()
	{
		SCR_CharacterDamageManagerComponent damageMgr = SCR_CharacterDamageManagerComponent.Cast(GetHitZoneContainer());
		if (!damageMgr)
			return 0;

		return damageMgr.IsArmorBluntDamageEnabled(this);
	};

	float GetArmorBluntDamageThreshold(EDamageType damageType)
	{
		SCR_CharacterDamageManagerComponent damageMgr = SCR_CharacterDamageManagerComponent.Cast(GetHitZoneContainer());
		if (!damageMgr)
			return 0;

		return damageMgr.GetArmorBluntDamageThreshold(this, damageType);
	};

	float GetArmorBluntDamageMultiplier(EDamageType damageType)
	{
		SCR_CharacterDamageManagerComponent damageMgr = SCR_CharacterDamageManagerComponent.Cast(GetHitZoneContainer());
		if (!damageMgr)
			return 0;

		return damageMgr.GetArmorBluntDamageMultiplier(this, damageType);
	};
}
