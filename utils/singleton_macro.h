#ifndef _SINGLETON_MACRO_H_
#define _SINGLETON_MACRO_H_

#define DISALLOW_COPY_AND_ASSIGN(classname)                                    \
private:                                                                       \
    classname(const classname &);                                              \
    classname &operator=(const classname &);

#define DISALLOW_IMPLICIT_CONSTRUCTORS(classname)                              \
private:                                                                       \
    classname();                                                               \
    ~classname();                                                              \
    DISALLOW_COPY_AND_ASSIGN(classname);

#define DECLARE_SINGLETON(classname)                                           \
public:                                                                        \
    static classname *instance()                                               \
    {                                                                          \
        static classname instance;                                             \
        return &instance;                                                      \
    }                                                                          \
    DISALLOW_IMPLICIT_CONSTRUCTORS(classname)                                  \
private:

#endif // _SINGLETON_MACRO_H_