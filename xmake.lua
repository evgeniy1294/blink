
-- define toolchain
toolchain("arm-none-eabi-gcc")
    set_kind("standalone")
    set_bindir("/usr/bin")
    set_sdkdir("/usr/arm-none-eabi/")
    
    set_toolset("cc",    "arm-none-eabi-gcc")
    set_toolset("cxx",   "arm-none-eabi-g++")
    set_toolset("ld",    "arm-none-eabi-g++")
    set_toolset("sh",    "arm-none-eabi-g++", "arm-none-eabi-gcc")
    set_toolset("ar",    "arm-none-eabi-ar")
    set_toolset("ex",    "arm-none-eabi-ar")
    set_toolset("strip", "arm-none-eabi-strip")
    set_toolset("as",    "arm-none-eabi-as")

    -- check toolchain
    on_check(function (toolchain)
      return import("lib.detect.find_tool")("arm-none-eabi-gcc")
    end)
    
    -- on load
    on_load(function (toolchain)
        -- set arch
        local march = "arm"
            
        -- init flags for c++ 
        toolchain:add("cxxflags", "-mthumb", "-fno-rtti", "-fno-exceptions", "-specs=nosys.specs", "-specs=nano.specs")
        toolchain:add("ldflags", "-Wl,--cref", "-specs=nosys.specs", "-specs=nano.specs")
    end)
toolchain_end()        
        
        
        
        
        

target("blink_bp")
    set_kind("binary")
    set_toolchains("arm-none-eabi-gcc")
    set_plat("cross")
    set_arch("arm")
    set_policy("check.auto_ignore_flags", false)
    
    -- Enable this target
    set_enabled(true)
    
    -- Set c code standard: c99, c++ code standard: c++11
    set_languages("c11", "cxx17")

    -- Optimization rules
    add_rules("mode.debug", "mode.minsizerel")
    
    -- Add C++ flags
    add_cxxflags("-mcpu=cortex-m3", "-mfloat-abi=soft", "-ggdb3")
    
    -- Add ld flags
    add_ldflags("-T$(projectdir)/bsp/blue_pill/memory.ld", "-Wl,-Map=$(buildir)/cross/arm/$(mode)/blink_bp.map", "-mcpu=cortex-m3")
    
    -- Add files 
    add_files( "$(projectdir)/src/*.cpp", 
               "$(projectdir)/bsp/blue_pill/*.cpp",
               "$(projectdir)/lib/mpptim/cortex.cpp" )
    
    -- Add include directory
    add_includedirs( "$(projectdir)/src", 
                     "$(projectdir)/bsp/blue_pill/",
                     "$(projectdir)/lib/",
                     "$(projectdir)/lib/cmsis_5/CMSIS/Core/Include/",
                     "$(projectdir)/lib/cmsis_device_f1/Include/" )
    -- Postbuild
    after_build(function (target)
        path = "$(buildir)/"..target:plat().."/"..target:arch().."/$(mode)/"
               
        -- Generate hex-file
        os.run("objcopy -Oihex "..path..target:name().." "..path..target:name()..".hex")
               
        -- Size
        os.exec("size "..path..target:name())
        os.exec("echo")
    end)
target_end() --blink_bp    







target("blink_dk2")
    set_kind("binary")
    set_toolchains("arm-none-eabi-gcc")
    set_plat("cross")
    set_arch("arm")
    set_policy("check.auto_ignore_flags", false)
    
    -- Enable this target
    set_enabled(true)
    
    -- Set c code standard: c99, c++ code standard: c++11
    set_languages("c11", "cxx17")

    -- Optimization rules
    add_rules("mode.debug", "mode.minsizerel")
    
    -- Add C++ flags
    add_cxxflags("-mcpu=cortex-m4", "-mfloat-abi=hard", "-mfpu=fpv4-sp-d16", "-ggdb3" )
    
    -- Add ld flags
    add_ldflags("-T$(projectdir)/bsp/stm32mp157_dk2/memory.ld", "-Wl,-Map=$(buildir)/cross/arm/$(mode)/blink_dk2.map", "-mcpu=cortex-m4", "-mfloat-abi=hard", "-mfpu=fpv4-sp-d16")
    
    -- Add files 
    add_files( "$(projectdir)/src/*.cpp", 
               "$(projectdir)/bsp/stm32mp157_dk2/*.cpp",
               "$(projectdir)/lib/mpptim/cortex.cpp" )
    
    -- Add include directory
    add_includedirs( "$(projectdir)/src", 
                     "$(projectdir)/bsp/stm32mp157_dk2/",
                     "$(projectdir)/lib/",
                     "$(projectdir)/lib/cmsis_5/CMSIS/Core/Include/")
    -- Postbuild
    after_build(function (target)
        path = "$(buildir)/"..target:plat().."/"..target:arch().."/$(mode)/"
               
        -- Generate hex-file
        os.run("objcopy -Oihex "..path..target:name().." "..path..target:name()..".hex")
               
        -- Size
        os.exec("size "..path..target:name())
        os.exec("echo")
    end)
