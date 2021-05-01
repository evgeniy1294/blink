# System {{{
  set(CMAKE_SYSTEM_NAME "Generic")
  set(CMAKE_SYSTEM_PROCESSOR "ARM")
# }}}



# Finding toolchain (Linux only) {{{
  set(TOOLCHAIN_PREFIX "arm-none-eabi")

  execute_process(
    COMMAND "which" ${TOOLCHAIN_PREFIX}-gcc
    OUTPUT_VARIABLE BINUTILS_PATH 
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )
  get_filename_component(ARM_TOOLCHAIN_DIR ${BINUTILS_PATH} DIRECTORY)
# }}}



# Without that flag CMake is not able to pass test compilation check {{{
  if (${CMAKE_VERSION} VERSION_EQUAL "3.6.0" OR ${CMAKE_VERSION} VERSION_GREATER "3.6")
    set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
  else()
    set(CMAKE_EXE_LINKER_FLAGS_INIT "--specs=nosys.specs")
  endif()
# }}}



# Utility  {{{
  set(CMAKE_AR        "${ARM_TOOLCHAIN_DIR}/${TOOLCHAIN_PREFIX}-ar")
  set(CMAKE_RANLIB    "${ARM_TOOLCHAIN_DIR}/${TOOLCHAIN_PREFIX}-ranlib")
  set(CMAKE_OBJCOPY   "${ARM_TOOLCHAIN_DIR}/${TOOLCHAIN_PREFIX}-objcopy")
  set(CMAKE_SIZE_UTIL "${ARM_TOOLCHAIN_DIR}/${TOOLCHAIN_PREFIX}-size")
# }}}



# ASM {{{
  set(CMAKE_ASM_COMPILER "${ARM_TOOLCHAIN_DIR}/${TOOLCHAIN_PREFIX}-as")
  set(CMAKE_ASM_CREATE_SHARED_LIBRARY "echo 'shared libraries not supported' && 1")
  set(CMAKE_ASM_CREATE_SHARED_MODULE  "echo 'shared modules not supported' && 1")
# }}}



# C compiler {{{
  set(CMAKE_C_COMPILER "${ARM_TOOLCHAIN_DIR}/${TOOLCHAIN_PREFIX}-gcc")
  set(CMAKE_C_CREATE_SHARED_LIBRARY "echo 'shared libraries not supported' && 1")
  set(CMAKE_C_CREATE_SHARED_MODULE  "echo 'shared modules not supported' && 1")
# }}}



# C++ compiler {{{
  set(CMAKE_CXX_COMPILER "${ARM_TOOLCHAIN_DIR}/${TOOLCHAIN_PREFIX}-g++")
  set(CMAKE_CXX_CREATE_SHARED_LIBRARY "echo 'shared libraries not supported' && 1")
  set(CMAKE_CXX_CREATE_SHARED_MODULE  "echo 'shared modules not supported' && 1")
# }}}



# Root {{{
  set(CMAKE_FIND_ROOT_PATH ${BINUTILS_PATH})
  set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
  set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
  set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
  set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
# }}}

