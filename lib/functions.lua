molecules={};
molecules_id={};
molecules_currid=0;

function RegisterMolecule(name, data)
	if molecules[name]==nil then
		molecules[name]={};
	end

	for key,value in data do
		if type(value)=="number" then
			SetMoleculeID(value, molecules_currid);
			break;
		end
	end

	table.insert( molecules[name], data );

	molecules_id[molecules_currid]=data;

	molecules_currid=molecules_currid+1;
	
	return molecules_currid-1;		
end

function GetMolecule(name, idx)
	if idx==nil then
		idx=0;
	end

	idx=idx+1;
	
	if molecules[name]==nil then
		return nil;
	end

	for i=1,table.getn(molecules[name]) do
		if i==idx then
			return molecules[name][i];
		end
	end
end

function GetMoleculeByID(id)
	return molecules_id[tonumber(id)];
end

--function RemoveMolecule(name, idx)
		

	
	
