set(CMAKE_LEGACY_CYGWIN_WIN32 0)

cmake_minimum_required (VERSION 2.6)
set (CMAKE_CXX_STANDARD 14)
add_compile_options(-fpermissive)
add_compile_options(-O3)
#link_libraries(cunit)
project (algorithms_project)

add_executable(curve_projection_hypercube
        src/mainCurvesProjectionCube.cpp
        src/Curve.cpp
        src/Curve.h
        src/curve_hasher.cpp
        src/Dataset.cpp
        src/Dataset.h
        src/distance.h
        src/distance.cpp
        src/hasher.h
        src/HashTableStruct.h
        src/HashTableStruct.cpp
        src/Object.h
        src/Point.cpp
        src/Point.h
        src/point_hasher.cpp
        src/utils.cpp
        src/utils.h
        src/ui.cpp
        src/ui.h
        src/LSH.h
        src/parse_files.cpp src/parse_files.h
        src/Cube.h src/search.cpp src/search.h
        src/Projection.cpp src/Projection.h src/RelevantTraversals.cpp src/RelevantTraversals.h src/GenericAlgorithm.h src/Cube.cpp)

add_executable(curve_projection_lsh
        src/mainCurvesProjectionLSH.cpp
        src/Curve.cpp
        src/Curve.h
        src/curve_hasher.cpp
        src/Dataset.cpp
        src/Dataset.h
        src/distance.h
        src/distance.cpp
        src/hasher.h
        src/HashTableStruct.h
        src/HashTableStruct.cpp
        src/Object.h
        src/Point.cpp
        src/Point.h
        src/point_hasher.cpp
        src/utils.cpp
        src/utils.h
        src/ui.cpp
        src/ui.h
        src/LSH.h
        src/parse_files.cpp src/parse_files.h
        src/Cube.h src/search.cpp src/search.h
        src/Projection.cpp src/Projection.h src/RelevantTraversals.cpp src/RelevantTraversals.h src/GenericAlgorithm.h src/Cube.cpp)

add_executable(cube
        src/mainPointsCube.cpp
        src/Curve.cpp
        src/Curve.h
        src/curve_hasher.cpp
        src/Dataset.cpp
        src/Dataset.h
        src/distance.h
        src/distance.cpp
        src/hasher.h
        src/HashTableStruct.h
        src/HashTableStruct.cpp
        src/Object.h
        src/Point.cpp
        src/Point.h
        src/point_hasher.cpp
        src/utils.cpp
        src/utils.h
        src/ui.cpp
        src/ui.h
        src/LSH.h
        src/parse_files.cpp src/parse_files.h
        src/Cube.h src/search.cpp src/search.h
        src/GenericAlgorithm.h src/Cube.cpp
        src/Projection.cpp src/Projection.h src/RelevantTraversals.cpp src/RelevantTraversals.h)

add_executable(lsh
        src/mainPointsLSH.cpp
        src/Curve.cpp
        src/Curve.h
        src/curve_hasher.cpp
        src/Dataset.cpp
        src/Dataset.h
        src/distance.h
        src/distance.cpp
        src/hasher.h
        src/HashTableStruct.h
        src/HashTableStruct.cpp
        src/Object.h
        src/Point.cpp
        src/Point.h
        src/point_hasher.cpp
        src/utils.cpp
        src/utils.h 
        src/ui.cpp 
        src/ui.h 
        src/LSH.h
        src/parse_files.cpp src/parse_files.h
        src/Cube.h src/search.cpp src/search.h src/GenericAlgorithm.h src/Cube.cpp
        src/Projection.cpp src/Projection.h src/RelevantTraversals.cpp src/RelevantTraversals.h)

add_executable(curve_grid_lsh
        src/mainCurvesGridLSH.cpp
        src/Curve.cpp
        src/Curve.h
        src/curve_hasher.cpp
        src/Dataset.cpp
        src/Dataset.h
        src/distance.h
        src/distance.cpp
        src/hasher.h
        src/HashTableStruct.h
        src/HashTableStruct.cpp
        src/Object.h
        src/Point.cpp
        src/Point.h
        src/point_hasher.cpp
        src/utils.cpp
        src/utils.h 
        src/ui.cpp 
        src/ui.h 
        src/LSH.h
        src/parse_files.cpp src/parse_files.h
        src/Projection.cpp src/Projection.h 
        src/Cube.h src/search.cpp src/search.h src/RelevantTraversals.cpp src/RelevantTraversals.h src/GenericAlgorithm.h src/Cube.cpp)

