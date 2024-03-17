local name="Methan";
local m={};

m.a0=CreateAtom("Kohlenstoff", name);
m.a1=CreateAtom("Wasserstoff", name);
m.a2=CreateAtom("Wasserstoff", name);
m.a3=CreateAtom("Wasserstoff", name);
m.a4=CreateAtom("Wasserstoff", name);
Connect(m.a0, m.a1);
Connect(m.a2, m.a0);
Connect(m.a3, m.a0);
Connect(m.a4, m.a0);

RegisterMolecule(name, m);
