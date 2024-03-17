local name="Glycin";
local m={};

m.a1=CreateAtom("Stickstoff", name);
m.h1=CreateAtom("Wasserstoff", name);
m.h2=CreateAtom("Wasserstoff", name);
m.h3=CreateAtom("Wasserstoff", name);
m.c1=CreateAtom("Kohlenstoff", name);
m.c2=CreateAtom("Kohlenstoff", name);
m.o1=CreateAtom("Sauerstoff", name);
m.o2=CreateAtom("Sauerstoff", name);
m.h4=CreateAtom("Wasserstoff", name);
m.h5=CreateAtom("Wasserstoff", name);
Connect(m.a1, m.h3);
Connect(m.a1, m.h1);
Connect(m.a1, m.c1);
Connect(m.o1, m.c2);
Connect(m.o1, m.c2);
Connect(m.o2, m.c2);
Connect(m.c1, m.c2);
Connect(m.c1, m.h5);
Connect(m.c1, m.h4);
Connect(m.o2, m.h2);

RegisterMolecule(name, m);
