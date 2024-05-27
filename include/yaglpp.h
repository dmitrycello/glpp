/*
	+---------------------------------------+
	|   YAGL++: Yet Another GC++ library    |
	+---------------------------------------+

	All information/instructions can be found here:
	https://github.com/dmitrycello/yaglpp/blob/main/README.md
*/
#pragma once

/*Define <CocoaChdirResources> pre-initialize hint*/
#define YAGLPP_COCOA_CHDIR_RESOURCES

/*Define <CocoaMenubar> pre-initialize hint*/
#define YAGLPP_COCOA_MENUBAR

/*Define <JoystickHatButtons> pre-initialize hint*/
#define YAGLPP_JOYSTICK_HAT_BUTTONS

/*Include all GLM library headers, affects the compile time*/
#define YAGLPP_GLM_HEADERS

/*Do not include main entry point into YAGL++ library*/
#define YAGLPP_NO_AFX_LAYOUT

/*Do not include FreeImage library into YAGL++ library*/
#define YAGLPP_NO_FREEIMAGE

/*Compile with the most recent GLFW nonlegacy library*/
#define YAGLPP_NO_GLFW_LEGACY

/*Define the minimum supported YAGL++ context major version value*/
#define YAGLPP_CONTEXT_VERSION_MAJOR 3

/*Define the minimum supported YAGL++ context minor version value*/
#define YAGLPP_CONTEXT_VERSION_MINOR 3

/*Define path to Static Debug build of GLFW library*/
#define YAGLPP_GLFW_DEBUG "GLFW/src/Debug/glfw3.lib"

/*Define path to Static Release build of GLFW library*/
#define YAGLPP_GLFW_RELEASE "GLFW/src/Release/glfw3.lib"

/*Define YAGL++ library debug output path*/
#define YAGLPP_LIB_DEBUG "Debug/yaglpp.lib"

/*Define YAGL++ library release output path*/
#define YAGLPP_LIB_RELEASE "yaglpp.lib"

/* END OF ADJUSTABLE SWITCHES */
#include <windows.h>
#include <iostream>
#include <glm/fwd.hpp>
#ifdef __cplusplus
namespace glm {
/*Two-component char vector type defined by YAGL++*/
typedef tvec2<char> cvec2;

/*Two-component unsigned char vector type defined by YAGL++*/
typedef tvec2<unsigned char> ucvec2;

/*Two-component short vector type defined by YAGL++*/
typedef tvec2<short> svec2;

/*Two-component unsigned short vector type defined by YAGL++*/
typedef tvec2<unsigned short> usvec2;

/*Three-component char vector type defined by YAGL++*/
typedef tvec3<char> cvec3;

/*Three-component unsigned char vector type defined by YAGL++*/
typedef tvec3<unsigned char> ucvec3;

/*Three-component short vector type defined by YAGL++*/
typedef tvec3<short> svec3;

/*Three-component unsigned short vector type defined by YAGL++*/
typedef tvec3<unsigned short> usvec3;

/*Four-component char vector type defined by YAGL++*/
typedef tvec4<char> cvec4;

/*Four-component unsigned char vector type defined by YAGL++*/
typedef tvec4<unsigned char> ucvec4;

/*Four-component short vector type defined by YAGL++*/
typedef tvec4<short> svec4;

/*Four-component unsigned short vector type defined by YAGL++*/
typedef tvec4<unsigned short> usvec4;
} // namespace glm

/*YAGL++ helper function, checks if the file with given path exists using <stat> structure
@param [in] The requested file with given path
@return True if file exists, false otherwise*/
bool fileExists(_In_z_ const char* file);

/*YAGL++ helper function, deallocates the pointer previously allocated by the library
@param [in] The pointer to freed memory block*/
void freeMemory(_In_ void* block);

class DataStore;
class StbImage;
typedef struct StbCallbacks;
enum class StbFormat : int;

#ifndef YAGLPP_NO_FREEIMAGE
class FreeImage;
#endif // #ifndef YAGLPP_NO_FREEIMAGE

#ifdef YAGLPP_BUILD_LIB
/*YAGL++ memory deallocation macro*/
#define YAGLPP_FREE(p) free(p)

#ifdef _DEBUG
#define YAGLPP_GLFW_LIB YAGLPP_GLFW_DEBUG
_Ret_notnull_ void* _assertCalloc(size_t);
_Ret_notnull_ void* _assertMalloc(size_t);
_Ret_notnull_ void* _assertRealloc(void*, size_t);

/*YAGL++ assertion macro, does nothing in Release mode*/
#define YAGLPP_ASSERT(e) assert(e)

/*YAGL++ Debug only statement macro, does nothing in Release mode*/
#define YAGLPP_DEBUG(s) s

/*YAGL++ zeroed memory allocation macro, does no assertion in Release mode*/
#define YAGLPP_CALLOC(s) _assertCalloc(s)

/*YAGL++ raw memory allocation macro, does no assertion in Release mode*/
#define YAGLPP_MALLOC(s) _assertMalloc(s)

/*YAGL++ memory reallocation macro, does no assertion in Release mode*/
#define YAGLPP_REALLOC(p, s) _assertRealloc(p, s)

#else // #ifdef _DEBUG
#define YAGLPP_GLFW_LIB YAGLPP_GLFW_RELEASE
#define YAGLPP_ASSERT(e)
#define YAGLPP_DEBUG(s)
#define YAGLPP_CALLOC(s) calloc(s, 1)
#define YAGLPP_MALLOC(s) malloc(s)
#define YAGLPP_REALLOC(p, s) realloc(p, s)
#endif // #ifdef _DEBUG

#else // #ifdef YAGLPP_BUILD_LIB
#include "DataStore.h"
#include "FreeImage.h"
#include "StbImage.h"
#include "gladpp.h"
#include "glfw3pp.h"

#ifdef YAGLPP_GLM_HEADERS
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#endif // #ifdef YAGLPP_GLM_HEADERS

#ifdef _DEBUG
#pragma comment(lib, YAGLPP_LIB_DEBUG)
#else // #ifdef _DEBUG
#pragma comment(lib, YAGLPP_LIB_RELEASE)
#endif // #ifdef _DEBUG
#endif // #ifndef YAGLPP_BUILD_LIB

#else // #ifdef __cplusplus
#error YAGL++ requires C++ compiler
#endif // #ifdef __cplusplus
