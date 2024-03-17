local name="Phenylendiamid";
local m={};

m.c1=CreateAtom("Kohlenstoff", name, -2463.36, 207.405, 1259.75);
m.c2=CreateAtom("Kohlenstoff", name, -2031.1, -461.144, 1675.22);
m.h1=CreateAtom("Wasserstoff", name, -2234.43, -1126.87, 2002.23);
m.c3=CreateAtom("Kohlenstoff", name, -2237.11, 980.779, 860.492);
m.c4=CreateAtom("Kohlenstoff", name, -1142.81, -486.409, 1814.48);
m.c5=CreateAtom("Kohlenstoff", name, -907.616, 296.641, 1427.03);
m.c6=CreateAtom("Kohlenstoff", name, -1341.52, 977.115, 989.995);
m.h2=CreateAtom("Wasserstoff", name, -874.958, -1103.03, 2184.5);
m.h3=CreateAtom("Wasserstoff", name, -2824.59, 1381.19, 563.336);
m.h4=CreateAtom("Wasserstoff", name, -758.047, 1446.45, 823.803);
m.a1=CreateAtom("Stickstoff", name, -3325.52, 319.197, 1110.93);
m.a2=CreateAtom("Stickstoff", name, -122.123, 683.067, 1332.71);
m.h5=CreateAtom("Wasserstoff", name, -3196.86, 1062.96, 1121.63);
m.h6=CreateAtom("Wasserstoff", name, 173.087, -5.21051, 1273.39);
m.h7=CreateAtom("Wasserstoff", name, -3412.82, 206.16, 1859.54);
m.h8=CreateAtom("Wasserstoff", name, -319.337, 792.646, 611.413);
Connect(m.c1, m.c2);
Connect(m.c1, m.c2);
Connect(m.c2, m.h1);
Connect(m.c1, m.c3);
Connect(m.c2, m.c4);
Connect(m.c3, m.c6);
Connect(m.c3, m.c6);
Connect(m.c4, m.c5);
Connect(m.c4, m.c5);
Connect(m.c5, m.c6);
Connect(m.c4, m.h2);
Connect(m.c3, m.h3);
Connect(m.c6, m.h4);
Connect(m.c1, m.a1);
Connect(m.c5, m.a2);
Connect(m.a1, m.h5);
Connect(m.h7, m.a1);
Connect(m.a2, m.h6);
Connect(m.a2, m.h8);

RegisterMolecule(name, m);