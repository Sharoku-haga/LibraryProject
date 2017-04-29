//==================================================================================================================================//
//!< @file		ISharokuLibrary.h
//!< @brief		ISharokuLibraryクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef SL_SHAROKU_LIBRARY_H
#define SL_SHAROKU_LIBRARY_H

#include <windows.h>
#include "Common/slDefine.h"
#include "Common/slTypes.h"
#include "Common/slStruct.h"
#include "Common/slVECTOR/slVECTOR2.h"
#include "Common/slVECTOR/slVECTOR3.h"
#include "Common/slInputEnum.h"

namespace sl
{

//======================================================================//
//!< SharokuLibararyのInterfaceクラス
//======================================================================//
interface ISharokuLibrary
{

public:
	//-----------------------------------------------------------------//
	// インスタンス関連関数
	//-----------------------------------------------------------------//

	/** 
	* インスタンス生成関数 
	*  @attention	このクラスを使用する場合は必ず最初に呼ぶこと
	*/
	static void Create(void);

	/** 
	* インスタンス破棄関数
	* @attention	上記のCreate関数をよんだら、破棄処理として必ずこの関数をよぶこと
	*/
	static void Delete(void);

	/**
	* インスタンス取得関数
	* @return ISharokuLibraryクラスのインスタンスへのポインタ
	*/
	inline static ISharokuLibrary*	Instance(){ return m_pILibrary; }

	//-----------------------------------------------------------------//
	// 初期化&破棄関連関数
	//-----------------------------------------------------------------//

	/** 
	* 初期化関数 
	* @param[in] pWinTitle		ウィンドウのタイトル
	* @param[in] winWidth		ウィンドウの横幅
	* @param[in] winHeight		ウィンドウの縦幅
	*/
	virtual void Initialize(t_char*  pWinTitle, int winWidth, int winHeight) = 0;

	/** 破棄関数 */
	virtual void Finalize(void) = 0;

	//-----------------------------------------------------------------//
	// Window関連関数
	//-----------------------------------------------------------------//

	/** 
	* ウィンドウ更新関数
	* @return ウィンドウが破棄されたかどうか true = 破棄された false = 破棄されていない
	*/
	virtual bool UpdateWindow(void)  = 0;

	/** 
	* スクリーンモードを変更する関数
	* @param[in] isFullScreen		true→フルスクリーン, false→ウィンドウモード
	*/
	virtual void ChangeWindowMode(bool isFullScreen) = 0;

	//-----------------------------------------------------------------//
	// テクスチャー関連関数
	//-----------------------------------------------------------------//

	/** 
	* 指定したパスのテクスチャーを読み込む関数 
	* @param[in] pFileName テクスチャーのファイルネーム
	* @return 登録したID
	*/
	virtual int LoadTexture(const t_char* pFileName) = 0;

	/** 
	* 指定したテクスチャーを解放する関数 
	* @param[in] texID 解放したいテクスチャーのID
	*/
	virtual void ReleaseTex(int texID) = 0;

	/** 現在読み込んでいるテクスチャー全てを解放する関数 */
	virtual void ReleaseTexALL(void) = 0;

	//-----------------------------------------------------------------//
	// 頂点関連関数
	//-----------------------------------------------------------------//

	/**
	* 2Dの頂点(4つ)バッファを生成する関数
	* @param[in] rSize	サイズ
	* @param[in] rUV	UV
	* @return	登録した頂点のID
	*/
	virtual int CreateVertex2D(const fRect& rSize, const fRect& rUV) = 0;

	/** 
	* 指定した2D頂点バッファを解放する関数
	* @param[in] vtxID 解放したい頂点のID
 	*/
	virtual void ReleaseVertex2D(int vtxID) = 0;

	/** 登録している頂点バッファ(2D頂点バッファを含む)を全て解放する関数 */
	virtual void ReleaseVertexALL(void) = 0;

	//-----------------------------------------------------------------//
	// 描画関連関数
	//-----------------------------------------------------------------//

	/** 描画開始処理 */
	virtual void StartRender(void) = 0;

	/** 描画終了処理 */
	virtual void EndRender(void) = 0;

	/** 
	* 2D描画関数
	* @todo とりあえず描画チェックの為実装。後で見直し
	* @param[in] ids	登録した頂点情報IDとテクスチャーID
	* @param[in] pos	位置座標
	* @param[in] scale	スケール値. デフォルトは1.0f,1.0f,1.0f
	* @param[in] angle	角度
	*/
	virtual void Draw2D(GraphicsIDs ids, SLVECTOR2 pos, SLVECTOR3 scale = SLVECTOR3(1.0f, 1.0f, 1.0f), float angle = 0.0f) = 0;

	//-----------------------------------------------------------------//
	// インプットデバイス関連関数
	//-----------------------------------------------------------------//

	/** インプットデバイス更新関数 */
	virtual void UpdateInputDevice(void) = 0;

	/** 
	* キーの状態をチェックする関数 
	* @param[in] keyID キーのID slInputEnum.hのKEY_TYPE
	* @return	キーの状態
	*/
	virtual DEVICE_STATE CheckKey(int keyID) = 0;

	/** 
	* ゲームパッドの状態をチェックする関数 
	* @param[in] padPartID	チェックしたいパッドのアクションID. XIGAMEPAD_ACTION_ID参照
	* @param[in] padNum		チェックしたいゲームパッドの番号.デフォルトは0
	* @return 状態
	*/
	virtual DEVICE_STATE CheckGamePad(int actionID, int  padNum = 0) = 0;

	/** 
	* ボタンなどを指定したIDで登録する関数 
	* @param[in] ID			登録したいID
	* @param[in] device		デバイスタイプ
	* @param[in] inputType	登録したいインプットタイプ	
	*/
	virtual void RegisterCustomizeType(int ID, HID_TYPE device, int inputType) = 0;

	/** 
	* カスタマイズしたボタンなどをチェックする関数
	* @param[in] ID			登録したID
	* @param[in] deviceNum	チェックしたいデバイス番号.デフォルトは0
	*/
	virtual DEVICE_STATE CheckCustomizeState(int ID, int deviceNum = 0) = 0;

	//-----------------------------------------------------------------//
	// 音関連関数
	//-----------------------------------------------------------------//

	//-----------------------------------------------------------------//
	// その他
	//-----------------------------------------------------------------//

	/** Desutructor */
	virtual ~ISharokuLibrary(void){}

protected:
	/** Constructor */
	ISharokuLibrary(void){}

private:
	static ISharokuLibrary*		m_pILibrary;			//!<  ISharokuLibraryクラスのインスタンスへのポインタ

};

}	// namespace sl

#endif	// SL_SHAROKU_LIBRARY_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