add_executable(curve_grid_hypercube
        src/mainCurvesGridCube.cpp
        src/Curve.cpp
        src/Curve.h
        src/curve_hasher.cpp
        src/Dataset.cpp
        src/Dataset.h
        src/distance.h
        src/distance.cpp
        src/hasher.h
        src/HashTableStruct.h
        src/HashTableStruct.cpp
        src/Object.h
        src/Point.cpp
        src/Point.h
        src/point_hasher.cpp
        src/utils.cpp
        src/utils.h 
        src/ui.cpp 
        src/ui.h 
        src/LSH.h
        src/parse_files.cpp src/parse_files.h
        src/Projection.cpp src/Projection.h 
        src/Cube.h src/search.cpp src/search.h src/RelevantTraversals.cpp src/RelevantTraversals.h src/GenericAlgorithm.h src/Cube.cpp)

add_executable(test_curve_grid_lsh
        src/test_curve_grid_lsh.cpp
        src/curve_grid_lsh.h
        src/Curve.cpp
        src/Curve.h
        src/curve_hasher.cpp
        src/Dataset.cpp
        src/Dataset.h
        src/distance.h
        src/distance.cpp
        src/hasher.h
        src/HashTableStruct.h
        src/HashTableStruct.cpp
        src/Object.h
        src/Point.cpp
        src/Point.h
        src/point_hasher.cpp
        src/utils.cpp
        src/utils.h 
        src/ui.cpp 
        src/ui.h 
        src/LSH.h
        src/parse_files.cpp src/parse_files.h
        src/Projection.cpp src/Projection.h 
        src/Cube.h src/search.cpp src/search.h src/RelevantTraversals.cpp src/RelevantTraversals.h src/GenericAlgorithm.h src/Cube.cpp)

add_executable(test_point_hasher
        src/test_point_hasher.cpp
        src/Curve.cpp
        src/Curve.h
        src/curve_hasher.cpp
        src/Dataset.cpp
        src/Dataset.h
        src/distance.h
        src/distance.cpp
        src/hasher.h
        src/HashTableStruct.h
        src/HashTableStruct.cpp
        src/Object.h
        src/Point.cpp
        src/Point.h
        src/point_hasher.cpp
        src/utils.cpp
        src/utils.h
        src/ui.cpp
        src/ui.h
        src/LSH.h
        src/parse_files.cpp src/parse_files.h
        src/Cube.h
        src/Projection.cpp src/Projection.h 
        src/RelevantTraversals.cpp src/RelevantTraversals.h 
        src/search.cpp src/search.h src/GenericAlgorithm.h src/Cube.cpp)

add_executable(test_curve_hasher
        src/test_curve_hasher.cpp
        src/Curve.cpp
        src/Curve.h
        src/Dataset.cpp
        src/Dataset.h
        src/distance.h
        src/distance.cpp
        src/hasher.h
        src/HashTableStruct.h
        src/HashTableStruct.cpp
        src/Object.h
        src/Point.cpp
        src/Point.h
        src/curve_hasher.cpp
        src/point_hasher.cpp
        src/utils.cpp
        src/utils.h
        src/ui.cpp
        src/ui.h
        src/LSH.h
        src/parse_files.cpp src/parse_files.h
        src/Projection.cpp src/Projection.h 
        src/Cube.h src/search.cpp src/search.h src/RelevantTraversals.cpp src/RelevantTraversals.h src/GenericAlgorithm.h src/Cube.cpp)

add_executable(test_lsh_points
        src/test_lsh_points.cpp
        src/Curve.cpp
        src/Curve.h
        src/Dataset.cpp
        src/Dataset.h
        src/distance.h
        src/distance.cpp
        src/hasher.h
        src/HashTableStruct.h
        src/HashTableStruct.cpp
        src/Object.h
        src/Point.cpp
        src/Point.h
        src/curve_hasher.cpp
        src/point_hasher.cpp
        src/utils.cpp
        src/utils.h
        src/ui.cpp
        src/ui.h
        src/LSH.h
        src/parse_files.cpp src/parse_files.h
        src/Projection.cpp src/Projection.h 
        src/RelevantTraversals.cpp src/RelevantTraversals.h 
        src/Cube.h src/search.cpp src/search.h src/GenericAlgorithm.h src/Cube.cpp)