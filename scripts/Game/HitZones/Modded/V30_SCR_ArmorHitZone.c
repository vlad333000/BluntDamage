modded class SCR_ArmorHitZone : SCR_HitZone
{
	[Attribute("0", UIWidgets.ComboBox, "EDamageTypes against which the hitzone will be protected", enums: ParamEnumArray.FromEnum(EDamageType))]
	ref array<EDamageType> m_aProtectedDamageTypes;

	[Attribute(defvalue: SCR_Enum.GetDefault(SCR_EArmorLevels.NONE), uiwidget: UIWidgets.ComboBox, "Armor protection level", enums: ParamEnumArray.FromEnum(SCR_EArmorLevels))]
	SCR_EArmorLevels m_eProtection;

	[Attribute(defvalue: "0", desc: "Enable blunt damage.")]
	bool m_bBluntDamageEnabled;

	[Attribute(defvalue: "0", desc: "Minimal damage required to apply blunt damage.", params: "0 inf")]
	float m_fBluntDamageThreshold;

	[Attribute(defvalue: "0.33", desc: "How much blunt damage is applied.", params: "0.0 1.0")]
	float m_fBluntDamageMultiplier;

	override float ComputeEffectiveDamage(notnull BaseDamageContext damageContext, bool isDOT)
	{
		float rawDamage = damageContext.damageValue;
		if (damageContext.damageValue > 0 && !isDOT)
		{
			float protectionValue = GetArmorProtectionValue(damageContext.damageType);
			rawDamage = Math.Max(damageContext.damageValue - protectionValue, 0);
			
			if (IsArmorBluntDamageEnabled())
			{
				float bluntDamage = ComputeBluntDamage(damageContext, isDOT);
				rawDamage += bluntDamage;
			};
		};

		BaseDamageContext hack = BaseDamageContext.Cast(damageContext.Clone());
		hack.damageValue = rawDamage;

		return super.ComputeEffectiveDamage(hack, isDOT);
	};

	float GetArmorProtectionValue(EDamageType damageType)
	{
		foreach (EDamageType protectedType : m_aProtectedDamageTypes)
		{
			if (damageType == protectedType)
				return m_eProtection;
		}

		return 0;
	};
	bool IsArmorBluntDamageEnabled()
	{
		return m_bBluntDamageEnabled;
	};
	float GetArmorBluntDamageThreshold(EDamageType damageType)
	{
		foreach (EDamageType protectedType : m_aProtectedDamageTypes)
		{
			if (damageType == protectedType)
				return m_fBluntDamageThreshold;
		};

		return 0.0;
	};
	float GetArmorBluntDamageMultiplier(EDamageType damageType)
	{
		foreach (EDamageType protectedType : m_aProtectedDamageTypes)
		{
			if (damageType == protectedType)
				return m_fBluntDamageMultiplier;
		};

		return 0.5;
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
}
