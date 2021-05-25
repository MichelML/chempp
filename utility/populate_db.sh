rm mcule.smi mcule.smi.gz
curl -o mcule.smi.gz https://mcule.s3.amazonaws.com/database/mcule_purchasable_building_blocks_210414.smi.gz
gunzip mcule.smi.gz

PGPASSWORD=db-pass psql --host db --port 5432 -U postgres -c 'drop database if exists molecules'
PGPASSWORD=db-pass createdb --host db --port 5432 -U postgres molecules
PGPASSWORD=db-pass psql --host db --port 5432 -U postgres --dbname=molecules -f /utility/populate_db.sql

rm mcule.smi mcule.smi.gz
