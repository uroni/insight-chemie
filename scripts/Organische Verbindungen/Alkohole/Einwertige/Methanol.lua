local name="Methanol";
local m={};

m.a0=CreateAtom("Kohlenstoff", name);
m.a1=CreateAtom("Wasserstoff", name);
m.a2=CreateAtom("Wasserstoff", name);
m.a3=CreateAtom("Wasserstoff", name);
m.a4=CreateAtom("Sauerstoff", name);
m.a5=CreateAtom("Wasserstoff", name);
Connect(m.a0, m.a2);
Connect(m.a0, m.a1);
Connect(m.a0, m.a3);
Connect(m.a4, m.a5);
Connect(m.a0, m.a4);

local id=RegisterMolecule(name, m);

function Essigsaeuregaerung(id)
	
	local m=GetMoleculeByID(id);

	m.c={};
	m.c.c=CreateAtom("Kohlenstoff");
	m.c.o=CreateAtom("Sauerstoff");

	Connect(m.c.c,  m.c.o);
	Connect(m.c.c,  m.c.o);
	Connect(m.c.c,  m.c.o);

	Pause();

	Disconnect(m.a0, m.a4);
	Disconnect(m.c.c,  m.c.o);
	Connect(m.c.c, m.a0);
	Connect(m.c.c, m.a4);

	SetMoleculeName(m.c.c, "Essigsäure" );
end

AddAction(name, "Herstellung von Essigsäure", "Essigsaeuregaerung", id);

	
