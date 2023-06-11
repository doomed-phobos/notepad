include(FindSkia)

set(NOTEPAD_SOURCES
   window.cc)

if(UNIX)
   find_package(X11 REQUIRED)
   set(NOTEPAD_COMPILE_DEFINITIONS -DNOTEPAD_UNIX)   
   set(NOTEPAD_LIBRARIES X11::X11)
   list(APPEND NOTEPAD_SOURCES
      priv/x11/x11.cc)
elseif(WIN32)
   set(NOTEPAD_COMPILE_DEFINITIONS -DNOTEPAD_WIN)   
endif()

add_library(os-lib ${NOTEPAD_SOURCES})
target_include_directories(os-lib PUBLIC "..")
target_compile_definitions(os-lib PUBLIC ${NOTEPAD_COMPILE_DEFINITIONS})
target_link_libraries(os-lib base-lib skia ${NOTEPAD_LIBRARIES})