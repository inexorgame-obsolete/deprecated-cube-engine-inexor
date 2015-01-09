prepend(CLIENT_SOURCES_ENGINE ${SOURCE_DIR}/engine
    3dgui.cpp
    bih.cpp
    blend.cpp
    client.cpp
    command.cpp
    console.cpp
    decal.cpp
    dynlight.cpp
    grass.cpp
    main.cpp
    material.cpp
    menus.cpp
    movie.cpp
    normal.cpp
    octa.cpp
    octaedit.cpp
    octarender.cpp
    physics.cpp
    pvs.cpp
    rendergl.cpp
    rendermodel.cpp
    renderparticles.cpp
    rendersky.cpp
    rendertext.cpp
    renderva.cpp
    server.cpp
    shader.cpp
    sound.cpp
    texture.cpp
    water.cpp
    world.cpp
    worldio.cpp
    serverbrowser.cpp
    shadowmap.cpp
    lightmap.cpp
    glare.cpp
    blob.cpp)

prepend(CLIENT_SOURCES_FPSGAME ${SOURCE_DIR}/fpsgame
    ai.cpp
    client.cpp
    entities.cpp
    fps.cpp
    monster.cpp
    movable.cpp
    render.cpp
    scoreboard.cpp
    server.cpp
    waypoint.cpp
    weapon.cpp)

set(CLIENT_SOURCES_UI
    ${CMAKE_CURRENT_SOURCE_DIR}/../ui/cefapp
    ${CMAKE_CURRENT_SOURCE_DIR}/../ui/cefclienthandler
    ${CMAKE_CURRENT_SOURCE_DIR}/../ui/cefconsole
    ${CMAKE_CURRENT_SOURCE_DIR}/../ui/cefcontextmanager
    ${CMAKE_CURRENT_SOURCE_DIR}/../ui/cefcontextprovider
    ${CMAKE_CURRENT_SOURCE_DIR}/../ui/cefdebug
    ${CMAKE_CURRENT_SOURCE_DIR}/../ui/cefevent
    ${CMAKE_CURRENT_SOURCE_DIR}/../ui/cefeventmanager
    ${CMAKE_CURRENT_SOURCE_DIR}/../ui/ceflayer
    ${CMAKE_CURRENT_SOURCE_DIR}/../ui/ceflayermanager
    ${CMAKE_CURRENT_SOURCE_DIR}/../ui/cefmenu
    ${CMAKE_CURRENT_SOURCE_DIR}/../ui/cefmouse
    ${CMAKE_CURRENT_SOURCE_DIR}/../ui/cefrenderhandler
    ${CMAKE_CURRENT_SOURCE_DIR}/../ui/cefrequestcontexthandler

set(CLIENT_SOURCES_CEFDLL
    ${CMAKE_CURRENT_SOURCE_DIR}/../libraries/cef3/libcef_dll
)

set(CLIENT_SOURCES
  ${CLIENT_SOURCES_UI}
  ${CLIENT_SOURCES_CEFDLL}
  ${CLIENT_SOURCES_ENGINE}
  ${CLIENT_SOURCES_FPSGAME}
  ${COMMON_SOURCES} CACHE INTERNAL "")

# Set Binary name
set(CLIENT_BINARY inexor CACHE INTERNAL "Client binary name.")

add_definitions(-DCLIENT)

if(OS_LINUX)
    set(ADDITIONAL_LIBRARIES ${ADDITIONAL_LIBRARIES} dl rt)
elseif(OS_MACOSX)
  set(CLIENT_SOURCES ${CLIENT_SOURCES} engine/macutils.mm)
elseif(OS_WINDOWS)
    set(ADDITIONAL_LIBRARIES ${ADDITIONAL_LIBRARIES} opengl32)

    if(MSVC)
        set(ADDITIONAL_LIBRARIES ${ADDITIONAL_LIBRARIES} dbghelp)
    else()
        add_definitions(-mwindows)
    endif()
endif()

set(CMAKE_SKIP_BUILD_RPATH FALSE)
set(CEF_DLL_LIBRARY "libcef_dll_wrapper")
set(CEF_BASE_DIR "${PROJECT_SOURCE_DIR}/src/libraries/cef3")
set(ICUDTL_DAT "${CEF_BASE_DIR}/Resources/icudtl.dat")
if(BUILD_TARGET_LINUX)
    set(CEF_LINUX_DIR "${CEF_BASE_DIR}/cef_bin/linux")
    if(BUILD_TARGET_X86)
        set(CEF_LINUX_X86_DIR "${CEF_LINUX_DIR}/bin_x86")
        set(UDEV_LIBRARY "${CEF_LINUX_X86_DIR}/libudev.so")
        set(CEF_LIBRARY "${CEF_LINUX_X86_DIR}/libcef.so")
        set(FFMPEGSUMO_LIBRARY "${CEF_LINUX_X86_DIR}/libffmpegsumo.so")
        set(CHROME_SANDBOX_BIN "${CEF_LINUX_X86_DIR}/chrome-sandbox")
    else()
        set(CEF_LINUX_X86_64_DIR "${CEF_LINUX_DIR}/bin_x86_64")
        set(UDEV_LIBRARY "${CEF_LINUX_X86_64_DIR}/libudev.so")
        set(CEF_LIBRARY "${CEF_LINUX_X86_64_DIR}/libcef.so")
        set(FFMPEGSUMO_LIBRARY "${CEF_LINUX_X86_64_DIR}/libffmpegsumo.so")
        set(CHROME_SANDBOX_BIN "${CEF_LINUX_X86_64_DIR}/chrome-sandbox")
    endif()
elseif(BUILD_TARGET_WINDOWS)
    if(BUILD_TARGET_X86)
        set(CEF_LIBRARY "${CEF_BASE_DIR}/cef_bin/windows/lib32/libcef.lib")
    else()
        set(CEF_LIBRARY "${CEF_BASE_DIR}/cef_bin/windows/lib64/libcef.lib")
    endif()
endif()

set(CEF_LIBRARIES "${CEF_DLL_LIBRARY};-Wl,-rpath,. ${CEF_LIBRARY};-Wl,-rpath,. ${UDEV_LIBRARY}")

add_app(${CLIENT_BINARY} ${CLIENT_SOURCES})
target_link_libs(${CLIENT_BINARY}
  ${COMMON_LIBS}
  ${SDL2_LIBRARIES}
  ${OPENGL_LIBRARIES}
  ${ADDITIONAL_LIBRARIES}
  ${CEF_LIBRARIES})

config_net(${CLIENT_BINARY})
config_rpc(${CLIENT_BINARY})
config_util(${CLIENT_BINARY})
config_muparser(${CLIENT_BINARY})

message(STATUS "UDEV_LIBRARY ${UDEV_LIBRARY}")

file(COPY ${UDEV_LIBRARY} DESTINATION ${INSTALL_RUNTIME_DIR})
file(COPY ${CEF_LIBRARY} DESTINATION ${INSTALL_RUNTIME_DIR})
file(COPY ${FFMPEGSUMO_LIBRARY} DESTINATION ${INSTALL_RUNTIME_DIR})
file(COPY ${CHROME_SANDBOX_BIN} DESTINATION ${INSTALL_RUNTIME_DIR})
file(COPY ${ICUDTL_DAT} DESTINATION ${INSTALL_RUNTIME_DIR})
