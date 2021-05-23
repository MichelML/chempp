
#ifndef EXAMPLE_POSTGRESQL_MOLECULESERVICE_HPP
#define EXAMPLE_POSTGRESQL_MOLECULESERVICE_HPP

#include "db/UserDb.hpp"
#include "dto/PageDto.hpp"
#include "dto/StatusDto.hpp"

#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/core/macro/component.hpp"

class MoleculeService {
private:
  typedef oatpp::web::protocol::http::Status Status;
private:
  OATPP_COMPONENT(std::shared_ptr<UserDb>, m_database); // Inject database component
public:

  oatpp::Object<UserDto> getMoleculeById(const oatpp::String& id);
};

#endif //EXAMPLE_POSTGRESQL_MOLECULESERVICE_HPP
