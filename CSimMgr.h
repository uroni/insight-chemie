#ifndef SIMMGR_H
#define SIMMGR_H
//-----

#include "CConnection.h"

#include <vector>
#include <map>
#include <deque>

namespace irr{ namespace scene{ class ISceneNode; }}

struct SConnectionFunction
{
        std::string name;
        std::vector<std::string> molecules;
};

struct SPresItem
{
        std::string title;
        std::string description;
        std::string data;
        std::string molname;
        bool newmol;
};

typedef std::map<std::string, std::vector<SConnectionFunction*> > conn_array;

class CElektronBank;

class CSimMgr
{
public:
        CSimMgr(void);
        ~CSimMgr(void);
        void init(void);
        int addAtom(sElementData sEmd, std::string pName, float posx, float posy, float posz);
        bool removeAtom(sElementData sEmd);
        bool removeAtom(int id);
        void removeAll(void);

        void setDetail(bool bdetail);

        void Simulate(f32 time);

        sElementData getElement(std::string name);

        bool LoadElements(std::string sfile);

        bool Connect(int atom1, int atom2);
        bool Disconnect(int atom1, int atom2, bool cap=false);
        void Disconnect(CConnection* connection, int cap=-1);

        CAtom* getAtom(int id);
        int getAtomIDbyName(std::string name);
        int getMolceuleIDbyName(std::string name);

        bool RemoveBank(CElektronBank* bank);

        CAtom* FindSceneNode(irr::scene::ISceneNode* node);

        core::aabbox3d<f32> getSandbox(void);

        void RotateWorld(core::vector3df rotation, core::vector3df center);
        void CenterWorld(void);

        std::string getSaveScript(void);

        std::vector<std::string> getMoleculeNames(void);
        std::map<std::string,bool> getMoleculeNamesMap(void);

        void getMolecule(CAtom* currnode, std::vector<CAtom*> &atoms);

        void addAction( std::string mname, std::string aname, std::string fname);
        std::string getActionFunction(std::string mname, std::string aname);
        std::vector<std::string> getActions(std::string mname);

        void addConnectionFunction(SConnectionFunction *conn);
        std::vector<SConnectionFunction*> getConnectionFunctions(std::string mname);

        void UnfreezeAll(bool reset_age=false);

        void setPresentationCapturingEnabled(bool b);
        void AddPresentationItem(std::string title, std::string description, std::string data);
        bool isCapturing(void);
        void ResetCapturing(void);
        void setCaptureMoleculeName(std::string pName);
        void CaptureNewMol(void);
        std::vector<int> getCapturedAtomIDs(void);
        std::string getCaptureID(int rID);
        bool allowPause(void);
        void setAllowPause(bool b);

        void SaveState(void);
        void getLastState(std::string &data, bool &last);

        bool isNewRing(CAtom* a1, CAtom* a2);

        void SeparateMolecules(void);

        void HideNewAtoms(bool b);

private:
        void ReconfigureConnections(void);
        void SimulateRejection(f32 time);
        core::vector3df RotateNodeAxis(core::vector3df pos,const core::vector3df &rot, const core::line3d<f32> &XLine, const core::line3d<f32> &YLine);

        bool bdetailed;

        std::vector<CAtom*> atoms;
        std::map<CAtom*, std::vector<CConnection*> > connected;

        std::vector<CConnection*> connections;

        irr::scene::ISceneNode* rootNode;

        int currid;
        std::map<std::string, sElementData> elements;

        std::map<std::string, std::map<std::string,std::string> > actions;
        conn_array conn_functs;

        bool pres_capturing;
        int pres_atom_id;
        std::map<int,int> pres_id_map;
        std::string pres_curr_name;
        
        std::deque<std::string> states;

        bool hidenewatoms;
        bool newcapturemol;
        bool allow_pause;
};

extern CSimMgr* simmgr;

#endif //SIMMGR_H
