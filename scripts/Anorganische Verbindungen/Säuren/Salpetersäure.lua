local name="";
local m={};

m.a0=CreateAtom("Stickstoff", name);
m.a1=CreateAtom("Sauerstoff", name);
m.a2=CreateAtom("Sauerstoff", name);
m.a3=CreateAtom("Sauerstoff", name);
m.a4=CreateAtom("Wasserstoff", name);
Connect(m.a0, m.a2);
Connect(m.a1, m.a0);
Connect(m.a0, m.a3);
Connect(m.a0, m.a2);
Connect(m.a3, m.a4);

RegisterMolecule(name, m);
