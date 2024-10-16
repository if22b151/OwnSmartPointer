#pragma once

//#include <algorithm>

template <typename T>
class UniquePtr {
public:
	//Constructors
	UniquePtr(T* ptr) : m_ptr(ptr) {}
	UniquePtr() : m_ptr(nullptr) {}
	//delete copy constructor and copy assignment operator to prevent copying
	UniquePtr(const UniquePtr& other) = delete;
	UniquePtr& operator=(const UniquePtr& other) = delete;
	//move constructor and move assignment operator to move ownership of the pointer
	UniquePtr(UniquePtr&& other);
	UniquePtr& operator=(UniquePtr&& other);
	//Destructor
	~UniquePtr() { delete m_ptr; }

	//Operators
	T& operator*() const { return *m_ptr; }
	T* operator->() const { return m_ptr; }
	operator bool() const { return m_ptr != nullptr; }

	//Methods
	T* Release();
	void Reset(T* ptr = nullptr);
	void Swap(UniquePtr& other);



private:
	T* m_ptr;
};

//other UniquePtr gives up ownership of the pointer and this UniquePtr takes ownership of it
template<typename T>
UniquePtr<T>::UniquePtr(UniquePtr&& other) {
	m_ptr = other.Release();	
}

//this UniquePtr sets its ptr to the other UniquePtr's ptr and the other UniquePtr's ptr is set to nullptr
template<typename T>
UniquePtr<T>& UniquePtr<T>::operator=(UniquePtr&& other) {
	Reset(other.Release());
	return *this;
}

//Give up ownership of the pointer and return it
template<typename T>
T* UniquePtr<T>::Release() {
	T* temp = m_ptr;
	m_ptr = nullptr;
	return temp;
}

//Reset the pointer to a new pointer, default = nullptr
template<typename T>
void UniquePtr<T>::Reset(T* ptr) {
	m_ptr = nullptr;
	m_ptr = ptr;
}

//swap the pointers
template<typename T>
void UniquePtr<T>::Swap(UniquePtr& other) {
	//Which version?
	auto temp = m_ptr;
	m_ptr = other.m_ptr;
	other.m_ptr = temp;	
	/*std::swap(m_ptr, other.m_ptr);*/
}
