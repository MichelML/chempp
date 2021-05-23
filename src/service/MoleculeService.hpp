
#ifndef EXAMPLE_POSTGRESQL_MOLECULESERVICE_HPP
#define EXAMPLE_POSTGRESQL_MOLECULESERVICE_HPP

#include "db/MoleculeDb.hpp"
#include "dto/StatusDto.hpp"

#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/core/macro/component.hpp"

class MoleculeService {
private:
  typedef oatpp::web::protocol::http::Status Status;
private:
  OATPP_COMPONENT(std::shared_ptr<MoleculeDb>, m_database); // Inject database component
public:

  oatpp::Object<MoleculeDto> getMoleculeById(const oatpp::String& id);
};

#endif //EXAMPLE_POSTGRESQL_MOLECULESERVICE_HPP
