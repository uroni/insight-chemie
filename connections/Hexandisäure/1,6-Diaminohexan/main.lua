local hex=GetMoleculeByID(id1);
local dia=GetMoleculeByID(id2);

Disconnect( hex.c5, hex.o2 );
Disconnect( hex.c6, hex.o3 );

Disconnect( dia.a1, dia.h15 );
Disconnect( dia.a2, dia.h13 );

Connect( dia.h15, hex.o2 );
Connect( dia.h13, hex.o3 );

Connect( dia.a1, hex.c5 );

local r1=CreateAtom("Rest");
local r2=CreateAtom("Rest");

Connect( dia.a2, r1);
Connect( hex.c6, r2);

SetMoleculeName(dia.h15, "Wasser");
SetMoleculeName(dia.h13, "Wasser");

SetMoleculeName(dia.a2, "Nylon-6,6");