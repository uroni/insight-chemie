local name="Carbonyl-Gruppe";
local m={};

m.a0=CreateAtom("Kohlenstoff", name);
m.a1=CreateAtom("Sauerstoff", name);
Connect(m.a1, m.a0);
Connect(m.a1, m.a0);

RegisterMolecule(name, m);
