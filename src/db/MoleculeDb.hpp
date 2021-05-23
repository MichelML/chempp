
#ifndef EXAMPLE_POSTGRESQL_MOLECULEDB_HPP
#define EXAMPLE_POSTGRESQL_MOLECULEDB_HPP

#include "dto/MoleculeDto.hpp"
#include "dto/MoleculesListDto.hpp"
#include "oatpp-postgresql/orm.hpp"

#include OATPP_CODEGEN_BEGIN(DbClient) //<- Begin Codegen

/**
 * MoleculeDb client definitions.
 */
class MoleculeDb : public oatpp::orm::DbClient {
public:

  MoleculeDb(const std::shared_ptr<oatpp::orm::Executor>& executor)
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
        PREPARE(true), //<-- user prepared statement!
        PARAM(oatpp::Int64, id))

  QUERY(getSubstructureMatches,
        "SELECT id, m, cast(m as text) as smiles from mols where m@>:structure limit :limit;",
        PREPARE(true), //<-- user prepared statement!
        PARAM(oatpp::String, structure),
        PARAM(oatpp::Int64, limit))
};

#include OATPP_CODEGEN_END(DbClient) //<- End Codegen

#endif //EXAMPLE_POSTGRESQL_MOLECULEDB_HPP
