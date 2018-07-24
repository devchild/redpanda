#include <stdio.h>
#include <node.h>

#ifndef redpanda_exports_h__
#define redpanda_exports_h__

#ifdef _WIN32
#    ifdef LIBRARY_EXPORTS
#        define LIBRARY_API __declspec(dllexport)
#    else
#        define LIBRARY_API __declspec(dllimport)
#    endif
#else
#    define LIBRARY_API
#endif

#ifdef __cplusplus
extern "C" {  
	// only need to export C interface if
	// used by C++ source code
#endif

	LIBRARY_API int parser_parse(FILE* in, FILE* out);

#ifdef __cplusplus
}
#endif

#endif