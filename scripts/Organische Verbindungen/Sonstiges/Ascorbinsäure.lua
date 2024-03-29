local name="Ascorbinsäure";
local m={};

m.c1=CreateAtom("Kohlenstoff", name, -2459.38, 6387.93, -396.543);
m.c2=CreateAtom("Kohlenstoff", name, -1237.4, 7024.47, 112.194);
m.c3=CreateAtom("Kohlenstoff", name, -2478.18, 7263.32, -724.909);
m.c4=CreateAtom("Kohlenstoff", name, -1767.1, 7613.32, -296.03);
m.o1=CreateAtom("Sauerstoff", name, -1751.45, 6328.46, 273.662);
m.o2=CreateAtom("Sauerstoff", name, -2945.42, 5678.92, -330.843);
m.o3=CreateAtom("Sauerstoff", name, -1521.83, 8421.78, -530.255);
m.h1=CreateAtom("Wasserstoff", name, -1110.88, 8199.58, 11.0525);
m.o4=CreateAtom("Sauerstoff", name, -3105.38, 7530.78, -1248.43);
m.h2=CreateAtom("Wasserstoff", name, -2566.75, 7943.23, -1449.32);
m.c5=CreateAtom("Kohlenstoff", name, -727.928, 6601.1, -773.439);
m.o5=CreateAtom("Sauerstoff", name, 128.887, 7004.22, -832.622);
m.h3=CreateAtom("Wasserstoff", name, 96.9437, 6732.28, -243.89);
m.h4=CreateAtom("Wasserstoff", name, -621.992, 7256.07, 508.325);
m.h5=CreateAtom("Wasserstoff", name, -561.801, 5803.85, -894.116);
m.c6=CreateAtom("Kohlenstoff", name, -926.722, 6951.33, -1671.86);
m.h6=CreateAtom("Wasserstoff", name, -800.001, 7719.33, -1705.81);
m.h7=CreateAtom("Wasserstoff", name, -1487.54, 6618.38, -2074.93);
m.o6=CreateAtom("Sauerstoff", name, -201.496, 6726.73, -2263.78);
m.h8=CreateAtom("Wasserstoff", name, -308.284, 6178.71, -1923.29);
Connect(m.c4, m.c2);
Connect(m.c3, m.c4);
Connect(m.c1, m.c3);
Connect(m.o1, m.c2);
Connect(m.c1, m.o1);
Connect(m.c1, m.o2);
Connect(m.c1, m.o2);
Connect(m.o3, m.h1);
Connect(m.o4, m.h2);
Connect(m.c3, m.o4);
Connect(m.o3, m.c4);
Connect(m.c3, m.c4);
Connect(m.o5, m.h3);
Connect(m.c5, m.o5);
Connect(m.c2, m.c5);
Connect(m.c2, m.h4);
Connect(m.c5, m.h5);
Connect(m.c6, m.h6);
Connect(m.h7, m.c6);
Connect(m.c5, m.c6);
Connect(m.o6, m.h8);
Connect(m.c6, m.o6);

RegisterMolecule(name, m);
