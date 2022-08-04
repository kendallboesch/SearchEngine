cmake_minimum_required(VERSION 3.16)
project(22s_final_proj)

set(CMAKE_CXX_STANDARD 17)
FILE(COPY sample_data_sets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
add_executable(22s_final_proj main.cpp catch_setup.cpp AVLTree.h DocumentParser.cpp DocumentParser.h porter2_stemmer.cpp porter2_stemmer.h indexObject.cpp indexObject.h EngineDriver.cpp EngineDriver.h AVLNode.h QueryProcessor.cpp QueryProcessor.h DSHashTable.h RelevancyRanker.cpp RelevancyRanker.h)
