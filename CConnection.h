#ifndef CCONNECTION_H
#define CCONNECTION_H
//------------------------------------------------------------

#include "types.h"
#include "CAtom.h"

#include "irrlicht/irrlicht.h"

#include <vector>

class CAtom;
class CElektronBank;

class CConnection
{
public:
        CConnection(CAtom *p_A1, CAtom *p_A2, f32 scale);
        ~CConnection(void);

        void Step(_f32 time);
        void StepBanks(_f32 time, const std::vector<CElektronBank*> &banks, const  std::vector<CConnection*> &connections, CAtom* a1, CAtom* a2);

        irr::scene::ISceneNode* getNode(void);
        core::vector3df getNodePosition(void);
        core::vector3df getPosition(void);
        void setPosition(core::vector3df npos);
        void setFreeze(int pFreeze);
        bool isFrozen(void);

        void addOtherConnection(CConnection *connection);

        CAtom* getAtom1(void);
        CAtom* getAtom2(void);

        void addBankA1(CElektronBank* bank);
        void addBankA2(CElektronBank* bank);
        void ResetBanks(void);
        bool RemoveBank(CElektronBank* bank);

        void addConnectionA1(CConnection* connection);
        void addConnectionA2(CConnection* connection);

        bool removeConnection(CConnection* connection);

        void setChanging(bool b);
        void setCounting(bool b);
        bool getCounting(void);
        void setDouble(int b);
        int getDouble(void);

private:
        CAtom *pA1;
        CAtom *pA2;
        irr::scene::ISceneNode *node;
        irr::core::vector3df position;
        f32 fScale;
        f32 fDistance;
        bool changing;
        bool counting;
        int conn_double;
        f32 chtime;

        std::vector<CConnection*> connections;
        std::vector<CConnection*> connections1;
        std::vector<CConnection*> connections2;
        std::vector<CElektronBank*> banks1;
        std::vector<CElektronBank*> banks2;

        int texture;

        int freeze;
};

//------------------------------------------------------------
#endif