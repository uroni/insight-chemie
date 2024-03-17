#include "irrlicht/irrlicht.h"
#include <vector>

using namespace std;
using namespace irr;


class CProton
{
public:
        CProton(scene::ISceneNode* p_node);

        void addOtherNeutron(scene::ISceneNode* p_node);
        void addOtherProton(scene::ISceneNode* p_node);

        void Step(u32 time);

        scene::ISceneNode* getNode(void);

private:
        scene::ISceneNode* node;

        vector<scene::ISceneNode*> neutrons;
        vector<scene::ISceneNode*> protons;
};