
#include "MoleculeService.hpp"
#include "utilities/uri.hpp"

oatpp::Object<MoleculeDto>
MoleculeService::getMoleculeById(const oatpp::Int64 &id) {

  auto dbResult = m_database->getMoleculeById(id);
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500,
                    dbResult->getErrorMessage());
  OATPP_ASSERT_HTTP(dbResult->hasMoreToFetch(), Status::CODE_404,
                    "Molecule not found");

  auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<MoleculeDto>>>();
  OATPP_ASSERT_HTTP(result->size() == 1, Status::CODE_500, "Unknown error");

  return result[0];
}

oatpp::Object<MoleculeDetailedDto>
MoleculeService::getExactMolecule(const oatpp::String &structure) {
  std::string parsedStructure = decodeURIComponent(structure->std_str());
  oatpp::String finalStructure = parsedStructure.c_str();
  auto dbResult = m_database->getExactMolecule(finalStructure);
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500,
                    dbResult->getErrorMessage());

  auto result =
      dbResult->fetch<oatpp::Vector<oatpp::Object<MoleculeDetailedDto>>>();
  OATPP_ASSERT_HTTP(result->size() == 1, Status::CODE_500, "Unknown error");

  return result[0];
}

oatpp::Object<ListDto<oatpp::Object<MoleculeDto>>>
MoleculeService::getSubstructureMatches(const oatpp::String &structure,
                                        const oatpp::Int64 &limit) {
  oatpp::Int64 countToFetch = limit;

  if (limit > 200) {
    countToFetch = 200;
  }

  std::string parsedStructure = decodeURIComponent(structure->std_str());
  oatpp::String finalStructure = parsedStructure.c_str();
  auto dbResult = m_database->getSubstructureMatches(finalStructure, limit);
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500,
                    dbResult->getErrorMessage());

  auto items = dbResult->fetch<oatpp::Vector<oatpp::Object<MoleculeDto>>>();
  auto resultsList = ListDto<oatpp::Object<MoleculeDto>>::createShared();
  resultsList->limit = countToFetch;
  resultsList->input = finalStructure;
  resultsList->items = items;

  return resultsList;
}
