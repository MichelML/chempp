
#include "MoleculeService.hpp"

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

oatpp::Object<ListDto<oatpp::Object<MoleculeDto>>>
MoleculeService::getSubstructureMatches(const oatpp::String &structure,
                                        const oatpp::Int64 &limit) {
  oatpp::Int64 countToFetch = limit;

  if (limit > 200) {
    countToFetch = 200;
  }

  auto dbResult = m_database->getSubstructureMatches(structure, limit);
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500,
                    dbResult->getErrorMessage());

  auto items = dbResult->fetch<oatpp::Vector<oatpp::Object<MoleculeDto>>>();
  auto resultsList = ListDto<oatpp::Object<MoleculeDto>>::createShared();
  resultsList->limit = countToFetch;
  resultsList->input = structure;
  resultsList->items = items;

  return resultsList;
}
