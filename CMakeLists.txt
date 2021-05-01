cmake_minimum_required(VERSION 3.11.0 FATAL_ERROR)
project(blink CXX C ASM)

include(arm_gcc_toolchain.cmake)


option(BLUE_PILL_EN "Build project for blue pill" ON)
option(STM32MP157_DK2_EN "Build project for stm32mp157_dk2" ON)


# Interface Library {{{


  # Compile Definitions {{{
    add_library("common_interface_lib" INTERFACE)
  
    target_compile_options("common_interface_lib" INTERFACE "$<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>")
    target_compile_options("common_interface_lib" INTERFACE "$<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions>")
    target_compile_options("common_interface_lib" INTERFACE "$<$<COMPILE_LANGUAGE:CXX>:-specs=nosys.specs>")
    target_compile_options("common_interface_lib" INTERFACE "$<$<COMPILE_LANGUAGE:CXX>:-specs=nano.specs>")
    target_compile_options("common_interface_lib" INTERFACE "$<$<COMPILE_LANGUAGE:CXX>:-O0>")
    target_compile_options("common_interface_lib" INTERFACE "$<$<COMPILE_LANGUAGE:CXX>:-Wl, --gc-sections>")
  # }}}
  
  
  # Libraries {{{  
    if(DEFINED ENV{CMSIS_CORE_PATH})
      target_include_directories ("common_interface_lib"
                                   INTERFACE "${CMAKE_CURRENT_LIST_DIR}/lib/cmsis_5/CMSIS/Core/Include/"
                                             "${CMAKE_CURRENT_LIST_DIR}/lib/")
    endif()  
    
  # }}}
  
  
# }}}





# blue pill {{{
if(BLUE_PILL_EN)
  add_executable("${CMAKE_PROJECT_NAME}_bp.elf")
  
  
  # Compile Definitions {{{
    target_compile_options("${CMAKE_PROJECT_NAME}_bp.elf" PRIVATE "-mcpu=cortex-m3"   "-mthumb"   "-mfloat-abi=soft"  "-ggdb3" )
    target_link_options   ("${CMAKE_PROJECT_NAME}_bp.elf" PRIVATE "-T${CMAKE_CURRENT_LIST_DIR}/bsp/blue_pill/memory.ld" "-Wl,-Map=${CMAKE_PROJECT_NAME}.map" "-Wl,--cref")
    target_link_options   ("${CMAKE_PROJECT_NAME}_bp.elf" PRIVATE "-mcpu=cortex-m3"   "-specs=nosys.specs"   "-specs=nano.specs"   "-mfloat-abi=soft"  )
    target_link_libraries ("${CMAKE_PROJECT_NAME}_bp.elf" PRIVATE "common_interface_lib")
  # }}}
  
  # Language standart {{{
  set_target_properties("${CMAKE_PROJECT_NAME}_bp.elf"
                        PROPERTIES
                          C_STANDARD 11
                          CXX_STANDARD 17
                          CXX_STANDARD_REQUIRED YES)
  # }}
  # Target Source {{{
    target_include_directories ("${CMAKE_PROJECT_NAME}_bp.elf"
                                 PRIVATE "${CMAKE_CURRENT_LIST_DIR}/bsp/blue_pill/"
                                         "${CMAKE_CURRENT_LIST_DIR}/src/"
                                         "${CMAKE_CURRENT_LIST_DIR}/")
                               
    target_sources("${CMAKE_PROJECT_NAME}_bp.elf"
                    PRIVATE "${CMAKE_CURRENT_LIST_DIR}/src/main.cpp"
                            "${CMAKE_CURRENT_LIST_DIR}/lib/mpptim/cortex.cpp"
                            "${CMAKE_CURRENT_LIST_DIR}/bsp/blue_pill/startup_gcc.cpp"
                            "${CMAKE_CURRENT_LIST_DIR}/bsp/blue_pill/bsp.cpp")
  # }}}   




  # Libraries {{{
 
    if(DEFINED ENV{CMSIS_STM32F1_PATH})
      target_include_directories ("${CMAKE_PROJECT_NAME}_bp.elf"
                                  PRIVATE "${CMAKE_CURRENT_LIST_DIR}/lib/cmsis_device_f1/Include/")
    endif()
  
  # }}} 

  
  
  # Post build command {{{
    add_custom_command(TARGET ${CMAKE_PROJECT_NAME}_bp.elf
                         POST_BUILD
                           COMMAND ${CMAKE_OBJCOPY} -Obinary ${CMAKE_PROJECT_NAME}_bp.elf ${CMAKE_PROJECT_NAME}_bp.bin
                           COMMAND ${CMAKE_OBJCOPY} -Oihex   ${CMAKE_PROJECT_NAME}_bp.elf ${CMAKE_PROJECT_NAME}_bp.hex
                           COMMAND ${CMAKE_SIZE_UTIL} ${CMAKE_PROJECT_NAME}_bp.elf 
                           COMMAND echo)
  #}}}
    
