#set (PROJECT_SOURCE_DIR src)
#set (PROJECT_BINARY_DIR src)

add_library(nss-maria SHARED configuration.c libnss-maria.c)

# The version number.
# soname (MAJOR) version must be 2
set (nss-maria_VERSION_MAJOR 2)
set (nss-maria_VERSION_MINOR 1)
set (nss-maria_VERSION_PATCH 0)

set(nss-maria_VERSION ${nss-maria_VERSION_MAJOR}.${nss-maria_VERSION_MINOR}.${nss-maria_VERSION_PATCH})

set_target_properties(nss-maria PROPERTIES
  VERSION ${nss-maria_VERSION}
  SOVERSION ${nss-maria_VERSION_MAJOR}
)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "configuration.h.in"
  "configuration.h"
)
