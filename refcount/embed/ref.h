/* C11 and __STDC_NO_ATOMICS__ not defined */
#include <stdatomic.h>

/* follow design of kernel refcount, reference: http://www.kroah.com/linux/talks/ols_2004_kref_paper/Reprint-Kroah-Hartman-OLS2004.pdf */
struct ref {
  atomic_int count;
  void (*release)(struct ref *r);
};

void ref_init(struct ref *r, void (*release)(struct ref *r));
void ref_get(struct ref *r);
void ref_put(struct ref *r);

