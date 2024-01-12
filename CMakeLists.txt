# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.20.0)

if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
	cmake_policy(SET CMP0135 NEW)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (NOT DEFINED CMAKE_TOOLCHAIN_FILE)
	set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/projects/arm-none-eabi-gcc.cmake)
endif()

project(template)

enable_language(C CXX ASM)

include(${CMAKE_SOURCE_DIR}/projects/version.cmake)
include(${CMAKE_SOURCE_DIR}/projects/app.cmake)
