class V30_BluntDamageData {
	bool m_bEnabled;
	float m_fThreshold;
	float m_fMultiplier;

	void V30_BluntDamageData(bool enabled = false, float threshold = 0.0, float multiplier = 0.5)
	{
		m_bEnabled = enabled;
		m_fThreshold = threshold;
		m_fMultiplier = multiplier;
	};

	static V30_BluntDamageData From(SCR_ArmoredClothItemData data)
	{
		if (!data)
			return V30_BluntDamageData();
		
		return V30_BluntDamageData(data.m_bBluntDamageEnabled, data.m_fBluntDamageThreshold, data.m_fBluntDamageMultiplier);
	};
}

modded class SCR_ArmoredClothItemData
{
	[Attribute(defvalue: "0", desc: "Enable blunt damage.")]
	bool m_bBluntDamageEnabled;

	[Attribute(defvalue: "0", desc: "Minimal damage required to apply blunt damage.", params: "0 inf")]
	float m_fBluntDamageThreshold;

	[Attribute(defvalue: "0.33", desc: "How much blunt damage is applied.", params: "0.0 1.0")]
	float m_fBluntDamageMultiplier;

	void SCR_ArmoredClothItemData(SCR_EArmorLevels protection, array<string> protectedHitZones, array<EDamageType> protectedDamageTypes, ResourceName resourceName, V30_BluntDamageData bluntDamage = null)
	{
		if (!bluntDamage)
			return;
		
		m_bBluntDamageEnabled = bluntDamage.m_bEnabled;
		m_fBluntDamageThreshold = bluntDamage.m_fThreshold;
		m_fBluntDamageMultiplier = bluntDamage.m_fMultiplier;
	};
}
