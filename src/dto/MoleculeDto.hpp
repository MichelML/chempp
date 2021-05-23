#ifndef MoleculeDto_hpp
#define MoleculeDto_hpp

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class MoleculeDto : public oatpp::DTO {
  
  DTO_INIT(MoleculeDto, DTO)

  DTO_FIELD(Int64, id, "id");
  DTO_FIELD(String, smiles, "smiles");
  DTO_FIELD(Float64, smiliarity, "similarity");
};

class MoleculeDetailedDto : public oatpp::DTO {
  
  DTO_INIT(MoleculeDetailedDto, DTO)

  DTO_FIELD(Int64, id, "id");
  DTO_FIELD(String, smiles, "smiles");
  DTO_FIELD(String, inchikey, "inchikey");
  DTO_FIELD(String, inchi, "inchi");
  DTO_FIELD(Float64, amw, "amw");
  DTO_FIELD(Float64, logp, "logp");
};

#include OATPP_CODEGEN_END(DTO)

#endif /* MoleculeDto_hpp */
