#include <stddef.h>


/* Using __typeof__ rather than typeof, because this file is compiled in ISO C */
#define container_of(ptr, type, member) ({                      \
        const  __typeof__( ((type *)0)->member ) *__mptr = (ptr);    \
        (type *)((char *)__mptr - offsetof(type,member));})

