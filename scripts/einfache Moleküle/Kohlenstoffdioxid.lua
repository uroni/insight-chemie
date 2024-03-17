local name="Kohlenstoffdioxid";
local m={};

m.a0=CreateAtom("Kohlenstoff", name);
m.a1=CreateAtom("Sauerstoff", name);
m.a2=CreateAtom("Sauerstoff", name);
Connect(m.a0, m.a2);
Connect(m.a0, m.a2);
Connect(m.a0, m.a1);
Connect(m.a0, m.a1);

RegisterMolecule(name, m);
