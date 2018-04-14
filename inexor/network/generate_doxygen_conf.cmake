# This file generates a doxygen.conf from a template of it, using given data.

# Generally these values must be defined:
#  DOXYFILE_TEMPLATE_IN
#  DOXYFILE_OUT
#Data must be defined
#  DOXYGEN_XML_DIR
#  SOURCE_FILES
string(REPLACE ".cpp\" ".cpp" SOURCE_FILES ${SOURCE_FILES})

message(STATUS "this is the SOURCE_FILES list: ${SOURCE_FILES}")
configure_file(${DOXYFILE_TEMPLATE_IN} ${DOXYFILE_OUT})

