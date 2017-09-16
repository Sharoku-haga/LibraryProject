//==================================================================================================================================//
//!< @file		slWeakPtr_private.inl
//!< @brief		sl::WeakPtrクラス実装
//!< @author	T.Haga
//!< @data		作成日時：2017/09/17	更新履歴：
//==================================================================================================================================//

#ifndef SL_WEAK_PTR_PRIVATE_INL
#define SL_WEAK_PTR_PRIVATE_INL

namespace sl
{

/* Public Functions ------------------------------------------------------------------------------------------- */

template<class Ty>
WeakPtr<Ty>::WeakPtr()noexcept
	: PtrBase<Ty>()
{}

template<class Ty>
WeakPtr<Ty>::WeakPtr(const SharedPtr<Ty>& rPtr)
	: PtrBase<Ty>(rPtr)
{
	AddObserverCount();
}

template<class Ty>
template<class OtherTy>
WeakPtr<Ty>::WeakPtr(const SharedPtr<OtherTy>& rPtr)
	: PtrBase<Ty>(rPtr)
{
	AddObserverCount();
}

template<class Ty>
WeakPtr<Ty>::WeakPtr(const WeakPtr& rPtr)
	: PtrBase<Ty>(rPtr)
{
	AddObserverCount();
}

template<class Ty>
template<class OtherTy>
WeakPtr<Ty>::WeakPtr(const WeakPtr<OtherTy>& rPtr)
	: PtrBase<Ty>(rPtr)
{
	AddObserverCount();
}

template<class Ty>
WeakPtr<Ty>::WeakPtr(WeakPtr&& rRight)
	: PtrBase<Ty>(Move(rRight))
{
	AddObserverCount();
	rRight.Reset();
}

template<class Ty>
template<class OtherTy>
WeakPtr<Ty>::WeakPtr(WeakPtr<OtherTy>&& rRight)
	: PtrBase<Ty>(Move(rRight))
{
	AddObserverCount();
	rPtr.Reset();
}

template<class Ty>
WeakPtr<Ty>::~WeakPtr()
{
	ReleaseObserver();
}

template<class Ty>
SharedPtr<Ty> WeakPtr<Ty>::Lock()
{
	return IsExpired() ? SharedPtr<Ty>() : SharedPtr<Ty>(*this);
}

template<class Ty>
void WeakPtr<Ty>::Reset()
{
	WeakPtr().Swap(*this);
}

template<class Ty>
bool WeakPtr<Ty>::IsExpired()
{
	return (UseRefCount() == 0);
}

template<class Ty>
WeakPtr<Ty>& WeakPtr<Ty>::operator = (const WeakPtr& rPtr)
{
	WeakPtr<Ty>(rPtr).Swap(*this);
	return (*this);
}

template<class Ty>
template<class OtherTy>
WeakPtr<Ty>& WeakPtr<Ty>::operator = (const WeakPtr<OtherTy>& rPtr)
{
	WeakPtr<Ty>(rPtr).Swap(*this);
	return (*this);
}

template<class Ty>
WeakPtr<Ty>& WeakPtr<Ty>::operator = (const SharedPtr<Ty>& rPtr)
{
	WeakPtr<Ty>(rPtr).Swap(*this);
	return (*this);
}

template<class Ty>
template<class OtherTy>
WeakPtr<Ty>& WeakPtr<Ty>::operator = (const SharedPtr<OtherTy>& rPtr)
{
	WeakPtr<Ty>(rPtr).Swap(*this);
	return (*this);
}

template<class Ty>
WeakPtr<Ty>& WeakPtr<Ty>::operator = (WeakPtr&& rRight)
{
	WeakPtr<Ty>(Move(rRight)).Swap(*this);
	return (*this);
}

template<class Ty>
template<class OtherTy>
WeakPtr<Ty>& WeakPtr<Ty>::operator = (WeakPtr<OtherTy>&& rRight)
{
	WeakPtr<Ty>(Move(rRight)).Swap(*this);
	return (*this);
}

}	// namespace sl

#endif	// SL_WEAK_PTR_PRIVATE_INL

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
