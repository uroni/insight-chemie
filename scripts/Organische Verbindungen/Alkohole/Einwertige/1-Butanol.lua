local name="1-Butanol";
local m={};

m.a0=CreateAtom("Kohlenstoff", name);
m.a1=CreateAtom("Kohlenstoff", name);
m.a2=CreateAtom("Kohlenstoff", name);
m.a3=CreateAtom("Kohlenstoff", name);
m.a4=CreateAtom("Sauerstoff", name);
m.a5=CreateAtom("Wasserstoff", name);
m.a6=CreateAtom("Wasserstoff", name);
m.a7=CreateAtom("Wasserstoff", name);
m.a8=CreateAtom("Wasserstoff", name);
m.a9=CreateAtom("Wasserstoff", name);
m.a10=CreateAtom("Wasserstoff", name);
m.a11=CreateAtom("Wasserstoff", name);
m.a12=CreateAtom("Wasserstoff", name);
m.a13=CreateAtom("Wasserstoff", name);
m.a14=CreateAtom("Wasserstoff", name);
Connect(m.a0, m.a3);
Connect(m.a0, m.a1);
Connect(m.a1, m.a2);
Connect(m.a4, m.a5);
Connect(m.a2, m.a4);
Connect(m.a2, m.a7);
Connect(m.a2, m.a11);
Connect(m.a1, m.a10);
Connect(m.a1, m.a6);
Connect(m.a3, m.a8);
Connect(m.a3, m.a9);
Connect(m.a3, m.a12);
Connect(m.a0, m.a13);
Connect(m.a0, m.a14);

RegisterMolecule(name, m);

Pause();

Cap( m.a4 );
