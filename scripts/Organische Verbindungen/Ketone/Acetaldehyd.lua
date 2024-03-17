local name="Acetaldehyd";
local m={};

m.a0=CreateAtom("Kohlenstoff", name);
m.a1=CreateAtom("Kohlenstoff", name);
m.a2=CreateAtom("Wasserstoff", name);
m.a3=CreateAtom("Wasserstoff", name);
m.a4=CreateAtom("Wasserstoff", name);
m.a5=CreateAtom("Wasserstoff", name);
m.a6=CreateAtom("Sauerstoff", name);
Connect(m.a1, m.a3);
Connect(m.a1, m.a4);
Connect(m.a5, m.a1);
Connect(m.a1, m.a0);
Connect(m.a0, m.a2);
Connect(m.a0, m.a6);
Connect(m.a0, m.a6);

RegisterMolecule(name, m);
