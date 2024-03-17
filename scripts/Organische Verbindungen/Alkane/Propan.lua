local name="Propan";
local m={};

m.a0=CreateAtom("Kohlenstoff", name);
m.a1=CreateAtom("Wasserstoff", name);
m.a2=CreateAtom("Wasserstoff", name);
m.a3=CreateAtom("Wasserstoff", name);
m.a4=CreateAtom("Wasserstoff", name);
m.a5=CreateAtom("Kohlenstoff", name);
m.a6=CreateAtom("Wasserstoff", name);
m.a7=CreateAtom("Wasserstoff", name);
m.a8=CreateAtom("Kohlenstoff", name);
m.a9=CreateAtom("Wasserstoff", name);
m.a10=CreateAtom("Wasserstoff", name);
Connect(m.a2, m.a0);
Connect(m.a3, m.a0);
Connect(m.a0, m.a5);
Connect(m.a5, m.a1);
Connect(m.a5, m.a7);
Connect(m.a5, m.a6);
Connect(m.a0, m.a8);
Connect(m.a8, m.a4);
Connect(m.a8, m.a9);
Connect(m.a8, m.a10);

RegisterMolecule(name, m);
