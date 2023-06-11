find_package(X11 REQUIRED)

add_library(os-lib
   window.cc
   priv/x11.cc)
target_include_directories(os-lib PUBLIC "..")
target_link_libraries(os-lib X11::X11)