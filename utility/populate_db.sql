drop database if exists molecules;
create table raw_data (id SERIAL, smiles text, mcule_id text);
create extension rdkit;
copy raw_data(smiles, mcule_id)
from '/mcule.smi' DELIMITER E'\t' CSV;
select * into mols
from (
        select id,
            mol_from_smiles(smiles::cstring) m
        from raw_data
    ) tmp
where m is not null;
create index molidx on mols using gist(m);