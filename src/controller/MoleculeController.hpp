
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
class MoleculeController : public oatpp::web::server::api::ApiController {
public:
  MoleculeController(const std::shared_ptr<ObjectMapper>& objectMapper)
    : oatpp::web::server::api::ApiController(objectMapper)
  {}
private:
  MoleculeService m_moleculeService; // Create user service.
public:

  static std::shared_ptr<MoleculeController> createShared(
    OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper) // Inject objectMapper component here as default parameter
  ){
    return std::make_shared<MoleculeController>(objectMapper);
  }
  
  ENDPOINT_INFO(getMoleculeById) {
    info->summary = "Get one molecule by molecule id";

    info->addResponse<Object<MoleculeDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

    info->pathParams["moleculeId"].description = "Molecule Identifier";
  }
  ENDPOINT("GET", "molecules/{moleculeId}", getMoleculeById,
           PATH(String, moleculeId))
  {
    return createDtoResponse(Status::CODE_200, m_moleculeService.getMoleculeById(userId));
  }
};

#include OATPP_CODEGEN_BEGIN(ApiController) //<- End Codegen

#endif /* MoleculeController_hpp */