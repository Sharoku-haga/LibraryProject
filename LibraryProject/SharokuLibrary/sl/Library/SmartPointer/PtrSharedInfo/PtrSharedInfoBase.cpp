//==================================================================================================================================//
//!< @file		slPtrSharedInfoBase.cpp
//!< @brief		sl::PtrSharedInfoBaseクラス実装
//!< @author	T.Haga
//!< @data		作成日時：2017/09/17	更新履歴：
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "PtrSharedInfoBase.h"

namespace sl
{

/* Public Functions ------------------------------------------------------------------------------------------- */


PtrSharedInfoBase::PtrSharedInfoBase()
	: m_RefCount(0)
	, m_ObserverCount(0)
{}

PtrSharedInfoBase::PtrSharedInfoBase(const PtrSharedInfoBase& rInfo)
	: m_RefCount(rInfo.m_RefCount)
	, m_ObserverCount(rInfo.m_ObserverCount)
{
	AddRefCount();
	AddObserverCount();
}

PtrSharedInfoBase::PtrSharedInfoBase(PtrSharedInfoBase&& rRight)
	: m_RefCount(rRight.m_RefCount)
	, m_ObserverCount(rRight.m_ObserverCount)
{}

void PtrSharedInfoBase::AddRefCount()
{
	++m_RefCount;
}

void PtrSharedInfoBase::AddObserverCount()
{
	++m_ObserverCount;
}

void PtrSharedInfoBase::ReleaseReference()
{
	--m_RefCount;
	if(m_RefCount == 0)
	{
		DestroyResource();
	}
}

void PtrSharedInfoBase::ReleaseObserver()
{
	--m_ObserverCount;
}

}	// namespace sl

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
