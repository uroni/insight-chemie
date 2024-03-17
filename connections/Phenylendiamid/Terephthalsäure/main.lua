local ph=GetMoleculeByID(id1);
local te=GetMoleculeByID(id2);

Disconnect( te.o2, te.c7 );
Disconnect( ph.a1, ph.h5);

Connect( te.c7, ph.a1 );
Connect( te.o2, ph.h5 );

SetMoleculeName(te.c7, "Kevlar - Teilabschnitt" );
SetMoleculeName(te.o2, "Wasser" );
