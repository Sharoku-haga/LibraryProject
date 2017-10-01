//==================================================================================================================================//
//!< @file		slDXConstantBufferManager.cpp		
//!< @brief		sl::DXConstantBufferManagerクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017/10/04	更新履歴：2017/10/06
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "slDXConstantBufferManager.h"
#include "../../../../Utility/slTemplateFunction.h"
#include "../../../../Debugger/slDebugFunction.h"

namespace sl
{

/* Public Functions ------------------------------------------------------------------------------------------- */

DXConstantBufferManager::DXConstantBufferManager(ID3D11Device*	pDevice)
	: m_pDevice(pDevice)
{}

DXConstantBufferManager::~DXConstantBufferManager()
{
	ReleaseALL();
}

ConstantBufferID DXConstantBufferManager::CreateConstantBuffer(unsigned int constantBufferSize)
{
	int bufferID = INT_MAX;
	ID3D11Buffer* pConstantBuffer;
	D3D11_BUFFER_DESC ConstantBufferDesc;
	ZeroMemory(&ConstantBufferDesc, sizeof(D3D11_BUFFER_DESC));
	ConstantBufferDesc.ByteWidth			= constantBufferSize;
	ConstantBufferDesc.Usage				= D3D11_USAGE_DYNAMIC;
	ConstantBufferDesc.BindFlags			= D3D11_BIND_CONSTANT_BUFFER;
	ConstantBufferDesc.CPUAccessFlags		= D3D11_CPU_ACCESS_WRITE;
	ConstantBufferDesc.MiscFlags			= 0;
	ConstantBufferDesc.StructureByteStride	= 0;

	if (FAILED(m_pDevice->CreateBuffer(&ConstantBufferDesc, NULL, &pConstantBuffer)))
	{
		slOutputDebugString("コンスタントバッファの生成に失敗しました");
		return ConstantBufferID(bufferID);
	}

	bufferID = m_pConstantBuffer.size();
	m_pConstantBuffer.push_back(pConstantBuffer);

	return ConstantBufferID(bufferID);
}

void DXConstantBufferManager::Release(const ConstantBufferID& rID)
{
	SafeReleaseDX(m_pConstantBuffer[rID.m_Num]);
}

void DXConstantBufferManager::ReleaseALL()
{
	for(auto& pConstantBuffer : m_pConstantBuffer)
	{
		SafeReleaseDX(pConstantBuffer);
	}
	std::vector<ID3D11Buffer*>().swap(m_pConstantBuffer);
}


}	// namespace sl

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
