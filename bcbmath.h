#include <math.h>

#if defined(__BORLANDC__) || defined(__BCPLUSPLUS__)

#ifndef BCBMATH_H
#define BCBMATH_H
//#ifdef borland

int _RTLENTRY _EXPFUNC _matherr(struct _exception* e)
{

                e->retval=1.0;

                return 1;

}
#endif

#endif