
#ifndef MoleculeController_hpp
#define MoleculeController_hpp

#include "service/MoleculeService.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/network/Url.hpp"
#include "oatpp/core/utils/ConversionUtils.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen

/**
 * Molecule REST controller.
 */
class MoleculeController : public oatpp::web::server::api::ApiController
{
public:
  MoleculeController(const std::shared_ptr<ObjectMapper> &objectMapper)
      : oatpp::web::server::api::ApiController(objectMapper)
  {
  }

private:
  MoleculeService m_moleculeService; // Create user service.
public:
  static std::shared_ptr<MoleculeController> createShared(
      OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper) // Inject objectMapper component here as default parameter
  )
  {
    return std::make_shared<MoleculeController>(objectMapper);
  }

  ENDPOINT_INFO(getMoleculeById)
  {
    info->summary = "Get one molecule by molecule id";

    info->addResponse<Object<MoleculeDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

    info->pathParams["moleculeId"].description = "Molecule Identifier";
  }
  ENDPOINT("GET", "molecules/{moleculeId}", getMoleculeById,
           PATH(Int64, moleculeId))
  {
    return createDtoResponse(Status::CODE_200, m_moleculeService.getMoleculeById(moleculeId));
  }

  ENDPOINT_INFO(getExactMolecule)
  {
    info->summary = "Get one molecule by SMILES with additional information";

    info->addResponse<Object<MoleculeDetailedDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

    info->pathParams["structure"].description = "Molecule SMILES";
  }
  ENDPOINT("GET", "molecules/exact_search/{structure}", getExactMolecule,
           PATH(String, structure))
  {
    return createDtoResponse(Status::CODE_200, m_moleculeService.getExactMolecule(structure));
  }

  ENDPOINT_INFO(getSubstructureMatches)
  {
    info->summary = "Get substructure search matches";

    info->addResponse<Object<MoleculesListDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

    info->pathParams["structure"].description = "Molecule SMILES";
    info->queryParams.add<String>("limit").description = "Number of molecules returned";
    info->queryParams["limit"].required = false; // make parameter optional
  }
  ENDPOINT("GET", "molecules/substruct_search/{structure}/*", getSubstructureMatches,
            REQUEST(std::shared_ptr<IncomingRequest>, request), // Map request object to endpoint method
           PATH(String, structure))
  {
    auto limit = request->getQueryParameter("limit", "100");
    bool success;
    Int64 limitInt = oatpp::utils::conversion::strToInt64(limit, success);
    return createDtoResponse(Status::CODE_200, m_moleculeService.getSubstructureMatches(structure, limitInt));
  }

  ENDPOINT_INFO(getSimilarityMatches)
  {
    info->summary = "Get similarity search matches";

    info->addResponse<Object<MoleculesSimListDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

    info->pathParams["structure"].description = "Molecule SMILES";
    info->queryParams.add<String>("limit").description = "Number of molecules returned";
    info->queryParams["limit"].required = false; // make parameter optional
    info->queryParams.add<String>("threshold").description = "Similarity threshold to use. Defaults to 0.5";
    info->queryParams["threshold"].required = false; // make parameter optional
  }
  ENDPOINT("GET", "molecules/substruct_search/{structure}/*", getSubstructureMatches,
            REQUEST(std::shared_ptr<IncomingRequest>, request), // Map request object to endpoint method
           PATH(String, structure))
  {
    auto limit = request->getQueryParameter("limit", "100");
    bool successLimit;
    Int64 limitInt = oatpp::utils::conversion::strToInt64(limit, successLimit);

    auto threshold = request->getQueryParameter("threshold", "0.5");
    bool successThreshold;
    Float64 thresholdFloat = oatpp::utils::conversion::strToFloat64(threshold, successThreshold);
    return createDtoResponse(Status::CODE_200, m_moleculeService.getSimilarityMatches(structure, limitInt, thresholdFloat));
  }
};

#include OATPP_CODEGEN_BEGIN(ApiController) //<- End Codegen

#endif /* MoleculeController_hpp */