endif() 
# }}}




# stm32mp157_dk2 {{{
if(STM32MP157_DK2_EN)  
  add_executable("${CMAKE_PROJECT_NAME}_dk2.elf")
  
  
  # Compile Definitions {{{
    target_compile_options("${CMAKE_PROJECT_NAME}_dk2.elf" PRIVATE "-mcpu=cortex-m4"   "-mthumb"   "-mfloat-abi=hard"   "-mfpu=fpv4-sp-d16"  "-ggdb3" )
    target_link_options   ("${CMAKE_PROJECT_NAME}_dk2.elf" PRIVATE "-T${CMAKE_CURRENT_LIST_DIR}/bsp/stm32mp157_dk2/memory.ld" "-Wl,-Map=${CMAKE_PROJECT_NAME}_dk2.map" "-Wl,--cref")
    target_link_options   ("${CMAKE_PROJECT_NAME}_dk2.elf" PRIVATE "-mcpu=cortex-m4"   "-specs=nosys.specs"   "-specs=nano.specs"   "-mfloat-abi=hard"   "-mfpu=fpv4-sp-d16"  )
    target_link_libraries ("${CMAKE_PROJECT_NAME}_dk2.elf" PRIVATE "common_interface_lib")
  # }}}
  
  # Language standart {{{
  set_target_properties("${CMAKE_PROJECT_NAME}_dk2.elf"
                        PROPERTIES
                          C_STANDARD 11
                          CXX_STANDARD 17
                          CXX_STANDARD_REQUIRED YES)
  # }}
  # Target Source {{{
    target_include_directories ("${CMAKE_PROJECT_NAME}_dk2.elf"
                                 PRIVATE "${CMAKE_CURRENT_LIST_DIR}/bsp/stm32mp157_dk2/"
                                         "${CMAKE_CURRENT_LIST_DIR}/src/"
                                         "${CMAKE_CURRENT_LIST_DIR}/inc/")
                               
    target_sources("${CMAKE_PROJECT_NAME}_dk2.elf"
                    PRIVATE "${CMAKE_CURRENT_LIST_DIR}/src/main.cpp"
                            "${CMAKE_CURRENT_LIST_DIR}/bsp/stm32mp157_dk2/bsp.cpp"
                            "${CMAKE_CURRENT_LIST_DIR}/lib/mpptim/cortex.cpp"
                            "${CMAKE_CURRENT_LIST_DIR}/bsp/stm32mp157_dk2/startup_gcc.cpp" )
  # }}}   




  # Libraries {{{
 
    #if(DEFINED ENV{CMSIS_STM32MP1_PATH})
    #  target_include_directories ("${CMAKE_PROJECT_NAME}_dk2.elf"
    #                              PRIVATE "$ENV{CMSIS_STM32MP1_PATH}")
    #endif()
  
  # }}} 

  
  
  # Post build command {{{
    add_custom_command(TARGET ${CMAKE_PROJECT_NAME}_dk2.elf
                         POST_BUILD
                           COMMAND ${CMAKE_OBJCOPY} -Obinary ${CMAKE_PROJECT_NAME}_dk2.elf ${CMAKE_PROJECT_NAME}_dk2.bin
                           COMMAND ${CMAKE_OBJCOPY} -Oihex   ${CMAKE_PROJECT_NAME}_dk2.elf ${CMAKE_PROJECT_NAME}_dk2.hex
                           COMMAND ${CMAKE_SIZE_UTIL} ${CMAKE_PROJECT_NAME}_dk2.elf 
                           COMMAND echo)
  #}}}
endif()  
# }}}
    
    
    
    

