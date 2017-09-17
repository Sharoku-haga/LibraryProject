//==================================================================================================================================//
//!< @file		slPtrBase_private.inl
//!< @brief		sl::PtrBaseクラス実装
//!< @author	T.Haga
//!< @data		作成日時：2017/09/17	更新履歴：
//==================================================================================================================================//

#ifndef SL_PTR_BASE_PRIVATE_INL
#define SL_PTR_BASE_PRIVATE_INL

namespace sl
{

/* Public Functions ------------------------------------------------------------------------------------------- */

template< class Ty>
PtrBase<Ty>::PtrBase()noexcept
	: m_pResource(nullptr)
	, m_pInfo(nullptr)
{}

template<class Ty>
PtrBase<Ty>::PtrBase(Ty* pResource)
	: m_pResource(pResource)
	, m_pInfo(new PtrSharedInfo<Ty, DefaultDeleter<Ty>>(pResource))
{}

template<class Ty>
template<class OtherTy>
PtrBase<Ty>::PtrBase(OtherTy* pResource)
	: m_pResource(pResource)
	, m_pInfo(new PtrSharedInfo<Ty, DefaultDeleter<Ty>>(pResource))
{}

template<class Ty> 
template<class Deleter>
PtrBase<Ty>::PtrBase(Ty* pResource, Deleter Del)
	: m_pResource(pResource)
	, m_pInfo(new PtrSharedInfo<Ty, Deleter>(pResource))
{}

template<class Ty> 
template< class OtherTy
		, class Deleter>
PtrBase<Ty>::PtrBase(OtherTy* pResource, Deleter Del)
	: m_pResource(pResource)
	, m_pInfo(new PtrSharedInfo<Ty, Deleter>(pResource))
{}

template<class Ty>
PtrBase<Ty>::PtrBase(const PtrBase& rPtr)
	: m_pResource(rPtr.m_pResource)
	, m_pInfo(rPtr.m_pInfo)
{}

template<class Ty>
template<class OtherTy>
PtrBase<Ty>::PtrBase(const PtrBase<OtherTy>& rPtr)
	: m_pResource(rPtr.m_pResource)
	, m_pInfo(rPtr.m_pInfo)
{}

template<class Ty>
PtrBase<Ty>::PtrBase(PtrBase&& rRight)noexcept
	: m_pResource(rRight.m_pResource)
	, m_pInfo(rRight.m_pInfo)
{}

template<class Ty>
template<class OtherTy>
PtrBase<Ty>::PtrBase(PtrBase<OtherTy>&& rRight)noexcept
	: m_pResource(rRight.m_pResource)
	, m_pInfo(rRight.m_pInfo)
{}

template<class Ty>
void PtrBase<Ty>::Swap(PtrBase& rPtr)noexcept
{
	SwapTemplate(m_pResource, rPtr.m_pResource);
	SwapTemplate(m_pInfo, rPtr.m_pInfo);
}

template<class Ty>
u_long PtrBase<Ty>::UseRefCount()
{
	return (!m_pInfo) ? 0 : m_pInfo->GetRefCount();
}

/* Protected Functions ---------------------------------------------------------------------------------------- */

template<class Ty>
void PtrBase<Ty>::AddRefCount()
{
	m_pInfo->AddRefCount();
}

template<class Ty>
void PtrBase<Ty>::AddObserverCount()
{
	m_pInfo->AddObserverCount();
}

template<class Ty>
void PtrBase<Ty>::ReleaseReference()
{
	if(m_pInfo != nullptr)
	{
	  m_pInfo->ReleaseReference();
	  ReleaseObserver();
	}
}

template<class Ty>
void PtrBase<Ty>::ReleaseObserver()
{
	if(m_pInfo == nullptr)
	{
		return;
	}
	
	m_pInfo->ReleaseObserver();

	if(m_pInfo->GetRefCount() == 0
		&& m_pInfo->GetObserverCount() == 0)
	{
		delete m_pInfo;
		m_pInfo = nullptr;
	}
}

template<class Ty>
u_long PtrBase<Ty>::UseObserverCount()
{
	return (!m_pInfo) ? 0 : m_pInfo->GetObserverCount();
}

}	// namespace sl

#endif	// SL_PTR_BASE_PRIVATE_INL

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
