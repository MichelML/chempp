
#ifndef EXAMPLE_POSTGRESQL_MOLECULELISTDTO_HPP
#define EXAMPLE_POSTGRESQL_MOLECULELISTDTO_HPP

#include "MoleculeDto.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

template<class T>
class ListDto : public oatpp::DTO {

  DTO_INIT(ListDto, DTO)

  DTO_FIELD(oatpp::String, input);
  DTO_FIELD(oatpp::Int64, limit);
  DTO_FIELD(Vector<T>, items);
};

template<class T>
class SimListDto : public oatpp::DTO {

  DTO_INIT(SimListDto, DTO)

  DTO_FIELD(oatpp::String, input);
  DTO_FIELD(oatpp::Int64, limit);
  DTO_FIELD(oatpp::Float64, threshold);
  DTO_FIELD(Vector<T>, items);
};

class MoleculesListDto : public ListDto<oatpp::Object<MoleculeDto>> {
  DTO_INIT(MoleculesListDto, ListDto<oatpp::Object<MoleculeDto>>)
};

class MoleculesSimListDto : public SimListDto<oatpp::Object<MoleculeDto>> {
  DTO_INIT(MoleculesSimListDto, SimListDto<oatpp::Object<MoleculeDto>>)
};

#include OATPP_CODEGEN_END(DTO)

#endif //EXAMPLE_POSTGRESQL_MOLECULELISTDTO_HPP
