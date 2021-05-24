
#include "MoleculeService.hpp"
#include "oatpp/core/utils/ConversionUtils.hpp"
#include "utilities/uri.hpp"
#include <regex>
#include <string>

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
  auto dbResult =
      m_database->getSubstructureMatches(finalStructure, countToFetch);
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500,
                    dbResult->getErrorMessage());

  auto items = dbResult->fetch<oatpp::Vector<oatpp::Object<MoleculeDto>>>();
  auto resultsList = ListDto<oatpp::Object<MoleculeDto>>::createShared();
  resultsList->limit = countToFetch;
  resultsList->input = finalStructure;
  resultsList->items = items;

  return resultsList;
}

oatpp::Object<SimListDto<oatpp::Object<MoleculeDto>>>
MoleculeService::getSimilarityMatches(const oatpp::String &structure,
                                      const oatpp::Int64 &limit,
                                      const oatpp::Float64 &threshold) {
  oatpp::Int64 countToFetch = limit;
  oatpp::Float64 simThreshold = threshold;

  if (limit > 200) {
    countToFetch = 200;
  }

  if (threshold < 0.5) {
    simThreshold = 0.5;
  } else if (threshold > 0.99) {
    simThreshold = 0.99;
  }

  std::string parsedStructure = decodeURIComponent(structure->std_str());
  oatpp::String finalStructure = parsedStructure.c_str();

  oatpp::String stringThreshold =
      oatpp::utils::conversion::float64ToStr(simThreshold, "%.2g");
  std::string tanimotoThresholdQuery = "set rdkit.tanimoto_threshold=XX;";
  tanimotoThresholdQuery = std::regex_replace(
      tanimotoThresholdQuery, std::regex("XX"), stringThreshold->std_str());
  oatpp::String tanimotoThresholdQueryFinal = tanimotoThresholdQuery.c_str();
  m_database->executeQuery(tanimotoThresholdQueryFinal, {});
  auto dbResult =
      m_database->getSimilarityMatches(finalStructure, countToFetch);
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500,
                    dbResult->getErrorMessage());

  auto items = dbResult->fetch<oatpp::Vector<oatpp::Object<MoleculeDto>>>();
  auto resultsList = SimListDto<oatpp::Object<MoleculeDto>>::createShared();
  resultsList->limit = countToFetch;
  resultsList->input = finalStructure;
  resultsList->threshold = simThreshold;
  resultsList->items = items;

  return resultsList;
}
