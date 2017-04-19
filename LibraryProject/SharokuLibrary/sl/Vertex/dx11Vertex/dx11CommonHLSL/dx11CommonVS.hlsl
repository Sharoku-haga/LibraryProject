//==================================================================================================================================//
//!< @file		dx11CommonVS.hlsl
//!< @brief		共通で使用するVSファイル		
//!< @author	T.Haga
//==================================================================================================================================//

Texture2D g_Texture: register(t0);
SamplerState g_Sampler : register(s0);

cbuffer global : register(b0)
{
	matrix g_WorldMat;
	float4 g_ViewPort;
};

struct VS_OUTPUT
{
	float4	m_Pos	: SV_POSITION;
	float4	m_Color	: COLOR;
	float2	m_UV	: TEXCOORD;
};

VS_OUTPUT VS(float4 Pos : POSITION, float4 Color : COLOR, float2 UV : TEXCOORD)
{
	VS_OUTPUT Out;

	Out.m_Pos	= mul(Pos, g_WorldMat);
	Out.m_Pos.x	= (Out.m_Pos.x / g_ViewPort.x) * 2 - 1;
	Out.m_Pos.y	= 1 - (Out.m_Pos.y / g_ViewPort.y) * 2;
	Out.m_UV = UV;
	Out.m_Color = Color;

	return Out;
}

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
