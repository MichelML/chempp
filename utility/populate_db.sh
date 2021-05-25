rm mcule.smi mcule.smi.gz
curl -o mcule.smi.gz https://mcule.s3.amazonaws.com/database/mcule_purchasable_building_blocks_210414.smi.gz
gunzip mcule.smi.gz

if [[ -z "${SMALLDB}" ]]; then
  echo "using full dataset"
else
  echo "using subset of 1000 compounds of full dataset"
  head --lines 1000 mcule.smi > mcule_temp.smi
  mv mcule_temp.smi mcule.smi
fi

if [[ -z "${NODBDROP}" ]]; then
    echo "dropping and recreating existing database"
    PGPASSWORD=db-pass psql --host db --port 5432 -U postgres -c 'drop database if exists molecules'
    PGPASSWORD=db-pass createdb --host db --port 5432 -U postgres molecules
else
  echo "keeping existing database alive"
fi

PGPASSWORD=db-pass psql --host db --port 5432 -U postgres --dbname=molecules -f /utility/populate_db.sql

rm mcule.smi mcule.smi.gz
