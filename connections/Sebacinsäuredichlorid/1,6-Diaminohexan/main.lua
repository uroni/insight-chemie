local seba=GetMoleculeByID(id1);
local dia=GetMoleculeByID(id2);

Disconnect( dia.a1, dia.h15 );
Disconnect( dia.a2, dia.h13 );

Disconnect( seba.a1, seba.c1 );
Disconnect( seba.a2, seba.c10 );

Connect( dia.h15, seba.a1 );
Connect( dia.h13, seba.a2 );

Connect( dia.a1, seba.c1 );

local r1=CreateAtom("Rest");
local r2=CreateAtom("Rest");

Connect( dia.a2, r1 );
Connect( seba.c10, r2 );

SetMoleculeName(dia.h15, "Chlorwasserstoff" );
SetMoleculeName(dia.h13, "Chlorwasserstoff" );

SetMoleculeName(dia.a2, "Nylon-6,10" );
