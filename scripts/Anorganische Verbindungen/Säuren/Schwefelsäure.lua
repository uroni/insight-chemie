local name="";
local m={};

m.a0=CreateAtom("Schwefel", name);
m.a1=CreateAtom("Sauerstoff", name);
m.a2=CreateAtom("Sauerstoff", name);
m.a3=CreateAtom("Sauerstoff", name);
m.a4=CreateAtom("Sauerstoff", name);
m.a5=CreateAtom("Wasserstoff", name);
m.a6=CreateAtom("Wasserstoff", name);
Connect(m.a0, m.a4);
Connect(m.a3, m.a0);
Connect(m.a0, m.a1);
Connect(m.a0, m.a2);
Connect(m.a0, m.a2);
Connect(m.a0, m.a1);
Connect(m.a3, m.a5);
Connect(m.a4, m.a6);

RegisterMolecule(name, m);
