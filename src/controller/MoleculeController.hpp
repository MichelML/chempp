
#ifndef MoleculeController_hpp
#define MoleculeController_hpp

#include "service/MoleculeService.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
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

  ENDPOINT_INFO(getSubstructureMatches)
  {
    info->summary = "Get substructure search matches";

    info->addResponse<Object<MoleculesListDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

    info->pathParams["smiles"].description = "Molecule SMILES";
  }
  ENDPOINT("GET", "molecules/substruct_search/{smiles}/*", getSubstructureMatches,
            REQUEST(std::shared_ptr<IncomingRequest>, request), // Map request object to endpoint method
           PATH(String, smiles))
  {
    // queryParams logic was taken from https://github.com/oatpp/oatpp/issues/20#issuecomment-433079273
    String tail = request->getPathTail(); // everything that goes after '*'
    OATPP_ASSERT_HTTP(tail, Status::CODE_400, "null query-params");
    auto queryParams = oatpp::network::Url::Parser::parseQueryParams(tail);
    Int64 limit = queryParams->get("limit"/* parameter name */, 100 /* default value */);

    return createDtoResponse(Status::CODE_200, m_moleculeService.getSubstructureMatches(smiles, limit));
  }
};

#include OATPP_CODEGEN_BEGIN(ApiController) //<- End Codegen

#endif /* MoleculeController_hpp */
