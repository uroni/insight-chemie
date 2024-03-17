#ifndef CATOM_H
#define CATOM_H
//--------------------------------------------------------------------


#include "types.h"
#include "CNeutron.h"
#include "CProton.h"
#include "CElektron.h"
#include "CElektronBank.h"
#include "CConnection.h"

#include "irrlicht/irrlicht.h"
#include <vector>
#include <string>

using namespace irr;
using namespace std;


struct sElementData
{
        _u32 num_elektrons;
        _u32 num_protons;
        _u32 num_neutrons;

        _f32 elektroneg;
        _f32 bbsize;

        irr::video::ITexture *texture;
        _u32 modelsize;

        _u32 normal_elektrons;

        std::string name;

        bool element;
};
        


class CAtom
{
public:
        CAtom(sElementData cs_emd, bool bdetailed, int pID, int posx, int posy, int posz, std::string pName);
        ~CAtom(void);

        void PreStep(void);
        void StepKern(f32 time);
        void PostStep(void);

        sElementData getElementData(void);

        core::vector3df getPosition(void);
        core::vector3df getOldPosition(void);
        void setPosition(core::vector3df newpos);

        void addConnection(CConnection* connection);

        void ReconfigureConnections(void);

        size_t NumConnections(void);
        CConnection* getConnection(size_t num);

        int getTotalConnectionNum(std::vector<CAtom*> *exclude, bool *inRing=NULL);

        bool RemoveBank(CElektronBank* bank);
        bool removeConnection(CConnection* connection, int elektrons=1);

        int getCharge(void);

        int getID(void);
        int getMoleculeID(void);

        void setMoleculeID(int pID);

        void Reset(void);

        scene::ISceneNode* getNode(void);

        bool isOwningNode( scene::ISceneNode* node );

        std::string getName(void);
        void setName(std::string pName);

        vector<CElektronBank*> getBanks(void);

        bool isFrozen(void);

        void setFrozen(int fr);

        void ResetAge(void);

        void AddInvisibleConnection(int num);

        bool calculateConnPlane(void);
        void setConnPlane(const core::plane3d<f32> &plane, std::vector<CAtom*> *exclude);
        core::plane3d<f32> getConnPlane(void);
        bool isCalculatingPlane(void);

        f32 CalculateForce2Atom(f32 newforce);

        bool getCalculationDirection(void);

        void Hide(void);
        void Show(void);
        bool isVisible(void);

private:

        void Create(void);
        void Destroy(void);

        bool VerifyPosition(core::vector3df old_pos, core::vector3df pos);

        sElementData eldata;
        bool details;

        int num_invconn;


        vector<CNeutron*> neutrons;
        vector<CProton*>  protons;
        vector<CElektron*> elektrons;
        vector<CElektronBank*> banks;
        vector<CConnection*> connections;

        scene::ISceneNode* corenode;

        f32 oldforce;


        core::vector3df position;
        core::vector3df default_position;
        core::vector3df old_position;
        core::vector3df velocity;
        core::vector3df lastcenter;

        vector<core::vector3df> bank_positions;
        vector<core::vector3df> connection_positions;
        vector<f32> position_lengths;

        core::plane3d<f32> conn_plane;
        bool conn_plane_activ;
        bool calculated_plane;

        unsigned int age;
        int freeze;

        bool frozen;

        std::string name;

        int id;
        int molecule_id;

        bool calc_dir;

        bool visible;
};


//--------------------------------------------------------------------
#endif
