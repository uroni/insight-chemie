#include "irrlicht/irrlicht.h"

class EventReceiver : public irr::IEventReceiver
{
public:
	virtual bool OnEvent(irr::SEvent event);
};