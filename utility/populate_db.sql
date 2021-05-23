drop database if exists molecules;
create table raw_data (id SERIAL, smiles text, mcule_id text);
create extension rdkit;
copy raw_data(smiles, mcule_id)
from '/mcule.smi' DELIMITER E '\t' CSV;
select * into mols
from (
        select id,
            mol_from_smiles(smiles::cstring) m
        from raw_data
    ) tmp
where m is not null;
create index molidx on mols using gist(m);
select id,
    m::text,
    torsionbv_fp(m) as torsionbv,
    morganbv_fp(m) as mfp2,
    featmorganbv_fp(m) as ffp2 into fps
from mols;
create index fps_ttbv_idx on fps using gist(torsionbv);
create index fps_mfp2_idx on fps using gist(mfp2);
create index fps_ffp2_idx on fps using gist(ffp2);
alter table fps
add primary key (id);