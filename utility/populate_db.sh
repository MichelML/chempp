# steps are taken from https://rdkit.org/docs/Cartridge.html
PGPASSWORD=db-pass psql --host localhost -p 5432 -U postgres -c 'drop database if exists emolecules'
PGPASSWORD=db-pass createdb --host localhost -p 5432 -U postgres emolecules
PGPASSWORD=db-pass psql --host localhost -p 5432 -U postgres -c 'create extension rdkit' emolecules
PGPASSWORD=db-pass psql --host localhost -p 5432 -U postgres -c 'create table raw_data (id SERIAL, smiles text, emol_id integer, parent_id integer)' emolecules
curl -o emolecules-2021-05-01.smi.gz https://downloads.emolecules.com/free/2021-05-01/version.smi.gz
zcat emolecules-2021-05-01.smi.gz | sed '1d; s/\\/\\\\/g' | PGPASSWORD=db-pass psql --host localhost -p 5432 -U postgres -c "copy raw_data (smiles,emol_id,parent_id) from stdin with delimiter ' '" emolecules
PGPASSWORD=db-pass psql --host localhost -p 5432 -U postgres --dbname=emolecules -c 'select * into mols from (select id,mol_from_smiles(smiles::cstring) m from raw_data) tmp where m is not null' 
PGPASSWORD=db-pass psql --host localhost -p 5432 -U postgres --dbname=emolecules -c 'create index molidx on mols using gist(m)' 
