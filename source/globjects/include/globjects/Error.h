#pragma once

#include <string>

#include <globjects/binding/types.h>

#include <globjects/globjects_api.h>

namespace globjects
{

/** \brief Wrapper for OpenGL errors.
 
    To access the current Error (which can be none), call get().
    To discard any current error, call clear().
 */
class GLOBJECTS_API Error
{
public:
	Error();
	Error(binding::GLenum errorCode);

    static Error get();

	static void clear();

	binding::GLenum code() const;
	std::string name() const;

	bool isError() const;
    operator bool() const;

protected:
	binding::GLenum m_errorCode;
};

} // namespace globjects
