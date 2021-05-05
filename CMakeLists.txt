cmake_minimum_required(VERSION 3.11.0 FATAL_ERROR)
include(arm_gcc_toolchain.cmake)

project(blink CXX C ASM)



option(BLUE_PILL_EN "Build project for blue pill" ON)
option(STM32MP157_DK2_EN "Build project for stm32mp157_dk2" ON)
option(STM32F407_DISCO_EN "Build project for stm32f407-discovery" ON)


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
  target_include_directories ("common_interface_lib"
                               INTERFACE "${CMAKE_CURRENT_LIST_DIR}/lib/cmsis_5/CMSIS/Core/Include/"
                                         "${CMAKE_CURRENT_LIST_DIR}/lib/")

    
  # }}}
  
  
# }}}




# blue pill {{{
if(BLUE_PILL_EN)
  add_executable("${CMAKE_PROJECT_NAME}_bp")
  
  
  # Compile Definitions {{{
    target_compile_options("${CMAKE_PROJECT_NAME}_bp" PRIVATE "-mcpu=cortex-m3"   "-mthumb"   "-mfloat-abi=soft"  "-ggdb3" )
    target_link_options   ("${CMAKE_PROJECT_NAME}_bp" PRIVATE "-T${CMAKE_CURRENT_LIST_DIR}/bsp/blue_pill/memory.ld" "-Wl,-Map=${CMAKE_PROJECT_NAME}.map" "-Wl,--cref")
    target_link_options   ("${CMAKE_PROJECT_NAME}_bp" PRIVATE "-mcpu=cortex-m3"   "-specs=nosys.specs"   "-specs=nano.specs"   "-mfloat-abi=soft"  )
    target_link_libraries ("${CMAKE_PROJECT_NAME}_bp" PRIVATE "common_interface_lib")
  # }}}
  
  # Language standart {{{
  set_target_properties("${CMAKE_PROJECT_NAME}_bp"
                        PROPERTIES
                          C_STANDARD 11
                          CXX_STANDARD 17
                          CXX_STANDARD_REQUIRED YES)
  # }}
  # Target Source {{{
    target_include_directories ("${CMAKE_PROJECT_NAME}_bp"
                                 PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/bsp/blue_pill/"
                                         "${CMAKE_CURRENT_SOURCE_DIR}/src/"
                                         "${CMAKE_CURRENT_SOURCE_DIR}/")
                               
    target_sources("${CMAKE_PROJECT_NAME}_bp"
                    PRIVATE "${CMAKE_CURRENT_LIST_DIR}/src/main.cpp"
                            "${CMAKE_CURRENT_LIST_DIR}/lib/mpptim/cortex.cpp"
                            "${CMAKE_CURRENT_LIST_DIR}/bsp/blue_pill/startup_gcc.cpp"
                            "${CMAKE_CURRENT_LIST_DIR}/bsp/blue_pill/bsp.cpp")
  # }}}   




  # Libraries {{{
    target_include_directories ("${CMAKE_PROJECT_NAME}_bp"
                                PRIVATE "${CMAKE_CURRENT_LIST_DIR}/lib/cmsis_device_f1/Include/")
  
  # }}} 

  
  
  # Post build command {{{
    add_custom_command(TARGET ${CMAKE_PROJECT_NAME}_bp
                         POST_BUILD
                           COMMAND ${CMAKE_OBJCOPY} -Obinary ${CMAKE_PROJECT_NAME}_bp ${CMAKE_PROJECT_NAME}_bp.bin
                           COMMAND ${CMAKE_OBJCOPY} -Oihex   ${CMAKE_PROJECT_NAME}_bp ${CMAKE_PROJECT_NAME}_bp.hex
                           COMMAND ${CMAKE_SIZE_UTIL} ${CMAKE_PROJECT_NAME}_bp
                           COMMAND echo)
  #}}}
    
endif() 
# }}}




