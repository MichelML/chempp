- The README also indicates the file and class structure, along with the expected behavior or output of the program.
> The class and overall structure of the project follows the Oat++ conventions: https://oatpp.io/docs/start/high-level-overview/ .
> A good understanding of Data Transfer Objects, Object-relational mapping, and Controllers is required.

- The README indicates which rubric points are addressed. The README also indicates where in the code (i.e. files and line numbers) that the rubric points are addressed.

### Loops, Functions, I/O

> The project demonstrates an understanding of C++ functions and control structures.

See `src/service/MoleculeService.cpp` line 64 to 104 for this.

See also `src/utilities/uri.hpp` although it is a gist taken from elsewhere.

> The project reads data from a file and process the data, or the program writes data to a file.
See `src/AppComponent.hpp` line 28 to 44 retrieving the application profile from `resources/config.json`.

> The project accepts user input and processes the input.
See any REST API endpoints in `src/controller/MoleculeController.hpp`.

### Object oriented programming

> The project uses Object Oriented Programming techniques.
See whole project for this.

> Classes use appropriate access specifiers for class members.
See database component injection in `src/service/MoleculeService.hpp` line 17 and usage in `src/serbice/MoleculeService.cpp` for this.

> Class constructors utilize member initialization lists.
N/A (I don't get this one?).

> Classes abstract implementation details from their interfaces.
See `src/service/MoleculeService.cpp` (implementation) and `src/service/MoleculeService.hpp` (interface).

> Classes encapsulate behavior.
See `src/service/MoleculeService.cpp` which encapsulates behavior of each REST API endpoints.

> Classes follow an appropriate inheritance hierarchy.
See some inheritance patterns in `src/dto/MoleculesListDto.hpp`.

> Overloaded functions allow the same function to operate on different parameters.
No real examples in this project. But an example of this can be found in Oat++ utility functions for type conversions:
https://oatpp.io/api/latest/oatpp/core/utils/ConversionUtils/

> Derived class functions override virtual base class functions.
No examples in this project.

> Templates generalize functions in the project.
See the generic SimListDto and ListDto classes in `src/dto/MoleculesListDto.hpp` for this.

### Memory Management

> The project makes use of references in function declarations.

> The project uses destructors appropriately.

> The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate.

> The project follows the Rule of 5.

> The project uses move semantics to move data, instead of copying it, where possible.

> The project uses smart pointers instead of raw pointers.

### Concurrency

> The project uses multithreading.
Concurrency is not yet addressed in this project, but I plan on adding this to the project post graduation of the nanodegree.

> A promise and future is used in the project.
Concurrency is not yet addressed in this project, but I plan on adding this to the project post graduation of the nanodegree.

> A mutex or lock is used in the project.
Concurrency is not yet addressed in this project, but I plan on adding this to the project post graduation of the nanodegree.

> A condition variable is used in the project.
Concurrency is not yet addressed in this project, but I plan on adding this to the project post graduation of the nanodegree.
