function CreateGlucose()
	local name="Glukose";
	local m={};
	m.c1={c=CreateAtom("Kohlenstoff",name) };
	m.c2={c=CreateAtom("Kohlenstoff",name) };
	m.c3={c=CreateAtom("Kohlenstoff",name) };
	m.c4={c=CreateAtom("Kohlenstoff",name) };
	m.c5={c=CreateAtom("Kohlenstoff",name) };
	m.c6={c=CreateAtom("Kohlenstoff",name) };

	m.c1.h=CreateAtom("Wasserstoff",name);
	m.c1.o=CreateAtom("Sauerstoff",name);

	m.c2.h=CreateAtom("Wasserstoff",name);
	m.c2.o=CreateHydroxid(name);
	
	m.c3.h=CreateAtom("Wasserstoff",name);
	m.c3.o=CreateHydroxid(name);

	m.c4.h=CreateAtom("Wasserstoff",name);
	m.c4.o=CreateHydroxid(name);

	m.c5.h=CreateAtom("Wasserstoff",name);
	m.c5.o=CreateHydroxid(name);

	m.c6.h1=CreateAtom("Wasserstoff",name);
	m.c6.h2=CreateAtom("Wasserstoff",name);
	m.c6.o=CreateHydroxid();

	-- C1
	Connect(m.c1.c, m.c1.h);
	Connect(m.c1.c, m.c1.o);
	Connect(m.c1.c, m.c1.o);

	-- C2	
	Connect(m.c2.c, m.c1.c);
	Connect(m.c2.c, m.c2.h);
	Connect(m.c2.c, m.c2.o.o);

	-- C3	
	Connect(m.c3.c, m.c2.c);
	Connect(m.c3.c, m.c3.h);
	Connect(m.c3.c, m.c3.o.o);
	
	-- C4
	Connect(m.c4.c, m.c3.c);
	Connect(m.c4.c, m.c4.h);
	Connect(m.c4.c, m.c4.o.o);

	-- C5
	Connect(m.c5.c, m.c4.c);
	Connect(m.c5.c, m.c5.h);
	Connect(m.c5.c, m.c5.o.o);

	-- C6
	Connect(m.c6.c, m.c5.c);
	Connect(m.c6.c, m.c6.h1);
	Connect(m.c6.c, m.c6.h2);
	Connect(m.c6.c, m.c6.o.o);

	RegisterMolecule("Glucose", m);

	return m;	
end