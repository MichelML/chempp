
#include "MoleculeService.hpp"

oatpp::Object<MoleculeDto>
MoleculeService::getMoleculeById(const oatpp::String &id) {

  auto dbResult = m_database->getMoleculeById(id);
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500,
                    dbResult->getErrorMessage());
  OATPP_ASSERT_HTTP(dbResult->hasMoreToFetch(), Status::CODE_404,
                    "Molecule not found");

  auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<MoleculeDto>>>();
  OATPP_ASSERT_HTTP(result->size() == 1, Status::CODE_500, "Unknown error");

  return result[0];
}
