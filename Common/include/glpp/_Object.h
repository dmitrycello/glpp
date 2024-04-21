#pragma once
#include "gladpp.h"
namespace gl {
/*GLAD pointer to <glDelete..> functions*/
typedef void (WINAPI GLPP_GLAD_PFNDELETE)(GLsizei n, const GLuint* ids);

/*GLAD pointer to <glGen..> functions*/
typedef void (WINAPI GLPP_GLAD_PFNGEN)(GLsizei n, GLuint* ids);

/*OpenGL multi-object abstract root class*/
class _Objects
{
private:
	friend class _Object;
	typedef struct {
		GLuint num;		// Object number
#pragma warning(push)
#pragma warning(disable : 4200)
		GLuint ids[0];	// Zero data array
#pragma warning(pop)
	} _DATA, *_LPDATA;
	_LPDATA m_lpData;	// Class data

#ifdef _DEBUG
	GLuint _objects_assign(GLuint index, GLenum target);
#else // #ifdef _DEBUG
	GLuint _objects_assign(GLuint index);
#endif // #ifdef _DEBUG

protected:
	_Objects()
	{
		m_lpData = nullptr;
	}

	void _objects_append(GLPP_GLAD_PFNGEN pfnGen, GLuint num);
	void _objects_delete(GLPP_GLAD_PFNDELETE pfnDelete);
	void _objects_gen(GLPP_GLAD_PFNGEN pfnGen, GLuint num);

public:
	/*Returns the number of allocated OpenGL names in the multi-object
	@return The number of elements in the multi-object*/
	GLuint getObjectNum();

	/*Checks if valid OpenGL multi-object
	@return True if not an empty OpenGL multi-object, false otherwise*/
	GLboolean isObject()
	{
		return m_lpData != nullptr;
	}
}; // class _Objects

#ifndef _DEBUG
inline GLuint _Objects::_objects_assign(GLuint index)
{
	return m_lpData->ids[index];
}

inline GLuint _Objects::getObjectNum()
{
	return m_lpData->num;
}
#endif // #ifndef _DEBUG
} // namespace gl

#ifndef GLPP_BUILD_LIB
#include "Queries.h"
#include "Buffers.h"
#include "Textures.h"
#include "Framebuffers.h"
#include "Renderbuffers.h"
#include "Samplers.h"
#include "VertexArrays.h"
#endif // #ifdef GLPP_BUILD

namespace gl {
/*OpenGL object abstract root class*/
class _Object
{
private:
	GLint m_iId;

protected:
	_Object()
	{
		m_iId = 0;
	}

	void _object_delete(GLPP_GLAD_PFNDELETE pfnDelete);
	void _object_gen(GLPP_GLAD_PFNGEN pfnGen);
	GLuint _object_id(GLPP_GLAD_PFNGEN pfnGen);

#ifdef _DEBUG
	void _object_assign(_Objects& objects, GLuint index, GLenum target);
#else // #ifdef _DEBUG
	void _object_assign(_Objects& objects, GLuint index);
#endif // #ifdef _DEBUG

public:
	/*Checks if the OpenGL object name was generated
	@return True if generated OpenGL object, false otherwise*/
	GLboolean isObject()
	{
		return m_iId != 0;
	}

	/*Checks if the OpenGL object is single, or a part of multi-object
	@return True if single OpenGL object, false if a part of multi-object*/
	GLboolean isSingle()
	{
		return m_iId < 0;
	}
}; // class _Object

#ifndef _DEBUG
inline void _Object::_object_assign(_Objects& objects, GLuint index)
{
	m_iId = objects._objects_assign(index);
}
#endif // #ifndef _DEBUG
} // namespace gl

#ifndef GLPP_BUILD_LIB
#include "_Query.h"
#include "_Buffer.h"
#include "_Texture.h"
#include "_Framebuffer.h"
#include "Sampler.h"
#include "Renderbuffer.h"
#include "VertexArray.h"
#endif // #ifdef GLPP_BUILD