target_end() --blink_dk2    




target("blink_f4_disco")
    set_kind("binary")
    set_toolchains("arm-none-eabi-gcc")
    set_plat("cross")
    set_arch("arm")
    set_policy("check.auto_ignore_flags", false)
    
    -- Enable this target
    set_enabled(true)
    
    -- Set c code standard: c99, c++ code standard: c++11
    set_languages("c11", "cxx17")

    -- Optimization rules
    add_rules("mode.debug", "mode.minsizerel")
    
    -- Add C++ flags
    add_cxxflags("-mcpu=cortex-m4", "-mfloat-abi=hard", "-mfpu=fpv4-sp-d16", "-ggdb3" )
    
    -- Add ld flags
    add_ldflags("-T$(projectdir)/bsp/stm32f407g_disco/memory.ld", "-Wl,-Map=$(buildir)/cross/arm/$(mode)/blink_f4_disco.map", "-mcpu=cortex-m4", "-mfloat-abi=hard", "-mfpu=fpv4-sp-d16")
    
    -- Add files 
    add_files( "$(projectdir)/src/*.cpp", 
               "$(projectdir)/bsp/stm32f407g_disco/*.cpp",
               "$(projectdir)/lib/mpptim/cortex.cpp" )
    
    -- Add include directory
    add_includedirs( "$(projectdir)/src", 
                     "$(projectdir)/bsp/stm32f407g_disco/",
                     "$(projectdir)/lib/",
                     "$(projectdir)/lib/cmsis_5/CMSIS/Core/Include/",
                     "$(projectdir)/lib/cmsis_device_f4/Include/" )
    -- Postbuild
    after_build(function (target)
        path = "$(buildir)/"..target:plat().."/"..target:arch().."/$(mode)/"
               
        -- Generate hex-file
        os.run("objcopy -Oihex "..path..target:name().." "..path..target:name()..".hex")
               
        -- Size
        os.exec("size "..path..target:name())
        os.exec("echo")
    end)
target_end() --blink_f4_disco




target("blink_longan")
    set_kind("binary")
    set_toolchains("riscv32imac-kgp-elf")
    set_plat("cross")
    set_arch("riscv")
    set_policy("check.auto_ignore_flags", false)
    
    -- Enable this target
    set_enabled(false)
    
    -- Set c code standard: c99, c++ code standard: c++11
    set_languages("c11", "cxx17")

    -- Optimization rules
    add_rules("mode.debug", "mode.minsizerel")
    
    -- Add C++ flags
    add_cxxflags("-march=rv32imac" , "-ggdb3" )
    
    -- Add ld flags
    add_ldflags("-T$(projectdir)/bsp/longan_nano/memory.ld", "-Wl,-Map=$(buildir)/cross/arm/$(mode)/blink_f4_disco.map", "-march=rv32imac",  "-fno-lto")
    
    -- Add files 
    add_files( "$(projectdir)/src/*.cpp", 
               "$(projectdir)/bsp/longan_nano/*.cpp",
               "$(projectdir)/lib/mpptim/cortex.cpp" )
    
    -- Add include directory
    add_includedirs( "$(projectdir)/src", 
                     "$(projectdir)/bsp/longan_nano/",
                     "$(projectdir)/lib/"
                   )
    -- Postbuild
    after_build(function (target)
        path = "$(buildir)/"..target:plat().."/"..target:arch().."/$(mode)/"
               
        -- Generate hex-file
        os.run("objcopy -Oihex "..path..target:name().." "..path..target:name()..".hex")
               
        -- Size
        os.exec("size "..path..target:name())
        os.exec("echo")
    end)
target_end() --blink_longan



