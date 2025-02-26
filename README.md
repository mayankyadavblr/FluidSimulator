# How to use:

To run my current version:
* Navigate to ./out/build/cpp_compiler/FluidSim.exe
* Download the .exe file and run in your terminal

To mess around with starting conditions:
* Make sure you have cmake and a cpp compiler installed
* Follow https://github.com/SFML/cmake-sfml-project/tree/master
* Use my cmake and src folder instead
* Play around with sfml_test.cpp file in ./src/

### Legend:
* Color White to Black corresponds to lightest to heaviest

------------

# Future work:

* Optimize boundary collision checks
* Look for more optimizations
* Refactor Rectangle struct 
* Clean up code
* Documentation
* Investigate energy creation during collisions



------------

# Benchmarks:

## Frame size: 1000px X 1000px

### Number of particles and FPS:

* 250/170

* 500/110

* 1000/50
------------
# Change log / current status:
Feb-18th
* Implemented coefficient of restitution
* Implemented mass aware collision
* Shading particles based on mass

Feb-19th
* Variable particle radii
* Tested buoyancy (success)
* Implemented linear interpolation for collisions

Feb-20th
* Fixed and tested linear interpolation
* Refactored code avoid redefinitions of dt
* Fixed fake 'tunneling' effect in graphics

Feb-21st
* Implemented Quadtree for density aware frame subdivision

Feb-22nd
* Debugging quad tree implementation

Feb-23rd
* Made boundary collision recursive
* Figured out deletion of quad_tree

Feb-24th
* Finally fixed quad tree

Feb-25th
* Added energy counters
* Checked for memory leaks
