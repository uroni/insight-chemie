#include "simfuncts.h"
#include "settings.h"

_u32 getoelektrons(_u32 uEls)
{
        if(uEls<3)
                return uEls;
        else if(uEls>2&&uEls<11)
                return uEls-2;
        else if(uEls>10&&uEls<19)
                return uEls-10;
        else
                return uEls-18;
}

core::vector3df randPos(void)
{
        return core::vector3df(rand()%(_u32)sandboxsize.X-sandboxsize.X/2,rand()%(_u32)sandboxsize.Y-sandboxsize.Y/2,rand()%(_u32)sandboxsize.Z-sandboxsize.Z/2);
}

int round(float f)
{
  return (int)(f<0?f-0.5f:f+0.5f);
}
