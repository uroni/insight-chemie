local name="�ls�ure";
local m={};

m.c1=CreateAtom("Kohlenstoff", name, 881.111, 1565.11, -1912.52);
m.c2=CreateAtom("Kohlenstoff", name, 509.467, 950.641, -1371.32);
m.c3=CreateAtom("Kohlenstoff", name, 171.618, 191.651, -1676.33);
m.c4=CreateAtom("Kohlenstoff", name, 423.697, -452.446, -1090.42);
m.c5=CreateAtom("Kohlenstoff", name, 646.373, -46.8693, -276.423);
m.c6=CreateAtom("Kohlenstoff", name, 1428.01, -456.193, -149.296);
m.c7=CreateAtom("Kohlenstoff", name, 1844.96, -397, 649.157);
m.c8=CreateAtom("Kohlenstoff", name, 1800.37, -1222.62, 999.052);
m.c9=CreateAtom("Kohlenstoff", name, 250.177, -1489.38, 1462.25);
m.c10=CreateAtom("Kohlenstoff", name, -422.542, -919.242, 1579.97);
m.c11=CreateAtom("Kohlenstoff", name, -1253.79, -1165.39, 1443.43);
m.c12=CreateAtom("Kohlenstoff", name, -1539.74, -1709.74, 2118.17);
m.c13=CreateAtom("Kohlenstoff", name, -2430.48, -1461.87, 1974.95);
m.c14=CreateAtom("Kohlenstoff", name, -2496.79, -1131.76, 1098.99);
m.c15=CreateAtom("Kohlenstoff", name, -2275.26, -165.426, 1130.61);
m.c16=CreateAtom("Kohlenstoff", name, -2811.56, 463.942, 1678.32);
m.h1=CreateAtom("Wasserstoff", name, 1017.66, 1504.39, -2643.92);
m.h2=CreateAtom("Wasserstoff", name, 1560.94, 1693.01, -1539.74);
m.h3=CreateAtom("Wasserstoff", name, 329.929, 2124.87, -1805.78);
m.h4=CreateAtom("Wasserstoff", name, 1087.7, 727.254, -936.787);
m.h5=CreateAtom("Wasserstoff", name, -129.764, 1290.54, -1150.41);
m.h6=CreateAtom("Wasserstoff", name, 495.072, 59.9881, -2392.67);
m.h7=CreateAtom("Wasserstoff", name, -587.193, 210.334, -1695.99);
m.h8=CreateAtom("Wasserstoff", name, -140.13, -958.058, -988.615);
m.h9=CreateAtom("Wasserstoff", name, 1068.78, -782.829, -1428.5);
m.h10=CreateAtom("Wasserstoff", name, 137.244, -204.547, 237.606);
m.h11=CreateAtom("Wasserstoff", name, 764.311, 696.996, -418.788);
m.h12=CreateAtom("Wasserstoff", name, 1288.67, -1205.9, -248.188);
m.h13=CreateAtom("Wasserstoff", name, 1915.62, -92.9536, -633.665);
m.h14=CreateAtom("Wasserstoff", name, 1487.62, 109.78, 1084.92);
m.h15=CreateAtom("Wasserstoff", name, 2593.99, -247.034, 518.815);
m.h16=CreateAtom("Wasserstoff", name, 1581.28, -1186.55, 1727.15);
m.h17=CreateAtom("Wasserstoff", name, 2475.1, -1591.71, 890.726);
m.h18=CreateAtom("Wasserstoff", name, 1669.2, -1759.07, -137.208);
m.h19=CreateAtom("Wasserstoff", name, -282.209, -2137.24, 346.339);
m.h20=CreateAtom("Wasserstoff", name, 892.003, -1081.97, 1582.01);
m.h21=CreateAtom("Wasserstoff", name, 95.4171, -2096.11, 1903.92);
m.h22=CreateAtom("Wasserstoff", name, -379.566, -872.004, 2373.32);
m.h23=CreateAtom("Wasserstoff", name, -297.381, -287.787, 1178.58);
m.h24=CreateAtom("Wasserstoff", name, -1616.84, -478.76, 1617.98);
m.h25=CreateAtom("Wasserstoff", name, -1365.77, -1478.37, 810.24);
m.h26=CreateAtom("Wasserstoff", name, -1450.96, -2449.1, 2100.79);
m.h27=CreateAtom("Wasserstoff", name, -1295.67, -1422.08, 2826.03);
m.h28=CreateAtom("Wasserstoff", name, -2959.1, -1974.73, 2172.29);
m.h29=CreateAtom("Wasserstoff", name, -2510.2, -770.736, 2379.72);
m.h30=CreateAtom("Wasserstoff", name, -3241.42, -1076.58, 875.58);
m.h31=CreateAtom("Wasserstoff", name, -2053.65, -1553.96, 679.426);
m.h32=CreateAtom("Wasserstoff", name, -2479.54, 93.7789, 386.53);
m.h33=CreateAtom("Wasserstoff", name, -1560.17, -49.74, 1353.77);
m.o1=CreateAtom("Sauerstoff", name, -2643.8, 898.407, 2450.5);
m.h34=CreateAtom("Wasserstoff", name, -3105.53, 482.104, 2631.68);
m.o2=CreateAtom("Sauerstoff", name, -3173.44, 1169.9, 1236.46);
m.c17=CreateAtom("Kohlenstoff", name, 1211.21, -1635.2, 461.683);
m.c18=CreateAtom("Kohlenstoff", name, 350.968, -1818.07, 634.904);
Connect(m.c1, m.h1);
Connect(m.c1, m.c2);
Connect(m.c1, m.h2);
Connect(m.c1, m.h3);
Connect(m.c2, m.c3);
Connect(m.c2, m.h4);
Connect(m.c2, m.h5);
Connect(m.c3, m.c4);
Connect(m.c3, m.h6);
Connect(m.c3, m.h7);
Connect(m.c4, m.c5);
Connect(m.c4, m.h8);
Connect(m.c4, m.h9);
Connect(m.c5, m.c6);
Connect(m.c5, m.h10);
Connect(m.c5, m.h11);
Connect(m.c6, m.c7);
Connect(m.c6, m.h12);
Connect(m.c6, m.h13);
Connect(m.c7, m.c8);
Connect(m.c7, m.h14);
Connect(m.c7, m.h15);
Connect(m.c8, m.h16);
Connect(m.c8, m.h17);
Connect(m.c9, m.c10);
Connect(m.c9, m.h20);
Connect(m.c9, m.h21);
Connect(m.c10, m.c11);
Connect(m.c10, m.h22);
Connect(m.c10, m.h23);
Connect(m.c11, m.c12);
Connect(m.c11, m.h24);
Connect(m.c11, m.h25);
Connect(m.c12, m.c13);
Connect(m.c12, m.h26);
Connect(m.c12, m.h27);
Connect(m.c13, m.c14);
Connect(m.c13, m.h28);
Connect(m.c13, m.h29);
Connect(m.c14, m.c15);
Connect(m.c14, m.h30);
Connect(m.c14, m.h31);
Connect(m.c15, m.c16);
Connect(m.c15, m.h32);
Connect(m.c15, m.h33);
Connect(m.o1, m.h34);
Connect(m.c16, m.o1);
Connect(m.c16, m.o2);
Connect(m.c16, m.o2);
Connect(m.c9, m.c18);
Connect(m.c17, m.c18);
Connect(m.c17, m.c18);
Connect(m.c8, m.c17);
Connect(m.c17, m.h18);
Connect(m.c18, m.h19);

RegisterMolecule(name, m);
