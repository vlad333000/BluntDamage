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