//==================================================================================================================================//
//!< @file		slDirectSoundDevice.cpp		
//!< @brief		sl::DirectSoundDeviceクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017/10/31	更新履歴：
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "slDirectSoundDevice.h"
#include "../../../../../Utility/slTemplateFunction.h"
#include "../../../../../Debugger/slDebugFunction.h"
#include "../../ISoundData/DirectSoundData/slDirectSoundData.h"

namespace sl
{

/* Public Functions ------------------------------------------------------------------------------------------- */

DirectSoundDevice::DirectSoundDevice(const WindowHandle& rHandle)
	: m_WinHandle(rHandle)
	, m_pDSound8(NULL)
{}

DirectSoundDevice::~DirectSoundDevice()
{
	SafeReleaseDX(m_pDSound8);
}

bool DirectSoundDevice::Initlialize()
{
	if(FAILED(DirectSoundCreate8(NULL, &m_pDSound8, NULL)))
	{
		slOutputDebugString("DirectSoundデバイスの生成に失敗致しました");
		return false;
	}
	// 協調レベル設定
	m_pDSound8->SetCooperativeLevel(static_cast<HWND>(m_WinHandle.m_pAdress), DSSCL_NORMAL);

	return true;
}

bool DirectSoundDevice::CreateSoundData(t_char* pFileName, UniquePtr<ISoundData>& pData)
{
	LPDIRECTSOUNDBUFFER8 pDSBuffer = NULL;

	char *pWaveData = 0;
	DWORD waveSize = 0;
	WAVEFORMATEX	wFmt;	

	// Waveファイルオープン
	if(!OpenWave(pFileName, &wFmt, &pWaveData, &waveSize))
	{
		slOutputDebugString(pFileName);
		slOutputDebugString("のWAVEファイルオープンに失敗しました。");
		return false;
	}

	// バッファ作成
	{
		DSBUFFERDESC DSBufferDesc;
		DSBufferDesc.dwSize = sizeof(DSBUFFERDESC);
		DSBufferDesc.dwFlags = 0;
		DSBufferDesc.dwBufferBytes = waveSize;
		DSBufferDesc.dwReserved = 0;
		DSBufferDesc.lpwfxFormat = &wFmt;
		DSBufferDesc.guid3DAlgorithm = GUID_NULL;

		IDirectSoundBuffer *ptmpBuf = 0;
		m_pDSound8->CreateSoundBuffer(&DSBufferDesc, &ptmpBuf, NULL);
		ptmpBuf->QueryInterface(IID_IDirectSoundBuffer8, (void**)&pDSBuffer);
		ptmpBuf->Release();

		if(pDSBuffer == NULL)
		{
			slOutputDebugString("バッファの作成に失敗しました");
			return false;
		}
	}

	// セカンダリバッファにWaveデータ書き込み
	{
		LPVOID lpvWrite = 0;				//音声データ
		DWORD dwLength = 0;					//音声データの大きさ
		if(DS_OK == pDSBuffer->Lock(0, 0, &lpvWrite, &dwLength, NULL, NULL, DSBLOCK_ENTIREBUFFER))
		{
			memcpy(lpvWrite, pWaveData, dwLength);
			pDSBuffer->Unlock(lpvWrite, dwLength, NULL, 0);
		}
	}

	delete[] pWaveData;		// 元の音データ削除

	pData.Reset(new DirectSoundData(pDSBuffer));

	return true;
}

/* Private Functions ------------------------------------------------------------------------------------------ */

bool DirectSoundDevice::OpenWave(TCHAR* pFileName, WAVEFORMATEX* pWaveFormatEx
								, char** pWaveData, DWORD* pDataSize)
{
	if(pFileName == 0)
	{
		return false;
	}

	HMMIO hMmio = NULL;
	MMIOINFO mmioInfo;

	// waveファイルオープン
	memset(&mmioInfo, 0, sizeof(MMIOINFO));
	hMmio = mmioOpen(pFileName, &mmioInfo, MMIO_READ);
	if(!hMmio)
	{
		return false; // ファイルオープン失敗
	}

	// RIFFチャンク検索
	MMRESULT mmRes;
	MMCKINFO riffChunk;
	riffChunk.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	mmRes = mmioDescend(hMmio, &riffChunk, NULL, MMIO_FINDRIFF);
	if(mmRes != MMSYSERR_NOERROR)
	{
		mmioClose(hMmio, 0);
		return false;
	}

	// フォーマットチャンク検索
	MMCKINFO formatChunk;
	formatChunk.ckid = mmioFOURCC('f', 'm', 't', ' ');
	mmRes = mmioDescend(hMmio, &formatChunk, &riffChunk, MMIO_FINDCHUNK);
	if(mmRes != MMSYSERR_NOERROR)
	{
		mmioClose(hMmio, 0);
		return false;
	}
	DWORD fmsize = formatChunk.cksize;
	DWORD size = mmioRead(hMmio, (HPSTR)pWaveFormatEx, fmsize);
	if(size != fmsize) 
	{
		mmioClose(hMmio, 0);
		return false;
	}

	mmioAscend(hMmio, &formatChunk, 0);

	// データチャンク検索
	MMCKINFO dataChunk;
	dataChunk.ckid = mmioFOURCC('d', 'a', 't', 'a');
	mmRes = mmioDescend(hMmio, &dataChunk, &riffChunk, MMIO_FINDCHUNK);
	if(mmRes != MMSYSERR_NOERROR) 
	{
		mmioClose(hMmio, 0);
		return false;
	}

	*pWaveData = new char[dataChunk.cksize];
	size = mmioRead(hMmio, (HPSTR)*pWaveData, dataChunk.cksize);
	if(size != dataChunk.cksize) {
		delete[] *pWaveData;
		return false;
	}
	*pDataSize = size;

	// ハンドルクローズ
	mmioClose(hMmio, 0);

	return true;
}

}	// namespace sl

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
