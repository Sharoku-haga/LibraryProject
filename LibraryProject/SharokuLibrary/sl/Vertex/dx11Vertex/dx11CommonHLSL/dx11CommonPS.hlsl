//==================================================================================================================================//
//!< @file		dx11CommonPS.hlsl
//!< @brief		共通で使用するPSファイル		
//!< @author	T.Haga
//==================================================================================================================================//

Texture2D g_Texture: register(t0);
SamplerState g_Sampler : register(s0);

cbuffer global : register(b0)
{
	matrix g_WorldMat;
	float4 g_ViewPort;
};


struct PS_INPUT
{
	float4 m_Pos   : SV_POSITION;
	float4 m_Color : COLOR;
	float2 m_UV    : TEXCOORD;
};


float4 PS(PS_INPUT Input) : SV_Target
{
	float4 OutColor;
	OutColor = g_Texture.Sample(g_Sampler, Input.m_UV);
	//OutColor *= Input.m_Color;
	//////OutColor = Input.m_Color;;
	return OutColor;
	//return g_Texture.Sample(g_Sampler, Input.m_UV);
}


//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
