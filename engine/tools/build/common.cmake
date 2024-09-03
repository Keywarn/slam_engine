set(CMAKE_CONFIGURATION_TYPES "Debug;Profile;Release") 

set(ENV_ARCHITECTURE "x64" CACHE INTERNAL "")

# All projects write to the config appropriate output directory.
foreach(config ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${config} config_upper)
    string(TOLOWER ${config} config_lower)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${config_upper} ${ENV_ROOT_PATH}/generated/libs/${ENV_ARCHITECTURE}_${config_lower})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${config_upper} ${ENV_ROOT_PATH}/build/${ENV_ARCHITECTURE}_${config_lower})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${config_upper} ${ENV_ROOT_PATH}/build/${ENV_ARCHITECTURE}_${config_lower})
endforeach()

include(cpp-settings)
include(vs-settings)
include(utils)