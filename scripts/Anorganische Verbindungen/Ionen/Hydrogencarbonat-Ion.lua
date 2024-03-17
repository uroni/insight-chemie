local name="Hydrogencarbonat-Ion";
local m={};

m.a0=CreateAtom("Kohlenstoff", name);
m.a1=CreateAtom("Sauerstoff", name);
m.a2=CreateAtom("Sauerstoff", name);
m.a3=CreateAtom("Sauerstoff", name);
m.a4=CreateAtom("Wasserstoff", name);
Connect(m.a0, m.a1);
Connect(m.a0, m.a1);
Connect(m.a0, m.a3);
Connect(m.a0, m.a2);
Connect(m.a2, m.a4);

RegisterMolecule(name, m);
