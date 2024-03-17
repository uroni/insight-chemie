local name="Oxalsäure";
local m={};

m.a0=CreateAtom("Kohlenstoff", name);
m.a1=CreateAtom("Sauerstoff", name);
m.a2=CreateAtom("Wasserstoff", name);
m.a3=CreateAtom("Sauerstoff", name);
m.a4=CreateAtom("Kohlenstoff", name);
m.a5=CreateAtom("Sauerstoff", name);
m.a6=CreateAtom("Wasserstoff", name);
m.a7=CreateAtom("Sauerstoff", name);
Connect(m.a1, m.a2);
Connect(m.a0, m.a1);
Connect(m.a0, m.a3);
Connect(m.a0, m.a3);
Connect(m.a5, m.a6);
Connect(m.a4, m.a5);
Connect(m.a4, m.a7);
Connect(m.a4, m.a7);
Connect(m.a0, m.a4);

RegisterMolecule(name, m);
