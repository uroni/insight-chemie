function CreateOxygen()
	local name="Sauerstoff";
	
	local m={};
	m.o1=CreateAtom("Sauerstoff", name);
	m.o2=CreateAtom("Sauerstoff", name);
	
	Connect(m.o1,m.o2);
	Connect(m.o1,m.o2);

	return m;
end

function CreateWater()
	local name="Wasser";
	
	local m={};
	m.o=CreateAtom("Sauerstoff",name);
	m.h1=CreateAtom("Wasserstoff",name);
	m.h2=CreateAtom("Wasserstoff",name);

	Connect(m.o, m.h1);
	Connect(m.o, m.h2);
	
	return m;
end

function CreateHydroxid(name)
	local m={};
	
	m.o=CreateAtom("Sauerstoff",name);
	m.h=CreateAtom("Wasserstoff",name);

	Connect(m.o, m.h);
	
	return m;
end


function CreateCarbondioxide()
	local name="Kohlenstoffdioxid";
	local m={};
	

	m.c=CreateAtom("Kohlenstoff",name);
	m.o1=CreateAtom("Sauerstoff", name);
	m.o2=CreateAtom("Sauerstoff", name);

	Connect(m.c, m.o1);
	Connect(m.c, m.o1);
	Connect(m.c, m.o2);
	Connect(m.c, m.o2);	

	return m;
end

function CreateNitrate()
	local name="Stickstoff";
	local m={};

	m.n1=CreateAtom("Stickstoff");
	m.n2=CreateAtom("Stickstoff");

	Connect(m.n1, m.n2);

	return m;
end