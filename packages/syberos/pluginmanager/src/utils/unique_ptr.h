#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H

namespace Utils {

template<typename T>
struct DefaultDeleter
{
    void operator()(T *p)
    {
        if (p) {
            delete p;
            p = nullptr;
        }
    }
};


template<typename T, typename Deleter = DefaultDeleter<T>>
class unique_ptr
{
public:
    //construct
    unique_ptr(T *pT = nullptr);
    //destroy
    ~unique_ptr();
    //reset
    void reset(T *p = nullptr);
    //release the own of the pointer
    T *release();
    //get the pointer
    T *get();
    //convert unique_ptr to bool
    operator bool() const;
    //overload for operator *
    T &operator*();
    //overload for operator ->
    T *operator->();

//not allow copyable
private:
//    unique_ptr(const unique_ptr &);
    unique_ptr &operator=(const unique_ptr &);

    //pointer
    T *m_pT;
    //deleter
    Deleter m_deleter;
    //call deleter
    void del();
};

}
#endif // UNIQUE_PTR_H
