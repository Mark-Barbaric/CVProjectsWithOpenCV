set(OUTPUT_TO_MASTER_TARGETS ""
        CACHE INTERNAL "List of targets to output to Master* dirs" FORCE
        )

macro(OUTPUT_TO_MASTER_DIR _target)
    if(ARGV1)
        set(_subdir "/${ARGV1}")
    else()
        set(_subdir "")
    endif()

    set_target_properties(
            ${_target} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/MasterDebug${_subdir}"
            RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/MasterRelease${_subdir}"
            RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_BINARY_DIR}/MasterMinSizeRel${_subdir}"
            RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/MasterRelWithDebInfo${_subdir}"
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Master${CMAKE_BUILD_TYPE}${_subdir}"
    )

    list(APPEND OUTPUT_TO_MASTER_TARGETS "${_target}")
    set(
            OUTPUT_TO_MASTER_TARGETS "${OUTPUT_TO_MASTER_TARGETS}"
            CACHE INTERNAL "List of targets to output to Master* dirs" FORCE
    )

endmacro()