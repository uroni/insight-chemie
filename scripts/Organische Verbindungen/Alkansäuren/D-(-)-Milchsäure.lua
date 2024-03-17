local name="D-(-)-Milchsäure";
local m={};

local scale=1500;

m.c=CreateAtom("Kohlenstoff", name);
m.cooh=
{
	c=CreateAtom("Kohlenstoff", name,0,scale),
	o=CreateAtom("Sauerstoff",name,0,scale), 
	oh={ o=CreateAtom("Sauerstoff", name,0,scale), h=CreateAtom("Wasserstoff",name,0,scale) }
}
m.ch3=
{
	c=CreateAtom("Kohlenstoff", name,0,-scale,-scale),
	h1=CreateAtom("Wasserstoff", name,0,-scale,-scale),
	h2=CreateAtom("Wasserstoff", name,0,-scale,-scale),
	h3=CreateAtom("Wasserstoff", name,0,-scale,-scale)
}
m.h=CreateAtom("Wasserstoff",name,0,-scale,scale);
m.oh=
{
	o=CreateAtom("Sauerstoff", name, -scale,-scale);
	h=CreateAtom("Wasserstoff", name, -scale,-scale);
}

Connect(m.cooh.c, m.cooh.o);
Connect(m.cooh.c, m.cooh.o);
Connect(m.cooh.c, m.cooh.oh.o);
Connect(m.cooh.oh.o, m.cooh.oh.h);

Connect(m.oh.o, m.oh.h);

Connect(m.ch3.c, m.ch3.h1);
Connect(m.ch3.c, m.ch3.h2);
Connect(m.ch3.c, m.ch3.h3);

Connect(m.c, m.cooh.c);
Connect(m.c, m.ch3.c);
Connect(m.c, m.h);

Connect(m.c, m.oh.o);


RegisterMolecule(name, m);
