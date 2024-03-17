local m={};

m.a0=CreateAtom("Kohlenstoff", "Methan");
m.a1=CreateAtom("Wasserstoff", "Methan");
m.a2=CreateAtom("Wasserstoff", "Methan");
m.a3=CreateAtom("Wasserstoff", "Methan");
m.a4=CreateAtom("Wasserstoff", "Methan");
m.a5=CreateAtom("Kohlenstoff", "");
m.a6=CreateAtom("Wasserstoff", "");
m.a7=CreateAtom("Wasserstoff", "");
Connect(m.a2, m.a0);
Connect(m.a3, m.a0);
Connect(m.a4, m.a0);
Connect(m.a0, m.a5);
Connect(m.a5, m.a1);
Connect(m.a5, m.a7);
Connect(m.a5, m.a6);
