
template<typename T, typename Dx = std::default_delete<T>>
class UniquePtr {
    
    using pointer = T*;
    using reference = T&;
    using valueType = T;
    using deleter_type = Dx;

    
    public:
        //UniquePtr();
        explicit UniquePtr(T* ptr = nullptr, Dx deleter = deleter_type()) : m_ptr(ptr), deleter(deleter) {}
        
        UniquePtr(UniquePtr&& other) noexcept {
            //m_ptr = other.release();
            //deleter = std::move(other.deleter);

            m_ptr = other.m_ptr;
            deleter = std::move(other.deleter);
            other.m_ptr = nullptr;
        }

        UniquePtr& operator=(UniquePtr&& other) noexcept {
            //reset(other.release()); 
            //deleter = std::move(other.deleter);
            if (this != &other) {
                delete m_ptr;
                m_ptr = other.m_ptr;
                deleter = std::move(other.deleter);
                other.m_ptr = nullptr;
            }
            return *this;
        }

        ~UniquePtr() noexcept {
            if(m_ptr){
                deleter(m_ptr);
            }
        }
    
        UniquePtr(const UniquePtr& other) = delete;
        UniquePtr& operator=(const UniquePtr& other) = delete;

    public:
    	pointer get() const {
            return m_ptr;
        }

        deleter_type get_deleter() const {
            return deleter;
        }

        [[nodiscard]] pointer release() {
            return exchange(m_ptr, nullptr); 
        }

        void reset(pointer ptr = nullptr) {
            pointer old = exchange(m_ptr, ptr);
            if(old){
                deleter(old);
            }
        }
        // thats in the standard
        void swap(UniquePtr& right) noexcept {
            pointer temp = m_ptr;
            m_ptr = right.m_ptr;
            right.m_ptr = temp;
            
            deleter_type temp2 = deleter;
            deleter = right.deleter;
            right.deleter = temp2;
        }

    public:
        pointer operator->() const {
            return m_ptr;
        }

        reference operator*() const {
            return *m_ptr;
        }

        operator const T* () const {
            return m_ptr;
        }

        explicit operator bool () const {
            return (m_ptr != nullptr);
        }

        /* friend std::ostream& operator << (std::ostream& os, const UniquePtr& uni){
            return os << uni.m_ptr;
        } */

    private:
        template<typename Ty, typename Other = Ty>
        Ty exchange(Ty& val, Other&& newVal) noexcept (
            std::conjunction_v<std::is_nothrow_move_constructible<Ty>, std::is_nothrow_assignable<Ty&, Other>>) {
            
            Ty old = (Ty&&) val;
            val = (Other&&) newVal;
            return old;
        }

    private:
        pointer m_ptr;
        deleter_type deleter;
};

template <typename T, typename... Types>
[[nodiscard]] UniquePtr<T> make_UniquePtr(Types&&... Args) {
    return UniquePtr<T>(new T(std::forward<Types>(Args)...));
}

/**
* 
*  ---------------------------------------- ARRAY TYPE ----------------------------------------
*  
**/ 

/* template<class T>
class UniquePtr<T[]> {
    
    using pointer = T*;
    using reference = T&;
    using valueType = T;
    
    public:
        
        //UniquePtr();
        explicit UniquePtr(T* ptr = nullptr) : m_ptr(ptr) {}
        
        UniquePtr(UniquePtr&& other) noexcept {
            m_ptr = other.m_ptr;
            other.m_ptr = nullptr;
        }

        UniquePtr& operator=(UniquePtr&& other) noexcept {
            if (this != &other) {
                delete[] m_ptr;
                m_ptr = other.m_ptr;
                other.m_ptr = nullptr;
            }
            return *this;
        }

        ~UniquePtr() {
            delete[] m_ptr;
        }
    
        UniquePtr(const UniquePtr& other) = delete;
        UniquePtr& operator=(const UniquePtr& other) = delete;

    public:
    	pointer get() const {
            return m_ptr;
        }

        [[nodiscard]] pointer release() {
            return exchange(m_ptr, nullptr);
            //valueType temp = m_ptr;
            //m_ptr = nullptr;
            //return temp;
        }

        void reset(pointer ptr = nullptr){
            pointer old = exchange(m_ptr, ptr);
            if(old){
                delete[] old;
            }
        }
        // thats in the standard
        void swap(UniquePtr& right) noexcept {
            pointer temp = m_ptr;
            m_ptr = right.m_ptr;
            right.m_ptr = temp;
        }

    public:
        pointer operator->() const {
            return m_ptr;
        }

        reference operator*() const {
            return *m_ptr;
        }

        reference operator[](size_t n) const {
            return *(m_ptr + n);
        }

        operator const T* () const {
            return m_ptr;
        }

        explicit operator bool () const {
            return (m_ptr != nullptr);
        }

    private:
        template<typename Ty, typename Other = Ty>
        Ty exchange(Ty& val, Other&& newVal) noexcept {
            Ty old = (Ty&&) val;
            val = (Other&&) newVal;
            return old;
        }

    private:
        pointer m_ptr;
}; */

/* template<typename Ty>
struct remove_extent {
    using type = Ty;
};

template<typename Ty>
using remove_extent_t = typename remove_extent<Ty>::type;
 */

/* template <typename T>
[[nodiscard]] UniquePtr<T> make_UniquePtr(const size_t size) {
    using underlyingTypeOfArray = remove_extent_t<T>;
    return UniquePtr<T>(new underlyingTypeOfArray[size]());
}

 */
