//==================================================================================================================================//
//!< @file		slUniquePtr_private.inl
//!< @brief		UniquePtrクラス実装
//!< @author	T.Haga
//!< @data		作成日時：2017/09/10	更新履歴 : 2017/09/17
//==================================================================================================================================//

#ifndef SL_UNIQUE_PTR_PRIVATE_H
#define SL_UNIQUE_PTR_PRIVATE_H

namespace sl
{

/* Public Functions ------------------------------------------------------------------------------------------- */

template< class Ty
		, class Deleter>
UniquePtr<Ty, Deleter>::UniquePtr() noexcept
	: m_pResource(nullptr)
{}

template< class Ty
		, class Deleter>
UniquePtr<Ty, Deleter>::UniquePtr(Ty* pointer)
	: m_pResource(pointer)
{}

template< class Ty
		, class Deleter>
UniquePtr<Ty, Deleter>::UniquePtr(UniquePtr&& rRight) noexcept
		: m_pResource(rRight.Release())
{}

template< class Ty
		, class Deleter>
template< class OtherTy
		, class OtherDeleter>
UniquePtr<Ty, Deleter>::UniquePtr(UniquePtr<OtherTy, OtherDeleter>&& rRight) noexcept
	: m_pResource(rRight.Release())
{}
	
template< class Ty
		, class Deleter>
UniquePtr<Ty, Deleter>::~UniquePtr()
{
	Deleter()(m_pResource);
}

template< class Ty
		, class Deleter>
Ty* UniquePtr<Ty, Deleter>::Release() noexcept
{
	Ty* pointer = m_pResource;
	m_pResource = nullptr;
	return pointer;
}

template< class Ty
		, class Deleter>
void UniquePtr<Ty, Deleter>::Reset(Ty* pointer)
{
	Deleter()(m_pResource);
	m_pResource = pointer;
}

template< class Ty
		, class Deleter>
void UniquePtr<Ty, Deleter>::Swap(UniquePtr& rPtr)noexcept
{
	SwapTemplate(*this, rPtr);
}

template< class Ty
		, class Deleter>
UniquePtr<Ty, Deleter>&	UniquePtr<Ty, Deleter>::operator = (UniquePtr&& rRight)
{
	this->Reset(rRight.Release());
	return (*this);
}

template< class Ty
		, class Deleter>
template< class OtherTy
		, class OtherDeleter>
UniquePtr<Ty, Deleter>&	UniquePtr<Ty, Deleter>::operator = (UniquePtr< OtherTy, OtherDeleter>&& rRight)
{
	this->Reset(rRight.Release());
	return *this;
}

/* Global Functions ------------------------------------------------------------------------------------------- */

template< class Ty
		, class Deleter
		, class... Args >
UniquePtr<Ty, Deleter> MakeUniquePtr(Args&&... args)
{
	return UniquePtr<Ty, Deleter>(new Ty(std::forward<Args>(args)...));
}

template< class Ty
		, class Deleter 
		, class OtherTy
		, class OtherDeleter >
const bool operator == (const UniquePtr<Ty, Deleter>& rLeft, const UniquePtr<OtherTy, OtherDeleter>& rRight) noexcept
{
	return rLeft.Get() == rRight.Get();
}

template< class Ty
		, class Deleter 
		, class OtherTy
		, class OtherDeleter >
const bool operator != (const UniquePtr<Ty, Deleter>& rLeft, const UniquePtr<OtherTy, OtherDeleter>& rRight) noexcept
{
	return rLeft.Get() != rRight.Get();
}

}	// namespace sl

#endif	// SL_UNIQUE_PTR_PRIVATE_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
