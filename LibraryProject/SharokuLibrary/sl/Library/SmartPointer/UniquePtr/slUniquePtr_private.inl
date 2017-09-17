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

template< class T
		, template<class> class Deleter >
UniquePtr<T, Deleter>::UniquePtr() noexcept
	: m_Pointer(nullptr)
{}

template< class T
		, template<class> class Deleter >
UniquePtr<T, Deleter>::UniquePtr(T* pointer)  noexcept
	: m_Pointer(pointer)
{}

template< class T
		, template<class> class Deleter >
UniquePtr<T, Deleter>::UniquePtr(UniquePtr&& uiniquePtr) noexcept
		: m_Pointer(uiniquePtr.Release())
{}

template< class T
		, template<class> class Deleter >
template< class OtherT
		, template<class> class OtherDeleter>
UniquePtr<T, Deleter>::UniquePtr(UniquePtr<OtherT, OtherDeleter>&& uiniquePtr) noexcept
	: m_Pointer(uiniquePtr.Release())
{}
	
template< class T
		, template<class> class Deleter >
UniquePtr<T, Deleter>::~UniquePtr()
{
	Deleter<T>()(m_Pointer);
}

template< class T
		, template<class> class Deleter >
T* UniquePtr<T, Deleter>::Release() noexcept
{
	T* pointer = m_Pointer;
	m_Pointer = nullptr;
	return pointer;
}

template< class T
		, template<class> class Deleter >
void UniquePtr<T, Deleter>::Reset(T* pointer)
{
	Deleter<T>()(m_Pointer);
	m_Pointer = pointer;
}

template< class T
		, template<class> class Deleter >
void UniquePtr<T, Deleter>::Swap(UniquePtr& rUiniquePtr)noexcept
{
	T* tmp = this->Release();
	this->Reset(rUiniquePtr.Release());
	rUiniquePtr.Reset(tmp);
}

template< class T
		, template<class> class Deleter >
UniquePtr<T, Deleter>&	UniquePtr<T, Deleter>::operator = (UniquePtr&& uiniquePtr)
{
	this->Reset(uiniquePtr.Release());
	return *this;
}

template< class T
		, template<class> class Deleter >
template< class OtherT
		, template<class> class OtherDeleter>
UniquePtr<T, Deleter>&	UniquePtr<T, Deleter>::operator = (UniquePtr< OtherT, OtherDeleter>&& uiniquePtr)
{
	this->Reset(uiniquePtr.Release());
	return *this;
}

/* Global Functions ------------------------------------------------------------------------------------------- */

template< class T
		, template<class> class Deleter
		, class... Args >
UniquePtr<T, Deleter> MakeUniquePtr(Args&&... args)
{
	return UniquePtr<T, Deleter>(new T(std::forward<Args>(args)...));
}

template< class T
		, template<class T> class Deleter 
		, class OtherT
		, template<class OtherT>class OtherDeleter >
const bool operator == (const UniquePtr<T, Deleter>& rLeft, const UniquePtr<OtherT, OtherDeleter>& rRight) noexcept
{
	return rLeft.Get() == rRight.Get();
}

template< class T
		, template<class T> class Deleter 
		, class OtherT
		, template<class OtherT>class OtherDeleter >
const bool operator != (const UniquePtr<T, Deleter>& rLeft, const UniquePtr<OtherT, OtherDeleter>& rRight) noexcept
{
	return rLeft.Get() != rRight.Get();
}

}	// namespace sl

#endif	// SL_UNIQUE_PTR_PRIVATE_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
