//==================================================================================================================================//
//!< @file		App.h
//!< @brief		Appクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef APP_H
#define APP_H

namespace app
{

class App
{

public:
	/** Constructor */
	App();

	/** Destructor */
	~App();

	/** 初期化関数 */
	void Initialize();

	/** 破棄関数 */
	void Finalize();

	/** 
	 * 更新関数
	 * @return アプリケーションが終了したかどうか true→終了 false→継続
	 */
	bool Update(void);

};	// class App

}	// namespace app

#endif	// APP_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
