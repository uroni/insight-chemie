local name="";
local m={};

m.a0=CreateAtom("Stickstoff", name);
m.a1=CreateAtom("Wasserstoff", name);
m.a2=CreateAtom("Wasserstoff", name);
m.a3=CreateAtom("Wasserstoff", name);
Connect(m.a0, m.a3);
Connect(m.a0, m.a2);
Connect(m.a0, m.a1);

RegisterMolecule(name, m);
