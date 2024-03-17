#ifndef CELEKTRONBANK_H
#define CELEKTRONBANK_H
//-----------------------------------------------------

#include "irrlicht/irrlicht.h"
#include <vector>
#include "types.h"

using namespace irr;

class CConnection;
class CAtom;

class CElektronBank
{
public:
        CElektronBank(core::vector3df v_corepos, bool b_full, f32 f_distance, f32 f_scale, CAtom* pOwner);
        ~CElektronBank(void);

        void addOtherBank(CElektronBank *bank);
        void addConnection(CConnection *connection);

        bool removeConnection(CConnection *connection);

        bool removeOtherBank(CElektronBank *bank);

        bool isFull(void);
        void Step(_f32 time);
        void setFull(bool b);
        scene::ISceneNode* getNode(void);

        core::vector3df getPosition(void);
        void setPosition(core::vector3df nposition);

private:
        core::vector3df corepos;
        bool full;
        f32 bbsize;
        f32 scale;
        CAtom* owner;

        core::vector3df position;

        std::vector<CElektronBank*> banks;
        std::vector<CConnection*> connections;

        scene::ISceneNode *node;
};

//-----------------------------------------------------
#endif



