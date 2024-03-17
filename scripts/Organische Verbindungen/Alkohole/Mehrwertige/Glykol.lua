local name="Glykol";
local m={};

m.a0=CreateAtom("Kohlenstoff", name);
m.a1=CreateAtom("Kohlenstoff", name);
m.a2=CreateAtom("Sauerstoff", name);
m.a3=CreateAtom("Wasserstoff", name);
m.a4=CreateAtom("Sauerstoff", name);
m.a5=CreateAtom("Wasserstoff", name);
m.a6=CreateAtom("Wasserstoff", name);
m.a7=CreateAtom("Wasserstoff", name);
m.a8=CreateAtom("Wasserstoff", name);
m.a9=CreateAtom("Wasserstoff", name);
Connect(m.a2, m.a3);
Connect(m.a4, m.a5);
Connect(m.a0, m.a1);
Connect(m.a1, m.a2);
Connect(m.a0, m.a4);
Connect(m.a0, m.a8);
Connect(m.a0, m.a7);
Connect(m.a1, m.a9);
Connect(m.a1, m.a6);

RegisterMolecule(name, m);
