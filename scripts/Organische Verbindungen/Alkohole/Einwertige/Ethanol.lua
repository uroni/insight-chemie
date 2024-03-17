local name="Ethanol";

local m={};

m.c1=CreateAtom("Kohlenstoff",name);
m.c2=CreateAtom("Kohlenstoff",name);
m.oh=CreateHydroxid();

m.h1=CreateAtom("Wasserstoff");
m.h2=CreateAtom("Wasserstoff");
m.h3=CreateAtom("Wasserstoff");
Connect(m.h1, m.c1 );
Connect(m.h2, m.c1 );
Connect(m.h3, m.c1 );

m.h4=CreateAtom("Wasserstoff");
m.h5=CreateAtom("Wasserstoff");
Connect(m.h4, m.c2 );
Connect(m.h5, m.c2 );

Connect(m.c2, m.oh.o);

Connect(m.c1, m.c2 );

RegisterMolecule( name, m );
	
