
#ifndef EXAMPLE_POSTGRESQL_MOLECULEDB_HPP
#define EXAMPLE_POSTGRESQL_MOLECULEDB_HPP

#include "dto/MoleculeDto.hpp"
#include "dto/MoleculesListDto.hpp"
#include "oatpp-postgresql/orm.hpp"

#include OATPP_CODEGEN_BEGIN(DbClient) //<- Begin Codegen

/**
 * MoleculeDb client definitions.
 */
class MoleculeDb : public oatpp::orm::DbClient
{
public:
      MoleculeDb(const std::shared_ptr<oatpp::orm::Executor> &executor)
          : oatpp::orm::DbClient(executor)
      {

            oatpp::orm::SchemaMigration migration(executor);
            // We use a pre-filled, read-only database, therefore no migration files needed
            // migration.addFile(1 /* start from version 1 */, DATABASE_MIGRATIONS "/001_init.sql");
            // TODO - Add more migrations here.
            // migration.migrate(); // <-- run migrations. This guy will throw on error.

            auto version = executor->getSchemaVersion();
            OATPP_LOGD("MoleculeDb", "Migration - OK. Version=%d.", version);
      }

      QUERY(getMoleculeById,
            "SELECT id, cast(m as text) as smiles from mols where id=:id;",
            PREPARE(true),
            PARAM(oatpp::Int64, id))

      QUERY(getExactMolecule,
            "SELECT id, cast(m as text) as smiles, cast(mol_inchikey(m) as text) as inchikey, cast(mol_inchi(m) as text) as inchi, cast(mol_amw(m) as float) as amw, cast(mol_logp(m) as float) as logp from mols where m @= cast(:structure as mol) limit 1;",
            PREPARE(true),
            PARAM(oatpp::String, structure))

      QUERY(getSubstructureMatches,
            "SELECT id, cast(m as text) as smiles from mols where m@>cast(:structure as qmol) limit :limit;",
            PREPARE(true),
            PARAM(oatpp::String, structure),
            PARAM(oatpp::Int64, limit))

      QUERY(getSimilarityMatches,
            "SELECT id, cast(m as text) as smiles, tanimoto_sml(morganbv_fp(cast(:structure as mol)),mfp2) as similarity from fps where mfp2%morganbv_fp(cast(:structure as mol)) limit :limit;",
            PREPARE(true),
            PARAM(oatpp::String, structure),
            PARAM(oatpp::Int64, limit))
};

#include OATPP_CODEGEN_END(DbClient) //<- End Codegen

#endif //EXAMPLE_POSTGRESQL_MOLECULEDB_HPP
