local name="Glycerin";
local m={};

m.a0=CreateAtom("Kohlenstoff", name);
m.a1=CreateAtom("Kohlenstoff", name);
m.a2=CreateAtom("Kohlenstoff", name);
m.a3=CreateAtom("Sauerstoff", name);
m.a4=CreateAtom("Wasserstoff", name);
m.a5=CreateAtom("Sauerstoff", name);
m.a6=CreateAtom("Wasserstoff", name);
m.a7=CreateAtom("Sauerstoff", name);
m.a8=CreateAtom("Wasserstoff", name);
m.a9=CreateAtom("Wasserstoff", name);
m.a10=CreateAtom("Wasserstoff", name);
m.a11=CreateAtom("Wasserstoff", name);
m.a12=CreateAtom("Wasserstoff", name);
m.a13=CreateAtom("Wasserstoff", name);
Connect(m.a3, m.a4);
Connect(m.a5, m.a6);
Connect(m.a7, m.a8);
Connect(m.a0, m.a7);
Connect(m.a1, m.a5);
Connect(m.a2, m.a3);
Connect(m.a1, m.a2);
Connect(m.a1, m.a0);
Connect(m.a2, m.a9);
Connect(m.a2, m.a10);
Connect(m.a0, m.a11);
Connect(m.a0, m.a12);
Connect(m.a1, m.a13);

local id=RegisterMolecule(name, m);

function Salpetersaure(pos)
	local m={};
	local name="Salpetersäure";

	m.n=CreateAtom("Stickstoff",name,pos);
	m.o1=CreateAtom("Sauerstoff",name,pos);
	m.o2=CreateAtom("Sauerstoff",name,pos);
	m.o3=CreateAtom("Sauerstoff",name,pos);
	m.h=CreateAtom("Wasserstoff",name,pos);

	Connect(m.n, m.o1);
	Connect(m.n, m.o1);
	Connect(m.n, m.o2);
	Connect(m.n, m.o3);
	Connect(m.o3, m.h);

	return m;
end

function TransformToNitroglycerin(id)
	local m=GetMoleculeByID(id);

	local s1=Salpetersaure(1);

	local s2=Salpetersaure(-1);

	local s3=Salpetersaure(1);

	Sleep(500);
	Pause();

	Disconnect(m.a3, m.a4);
	Disconnect(m.a5, m.a6);
	Disconnect(m.a7, m.a8);

	Sleep(500);
	Pause();

	Disconnect(s1.n, s1.o3);
	Disconnect(s2.n, s2.o3);
	Disconnect(s3.n, s3.o3);

	Sleep(500);
	Pause();

	Connect(s1.o3, m.a4 );
	Connect(s2.o3, m.a6 );
	Connect(s3.o3, m.a8 );

	Sleep(500);
	Pause();

	Connect(s1.n, m.a3 );
	Connect(s2.n, m.a5 );
	Connect(s3.n, m.a7 );

	local name="Glycerintrinitrat";

	SetMoleculeName( s1.n, "Glycerintrinitrat");

	SetMoleculeName( s1.o3, "Wasser");
	SetMoleculeName( s2.o3, "Wasser");
	SetMoleculeName( s3.o3, "Wasser");

	local nitro={};
	
	nitro.s1=s1;
	nitro.s2=s3;
	nitro.s3=s3;	
	
	nitro.g=m;

	local id=RegisterMolecule(name, nitro);

	AddAction(name, "Explodieren", "NitrogylcerinZerfall", id );
end

function NitrogylcerinZerfall(id)
	
	local m=GetMoleculeByID(id);

	RemoveMolecule(m.s1.n);

	for i=1,12 do
		CreateCarbondioxide();
	end

	for i=1,10 do
		CreateWater();
	end
	

	for i=1,5 do
		CreateNitrate();
	end

	Connect( CreateAtom("Stickstoff"), CreateAtom("Sauerstoff") );
	Connect( CreateAtom("Stickstoff"), CreateAtom("Sauerstoff") );
end	
	

AddAction(name, "Umwandeln in Nitroglycerin", "TransformToNitroglycerin", id );

	
	
	
