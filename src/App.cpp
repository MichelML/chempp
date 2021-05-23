
#include "AppComponent.hpp"
#include "DatabaseComponent.hpp"
#include "ServiceComponent.hpp"
#include "SwaggerComponent.hpp"
#include "controller/MoleculeController.hpp"

#include "oatpp-swagger/Controller.hpp"

#include "oatpp/network/Server.hpp"

#include <iostream>

void run(const oatpp::base::CommandLineArguments &args) {

  AppComponent appComponent(args);
  ServiceComponent serviceComponent;
  SwaggerComponent swaggerComponent;
  DatabaseComponent databaseComponent;

  /* create ApiControllers and add endpoints to router */

  auto router = serviceComponent.httpRouter.getObject();
  auto docEndpoints = oatpp::swagger::Controller::Endpoints::createShared();

  auto moleculeController = MoleculeController::createShared();
  moleculeController->addEndpointsToRouter(router);

  docEndpoints->pushBackAll(
      moleculeController->getEndpoints()); // Add moleculeController to swagger

  auto swaggerController =
      oatpp::swagger::Controller::createShared(docEndpoints);
  swaggerController->addEndpointsToRouter(router);

  /* create server */

  oatpp::network::Server server(
      serviceComponent.serverConnectionProvider.getObject(),
      serviceComponent.serverConnectionHandler.getObject());

  auto port = serviceComponent.serverConnectionProvider.getObject()
                  ->getProperty("port")
                  .toString()
                  ->c_str();

  OATPP_LOGD("Server", "Running on port %s...", port);
  OATPP_LOGD("Server", "Full URL at http://localhost:%s", port);

  server.run();
}

int main(int argc, const char *argv[]) {

  oatpp::base::Environment::init();

  run(oatpp::base::CommandLineArguments(argc, argv));

  oatpp::base::Environment::destroy();

  return 0;
}
