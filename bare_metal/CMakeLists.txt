cmake_minimum_required(VERSION 3.20)

# Disable in-source build.
if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
    message(FATAL_ERROR "In-source build is not allowed! Please specify a build folder.\n\tex:cmake -B build")
endif()

## Specify configuration

## Import XMOS configurations
include("$ENV{XCORE_SDK_PATH}/tools/cmake_utils/xmos_toolchain.cmake")

## Define project
project(explorer_power_test)

## Enable languages for project
enable_language(CXX C ASM)

## Set XMOS application variables
set(APP_COMPILER_FLAGS
    "-Os"
    "-g"
    "-report"
    "${CMAKE_CURRENT_SOURCE_DIR}/${BOARD}.xn"
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin")

## Create targets
set(CORE_LIST 1 5 8)
set(OP_LIST "nop" "waiteu")

## Single Tile Targets
foreach(core ${CORE_LIST})
    foreach(threadop ${OP_LIST})
        set(TARGET_NAME "${PROJECT_NAME}_1tile_${core}core_${threadop}.xe")
        add_executable(${TARGET_NAME})
        target_sources(${TARGET_NAME} PRIVATE "src/1tile_main.c")
        target_include_directories(${TARGET_NAME} PRIVATE "src")
        target_compile_options(${TARGET_NAME} PRIVATE ${APP_COMPILER_FLAGS})
        target_compile_definitions(${TARGET_NAME} PRIVATE "THREAD_OP=\"${threadop}\"" "CORES=${core}")
        target_link_options(${TARGET_NAME} PRIVATE ${APP_COMPILER_FLAGS})
    endforeach()

    set(TARGET_NAME "${PROJECT_NAME}_1tile_${core}core_wait_in_unused.xe")
    add_executable(${TARGET_NAME})
    target_sources(${TARGET_NAME} PRIVATE "src/1tile_main_fill_all_unused.c")
    target_include_directories(${TARGET_NAME} PRIVATE "src")
    target_compile_options(${TARGET_NAME} PRIVATE ${APP_COMPILER_FLAGS})
    target_compile_definitions(${TARGET_NAME} PRIVATE "THREAD_OP=\"${threadop}\"" "CORES=${core}")
    target_link_options(${TARGET_NAME} PRIVATE ${APP_COMPILER_FLAGS})
endforeach()

## 2 Tile Targets
foreach(core ${CORE_LIST})
    foreach(threadop ${OP_LIST})
        set(TARGET_NAME "${PROJECT_NAME}_2tile_${core}core_${threadop}.xe")
        add_executable(${TARGET_NAME})
        target_sources(${TARGET_NAME} PRIVATE "src/2tile_main.c" "src/main.xc")
        target_include_directories(${TARGET_NAME} PRIVATE "src")
        target_compile_options(${TARGET_NAME} PRIVATE ${APP_COMPILER_FLAGS})
        target_compile_definitions(${TARGET_NAME} PRIVATE "THREAD_OP=\"${threadop}\"" "CORES=${core}" "HP_FAST_MODE=0")
        target_link_options(${TARGET_NAME} PRIVATE ${APP_COMPILER_FLAGS})


        set(TARGET_NAME "${PROJECT_NAME}_2tile_${core}core_${threadop}_hpfast.xe")
        add_executable(${TARGET_NAME})
        target_sources(${TARGET_NAME} PRIVATE "src/2tile_main.c" "src/main.xc")
        target_include_directories(${TARGET_NAME} PRIVATE "src")
        target_compile_options(${TARGET_NAME} PRIVATE ${APP_COMPILER_FLAGS})
        target_compile_definitions(${TARGET_NAME} PRIVATE "THREAD_OP=\"${threadop}\"" "CORES=${core}" "HP_FAST_MODE=1")
        target_link_options(${TARGET_NAME} PRIVATE ${APP_COMPILER_FLAGS})
    endforeach()

    set(TARGET_NAME "${PROJECT_NAME}_2tile_${core}core_memop.xe")
    add_executable(${TARGET_NAME})
    target_sources(${TARGET_NAME} PRIVATE "src/2tile_main_mem_op.c" "src/main.xc")
    target_include_directories(${TARGET_NAME} PRIVATE "src")
    target_compile_options(${TARGET_NAME} PRIVATE ${APP_COMPILER_FLAGS})
    target_compile_definitions(${TARGET_NAME} PRIVATE "CORES=${core}" "HP_FAST_MODE=0")
    target_link_options(${TARGET_NAME} PRIVATE ${APP_COMPILER_FLAGS})

    set(TARGET_NAME "${PROJECT_NAME}_2tile_${core}core_memop_hpfast.xe")
    add_executable(${TARGET_NAME})
    target_sources(${TARGET_NAME} PRIVATE "src/2tile_main_mem_op.c" "src/main.xc")
    target_include_directories(${TARGET_NAME} PRIVATE "src")
    target_compile_options(${TARGET_NAME} PRIVATE ${APP_COMPILER_FLAGS})
    target_compile_definitions(${TARGET_NAME} PRIVATE "CORES=${core}" "HP_FAST_MODE=1")
    target_link_options(${TARGET_NAME} PRIVATE ${APP_COMPILER_FLAGS})

    set(TARGET_NAME "${PROJECT_NAME}_2tile_${core}core_vpuop.xe")
    add_executable(${TARGET_NAME})
    target_sources(${TARGET_NAME} PRIVATE "src/2tile_main_vpu_op.c" "src/main.xc" "src/vpu_op.S")
    target_include_directories(${TARGET_NAME} PRIVATE "src")
    target_compile_options(${TARGET_NAME} PRIVATE ${APP_COMPILER_FLAGS})
    target_compile_definitions(${TARGET_NAME} PRIVATE "CORES=${core}" "HP_FAST_MODE=0")
    target_link_options(${TARGET_NAME} PRIVATE ${APP_COMPILER_FLAGS})

    set(TARGET_NAME "${PROJECT_NAME}_2tile_${core}core_vpuop_hpfast.xe")
    add_executable(${TARGET_NAME})
    target_sources(${TARGET_NAME} PRIVATE "src/2tile_main_vpu_op.c" "src/main.xc" "src/vpu_op.S")
    target_include_directories(${TARGET_NAME} PRIVATE "src")
    target_compile_options(${TARGET_NAME} PRIVATE ${APP_COMPILER_FLAGS})
    target_compile_definitions(${TARGET_NAME} PRIVATE "CORES=${core}" "HP_FAST_MODE=1")
    target_link_options(${TARGET_NAME} PRIVATE ${APP_COMPILER_FLAGS})
endforeach()
