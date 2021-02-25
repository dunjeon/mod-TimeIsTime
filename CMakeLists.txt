AC_ADD_SCRIPT("${CMAKE_CURRENT_LIST_DIR}/src/TimeIsTime.cpp")
AC_ADD_SCRIPT_LOADER("TimeIsTime" "${CMAKE_CURRENT_LIST_DIR}/src/loader.h")

AC_ADD_CONFIG_FILE("${CMAKE_CURRENT_LIST_DIR}/conf/mod-time_is_time.conf.dist")