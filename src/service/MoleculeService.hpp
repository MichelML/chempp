
#ifndef EXAMPLE_POSTGRESQL_MOLECULESERVICE_HPP
#define EXAMPLE_POSTGRESQL_MOLECULESERVICE_HPP

#include "db/MoleculeDb.hpp"
#include "dto/StatusDto.hpp"
#include "dto/MoleculeDto.hpp"
#include "dto/MoleculesListDto.hpp"

#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/core/macro/component.hpp"

class MoleculeService {
private:
  typedef oatpp::web::protocol::http::Status Status;
private:
  OATPP_COMPONENT(std::shared_ptr<MoleculeDb>, m_database); // Inject database component
public:

  oatpp::Object<MoleculeDto> getMoleculeById(const oatpp::Int64& id);
  oatpp::Object<MoleculeDetailedDto> getExactMolecule(const oatpp::String& structure);
  oatpp::Object<ListDto<oatpp::Object<MoleculeDto>>> getSubstructureMatches(const oatpp::String& structure, const oatpp::Int64& limit);
  oatpp::Object<SimListDto<oatpp::Object<MoleculeDto>>> getSimilarityMatches(const oatpp::String& structure, const oatpp::Int64& limit, const oatpp::Float64& threshold);
};

#endif //EXAMPLE_POSTGRESQL_MOLECULESERVICE_HPP
