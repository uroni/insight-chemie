local ala=GetMoleculeByID(id1);
local gly=GetMoleculeByID(id2);

--Wasserstoff abtrennen
Disconnect( gly.a1, gly.h3 );

--Hydroxid-Gruppe abtrennen
Disconnect( ala.c2, ala.o2 );

--Wasser verbinden
Connect( gly.h3, ala.o2 );

--Die Aminosäuren verbinden
Connect( gly.a1, ala.c2 );

--umbennen
SetMoleculeName( gly.a1, "Alanylglycin" );

SetMoleculeName( gly.h3, "Wasser" );

