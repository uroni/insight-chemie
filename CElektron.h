#include "irrlicht/irrlicht.h"
#include <vector>

using namespace std;
using namespace irr;

class CElektron
{
public:
        CElektron(scene::ISceneNode* p_node, f32 f_distance, core::vector3df v_corepos, f32 f_speed);

        void setCorePosition(core::vector3df v_corepos);

        void addOtherElektron(CElektron* p_elektron);

        scene::ISceneNode* getNode(void);

        void Step(u32 time);
private:

        f32 distance;
        core::vector3df corepos;

        core::vector3df velocity;

        f32 speed;
        f32 coreforce;

        f32 scale;


        scene::ISceneNode* node;

        vector<CElektron*> elektrons;
};
