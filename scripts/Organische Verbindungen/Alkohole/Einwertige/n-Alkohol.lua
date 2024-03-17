local n=tonumber(InputBox("Wie lange soll die Alkoholkette sein?", "5" ));

local m={};

local w_scale=2000;

local name="C"..n.." H"..(2*n+1).." OH";

for i=1,n do
	local posx=0;
	if( n>5 ) then posx=i; end

	table.insert(m, {c=CreateAtom("Kohlenstoff",name,posx*w_scale)} );
end

for i=1,n do
	if (i==1) then
		m[i].h3=CreateAtom("Wasserstoff",name);
		Connect(m[i].c, m[i].h3 );
	end
	if i~=n then
		Connect( m[i].c, m[i+1].c );
	end

	if i==n then
		m[i].oh=CreateHydroxid(name);
		Connect(m[i].c, m[i].oh.o);
	end

	m[i].h1=CreateAtom("Wasserstoff",name);
	m[i].h2=CreateAtom("Wasserstoff",name);
	Connect(m[i].c, m[i].h1 );
	Connect(m[i].c, m[i].h2 );
end

RegisterMolecule(name, m);