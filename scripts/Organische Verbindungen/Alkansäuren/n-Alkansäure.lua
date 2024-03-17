function CreateAlkanacid(n, name)
	local m={};

	local w_scale=2000;
	
	if name==nil then
		name="C"..(n-1).."-H"..(2*n-1).."-COOH";
	end

	for i=1,n do
		local posx=0;
		
		if n>5 then
			posx=i;
		end
	
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
			m[i].o=CreateAtom("Sauerstoff", name);
			Connect(m[i].c, m[i].oh.o);
			Connect(m[i].c, m[i].o);
			Connect(m[i].c, m[i].o);
		else
			m[i].h1=CreateAtom("Wasserstoff",name);
			m[i].h2=CreateAtom("Wasserstoff",name);
			Connect(m[i].c, m[i].h1 );
			Connect(m[i].c, m[i].h2 );
		end
	end

	RegisterMolecule(name, m);
end


if(drun==nil) then
	local n=tonumber(InputBox("Wie lange soll die Alkansäure sein?", "5" ));

	CreateAlkanacid(n);
end