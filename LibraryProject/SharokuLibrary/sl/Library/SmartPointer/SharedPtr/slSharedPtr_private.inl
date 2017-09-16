//==================================================================================================================================//
//!< @file		slSharedPtr_private.inl
//!< @brief		sl::SharedPtrクラス実装
//!< @author	T.Haga
//!< @data		作成日時：2017/09/17	更新履歴：
//==================================================================================================================================//

#ifndef SL_SHARED_PTR_PRIVATE_INL
#define SL_SHARED_PTR_PRIVATE_INL

namespace sl
{

/* Public Functions ------------------------------------------------------------------------------------------- */

template<class Ty>
SharedPtr<Ty>::SharedPtr() noexcept
		: PtrBase<Ty>()
{}

template<class Ty>
SharedPtr<Ty>::SharedPtr(Ty* pResource)
	: PtrBase<Ty>(pResource)
{
	AddRefCount();
	AddObserverCount();
}

template<class Ty>
template<class OtherTy>
SharedPtr<Ty>::SharedPtr(OtherTy* pResource)
	: PtrBase<Ty>(pResource)
{
	AddRefCount();
	AddObserverCount();
}

template<class Ty>
SharedPtr<Ty>::SharedPtr(const WeakPtr<Ty>& rWeakPtr)
	: PtrBase<Ty>(rWeakPtr)
{
	AddRefCount();
	AddObserverCount();
}

template<class Ty>
template<class Deleter>
SharedPtr<Ty>::SharedPtr(Ty* pResource, Deleter Del)
	: PtrBase<Ty>(pResource, Del)
{
	AddRefCount();
	AddObserverCount();
}

template<class Ty>
template< class OtherTy
		, class Deleter>
SharedPtr<Ty>::SharedPtr(OtherTy* pResource, Deleter Del)
	: PtrBase<Ty>(pResource, Del)
{
	AddRefCount();
	AddObserverCount();
}

template<class Ty>
SharedPtr<Ty>::SharedPtr(const SharedPtr& rPtr)
	: PtrBase<Ty>(rPtr)
{
	AddRefCount();
	AddObserverCount();
}

template<class Ty>
template<class OtherTy>
SharedPtr<Ty>::SharedPtr(const SharedPtr<OtherTy>& rPtr)
	: PtrBase<Ty>(rPtr)
{
	AddRefCount();
	AddObserverCount();
}

template<class Ty>
SharedPtr<Ty>::SharedPtr(SharedPtr&& rRight) noexcept
	: PtrBase<Ty>(Move(rRight))
{
	AddRefCount();
	AddObserverCount();
	rRight.Reset();
}

template<class Ty>
template<class OtherTy>
SharedPtr<Ty>::SharedPtr(SharedPtr<OtherTy>&& rRight) noexcept
	: PtrBase<Ty>(Move(rRight))
{
	AddRefCount();
	AddObserverCount();
	rRight.Reset();
}

template<class Ty>
SharedPtr<Ty>::~SharedPtr()
{
	ReleaseReference();
}

template<class Ty>
void SharedPtr<Ty>::Reset()
{
	SharedPtr().Swap(*this);
}

template<class Ty>
void SharedPtr<Ty>::Reset(Ty* pResource)
{
	SharedPtr(pResource).Swap(*this);
}

template<class Ty>
template<class OtherTy>
void SharedPtr<Ty>::Reset(OtherTy* pResource)
{
	SharedPtr(pResource).Swap(*this);
}

template<class Ty>
template<class Deleter>
void SharedPtr<Ty>::Reset(Ty* pResource, Deleter Del)
{
	SharedPtr(pResource, Del).Swap(*this);
}

template<class Ty>
template< class OtherTy
		, class Deleter>
void SharedPtr<Ty>::Reset(OtherTy* pResource, Deleter Del)
{
	SharedPtr(pResource, Del).Swap(*this);
}

template<class Ty>
SharedPtr<Ty>& SharedPtr<Ty>::operator = (const SharedPtr& rPtr)
{
	SharedPtr(rPtr).Swap(*this);
	return (*this);
}

template<class Ty>
template<class OtherTy>
SharedPtr<Ty>& SharedPtr<Ty>::operator = (const SharedPtr<OtherTy>& rPtr)
{
	SharedPtr(rPtr).Swap(*this);
	return (*this);
}

template<class Ty>
SharedPtr<Ty>& SharedPtr<Ty>::operator = (SharedPtr&& rRight)
{
	SharedPtr(Move(rRight)).Swap(*this);
	return (*this);
}

template<class Ty>
template<class OtherTy>
SharedPtr<Ty>& SharedPtr<Ty>::operator = (SharedPtr<OtherTy>&& rRight)
{
	SharedPtr(Move(rRight)).Swap(*this);
	return (*this);
}

/* Global Functions ------------------------------------------------------------------------------------------- */

template< class Ty1
		, class Ty2>
const bool operator == (const SharedPtr<Ty1>& rLeft, const SharedPtr<Ty2>& rRight) noexcept
{
	return rLeft.Get() == rRight.Get();
}

template< class Ty1
		, class Ty2>
const bool operator != (const SharedPtr<Ty1>& rLeft, const SharedPtr<Ty2>& rRight) noexcept
{
	return rLeft.Get() != rRight.Get();
}

}	// namespace sl

#endif	// SL_SHARED_PTR_PRIVATE_INL

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