# stm32mp157_dk2 {{{
if(STM32MP157_DK2_EN)  
  add_executable("${CMAKE_PROJECT_NAME}_dk2")
  
  
  # Compile Definitions {{{
    target_compile_options("${CMAKE_PROJECT_NAME}_dk2" PRIVATE "-mcpu=cortex-m4"   "-mthumb"   "-mfloat-abi=hard"   "-mfpu=fpv4-sp-d16"  "-ggdb3" )
    target_link_options   ("${CMAKE_PROJECT_NAME}_dk2" PRIVATE "-T${CMAKE_CURRENT_LIST_DIR}/bsp/stm32mp157_dk2/memory.ld" "-Wl,-Map=${CMAKE_PROJECT_NAME}_dk2.map" "-Wl,--cref")
    target_link_options   ("${CMAKE_PROJECT_NAME}_dk2" PRIVATE "-mcpu=cortex-m4"   "-specs=nosys.specs"   "-specs=nano.specs"   "-mfloat-abi=hard"   "-mfpu=fpv4-sp-d16"  )
    target_link_libraries ("${CMAKE_PROJECT_NAME}_dk2" PRIVATE "common_interface_lib")
  # }}}
  
  # Language standart {{{
  set_target_properties("${CMAKE_PROJECT_NAME}_dk2"
                        PROPERTIES
                          C_STANDARD 11
                          CXX_STANDARD 17
                          CXX_STANDARD_REQUIRED YES)
  # }}
  # Target Source {{{
    target_include_directories ("${CMAKE_PROJECT_NAME}_dk2"
                                 PRIVATE "${CMAKE_CURRENT_LIST_DIR}/bsp/stm32mp157_dk2/"
                                         "${CMAKE_CURRENT_LIST_DIR}/src/"
                                         "${CMAKE_CURRENT_LIST_DIR}/inc/")
                               
    target_sources("${CMAKE_PROJECT_NAME}_dk2"
                    PRIVATE "${CMAKE_CURRENT_LIST_DIR}/src/main.cpp"
                            "${CMAKE_CURRENT_LIST_DIR}/bsp/stm32mp157_dk2/bsp.cpp"
                            "${CMAKE_CURRENT_LIST_DIR}/lib/mpptim/cortex.cpp"
                            "${CMAKE_CURRENT_LIST_DIR}/bsp/stm32mp157_dk2/startup_gcc.cpp" )
  # }}}   




  # Libraries {{{
 
  
  # }}} 

  
  
  # Post build command {{{
    add_custom_command(TARGET ${CMAKE_PROJECT_NAME}_dk2
                         POST_BUILD
                           COMMAND ${CMAKE_OBJCOPY} -Obinary ${CMAKE_PROJECT_NAME}_dk2 ${CMAKE_PROJECT_NAME}_dk2.bin
                           COMMAND ${CMAKE_OBJCOPY} -Oihex   ${CMAKE_PROJECT_NAME}_dk2 ${CMAKE_PROJECT_NAME}_dk2.hex
                           COMMAND ${CMAKE_SIZE_UTIL} ${CMAKE_PROJECT_NAME}_dk2
                           COMMAND echo)
  #}}}
endif()  
# }}}
    
    
    
# stm32mp157_dk2 {{{
if(STM32F407_DISCO_EN)  
  add_executable("${CMAKE_PROJECT_NAME}_f4_disco")
  
  
  # Compile Definitions {{{
    target_compile_options("${CMAKE_PROJECT_NAME}_f4_disco" PRIVATE "-mcpu=cortex-m4"   "-mthumb"   "-mfloat-abi=hard"   "-mfpu=fpv4-sp-d16"  "-ggdb3" )
    target_link_options   ("${CMAKE_PROJECT_NAME}_f4_disco" PRIVATE "-T${CMAKE_CURRENT_LIST_DIR}/bsp/stm32f407g_disco/memory.ld" "-Wl,-Map=${CMAKE_PROJECT_NAME}_dk2.map" "-Wl,--cref")
    target_link_options   ("${CMAKE_PROJECT_NAME}_f4_disco" PRIVATE "-mcpu=cortex-m4"   "-specs=nosys.specs"   "-specs=nano.specs"   "-mfloat-abi=hard"   "-mfpu=fpv4-sp-d16"  )
    target_link_libraries ("${CMAKE_PROJECT_NAME}_f4_disco" PRIVATE "common_interface_lib")
  # }}}
  
  # Language standart {{{
  set_target_properties("${CMAKE_PROJECT_NAME}_f4_disco"
                        PROPERTIES
                          C_STANDARD 11
                          CXX_STANDARD 17
                          CXX_STANDARD_REQUIRED YES)
  # }}
  # Target Source {{{
    target_include_directories ("${CMAKE_PROJECT_NAME}_f4_disco"
                                 PRIVATE "${CMAKE_CURRENT_LIST_DIR}/bsp/stm32f407g_disco/"
                                         "${CMAKE_CURRENT_LIST_DIR}/src/"
                                         "${CMAKE_CURRENT_LIST_DIR}/inc/")
                               
    target_sources("${CMAKE_PROJECT_NAME}_f4_disco"
                    PRIVATE "${CMAKE_CURRENT_LIST_DIR}/src/main.cpp"
                            "${CMAKE_CURRENT_LIST_DIR}/bsp/stm32f407g_disco/bsp.cpp"
                            "${CMAKE_CURRENT_LIST_DIR}/lib/mpptim/cortex.cpp"
                            "${CMAKE_CURRENT_LIST_DIR}/bsp/stm32f407g_disco/startup_gcc.cpp" )
  # }}}   




  # Libraries {{{
    target_include_directories ("${CMAKE_PROJECT_NAME}_f4_disco"
                                PRIVATE "${CMAKE_CURRENT_LIST_DIR}/lib/cmsis_device_f4/Include/")

  # }}} 

  
  
  # Post build command {{{
    add_custom_command(TARGET ${CMAKE_PROJECT_NAME}_f4_disco
                         POST_BUILD
                           COMMAND ${CMAKE_OBJCOPY} -Obinary ${CMAKE_PROJECT_NAME}_f4_disco ${CMAKE_PROJECT_NAME}_f4_disco.bin
                           COMMAND ${CMAKE_OBJCOPY} -Oihex   ${CMAKE_PROJECT_NAME}_f4_disco ${CMAKE_PROJECT_NAME}_f4_disco.hex
                           COMMAND ${CMAKE_SIZE_UTIL} ${CMAKE_PROJECT_NAME}_f4_disco
                           COMMAND echo)
  #}}}
endif()  
# }}}

