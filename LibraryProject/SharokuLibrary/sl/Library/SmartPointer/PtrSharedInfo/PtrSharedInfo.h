//==================================================================================================================================//
//!< @file		slPtrSharedInfo.h
//!< @brief		sl::PtrSharedInfoクラスヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/09/17	更新履歴：
//==================================================================================================================================//

#ifndef SL_PTR_SHARED_INFO_H
#define SL_PTR_SHARED_INFO_H

#include "PtrSharedInfoBase.h"
#include "../../Utility/slCompressedPair.h"

namespace sl
{

//===================================================================================//
//!< ポインタの共有情報を管理するクラス
//===================================================================================//
template < class Ty
		 , class Deleter>
class PtrSharedInfo : public PtrSharedInfoBase
{

public:
	/** 
	* Constructor
	* @param[in] pResource リソースへのポインタ
	*/
	explicit PtrSharedInfo(Ty* pResource)
		: PtrSharedInfoBase()
		, m_PtrPair(Zero_then_variadic_args_t(), pResource)
	{}

	/** Destructor */
	~PtrSharedInfo() = default;

private:
	CompressedPair<Deleter, Ty*> m_PtrPair;		//!< リソースへのポインタとデリータのペア

	/** リソース破棄関数 */
	virtual void DestroyResource()override
	{
		m_PtrPair.GetFirst()(m_PtrPair.GetSecond());
	}
	
};	// class PtrSharedInfo

}	// namespace sl

#endif	// SL_PTR_SHARED_INFO_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
