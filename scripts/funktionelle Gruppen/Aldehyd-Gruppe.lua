local name="Aldehyd-Gruppe";
local m={};

m.a0=CreateAtom("Kohlenstoff", name);
m.a1=CreateAtom("Sauerstoff", name);
m.a2=CreateAtom("Wasserstoff", name);
Connect(m.a1, m.a0);
Connect(m.a1, m.a0);
Connect(m.a0, m.a2);

RegisterMolecule(name, m);
