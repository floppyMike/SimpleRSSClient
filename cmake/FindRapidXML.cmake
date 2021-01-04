set(RAPIDXML_ROOT "rapidxml/include")

find_path(RAPIDXML_INCLUDE_DIR
		NAMES
    	rapidxml.hpp
        HINTS
        ENV RAPIDXML
		PATHS
		/usr/include
		/usr/include/${RAPIDXML_ROOT}
		
		/usr/local/include
    	/usr/local/include/${RAPIDXML_ROOT}
)

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(
	RAPIDXML
	DEFAULT_MSG
	RAPIDXML_INCLUDE_DIR
)

mark_as_advanced(RAPIDXML_INCLUDE_DIR)