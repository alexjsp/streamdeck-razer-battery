cmake_minimum_required(VERSION 3.10)

project(com.alexjsp.razer-battery VERSION 1.2)

if (APPLE)
  set(
    STREAMDECK_PLUGIN_DIR
    "$ENV{HOME}/Library/ApplicationSupport/com.elgato.StreamDeck/Plugins"
  )
endif()
set(
  CMAKE_INSTALL_PREFIX
  "${STREAMDECK_PLUGIN_DIR}/${CMAKE_PROJECT_NAME}"
  CACHE STRING "See cmake documentation"
)

set(CMAKE_CXX_STANDARD 11)
set(CXX_STANDARD_REQUIRED true)
if (MSVC)
  add_definitions("/Zc:__cplusplus" -DUNICODE=1)
endif()
include_directories("${CMAKE_SOURCE_DIR}")

include("StreamDeckSDK.cmake")

set(
  SOURCES
  MyStreamDeckPlugin.cpp
  main.cpp
)
if (APPLE)
  include_directories("macOS/librazermacos/src/include")
  list(APPEND SOURCES macOS/librazermacos/src/lib/razeraccessory_driver.c)
  list(APPEND SOURCES macOS/librazermacos/src/lib/razerchromacommon.c)
  list(APPEND SOURCES macOS/librazermacos/src/lib/razercommon.c)
  list(APPEND SOURCES macOS/librazermacos/src/lib/razerdevice.c)
  list(APPEND SOURCES macOS/librazermacos/src/lib/razeregpu_driver.c)
  list(APPEND SOURCES macOS/librazermacos/src/lib/razerheadphone_driver.c)
  list(APPEND SOURCES macOS/librazermacos/src/lib/razerkbd_driver.c)
  list(APPEND SOURCES macOS/librazermacos/src/lib/razerkraken_driver.c)
  list(APPEND SOURCES macOS/librazermacos/src/lib/razermouse_driver.c)
  list(APPEND SOURCES macOS/librazermacos/src/lib/razermousedock_driver.c)
  list(APPEND SOURCES macOS/librazermacos/src/lib/razermousemat_driver.c)
  list(APPEND SOURCES macOS/RazerBatteryHelper.cpp)
elseif (WIN32)
  list(APPEND SOURCES Windows/RazerBatteryHelper.cpp)
endif()
add_executable(
  razer-battery
  ${SOURCES}
)
if (APPLE)
  find_library(CF CoreFoundation)
  find_library(IOK IOKit)
  target_link_libraries(razer-battery ${CF} ${IOK})
endif()
target_link_libraries(razer-battery StreamDeckSDK)
