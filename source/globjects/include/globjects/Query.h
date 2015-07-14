#pragma once

#include <chrono>

#include <globjects/binding/types.h>

#include <globjects/globjects_api.h>
#include <globjects/Object.h>

namespace globjects
{

/** \brief Encapsulates a GL Query object
    
    A Query object is used to query different aspects of the rendering 
    pipeline, such as passed samples, generated primitives, written transform
    feedback primitives or elapsed time. With begin() and end(), the scope of 
    the measurements could be specified. As a Query object queries the GPU 
    asynchroneously, the result won't be available right after the end() 
    invokation. The resultAvailable() method indicates whether the calling of
    get()/get64() will return the final result. To wait until the result is 
    available, the wait() method can be used. Alternatively there are 
    waitAndGet() and waitAndGet64() to query the result in one invokation.
    
    There is a convenience method to create a Query object which answeres with
    the current timestamp on the GPU named timestamp() (see example below).

    An example time measurement:
    \code{.cpp}

        Query * query = new Query(binding::GL_TIME_ELAPSED);
        query->begin();
    
        // more GL calls
    
        query->end();
    
        query->wait();
        binding::GLuint timeElapsed = query->get();
        // Note: sometimes it's important to use the 64 bit equivalent, because the 32 bit version can only capture time up to 4 seconds.

    \endcode
    
    An example timestamp access:
    \code{.cpp}

        // GL calls
    
        Query * query = Query::timestamp();
    
        // even more GL calls
    
        query->wait();
        binding::GLuint64 timestamp = query->get64();
        // Note: the result is the timestamp on the GPU right after the first GL calls finished and before the second calls started.

    \endcode
    
    \see http://www.opengl.org/wiki/Query_Object
    \see http://www.opengl.org/registry/specs/ARB/timer_query.txt
 */
class GLOBJECTS_API Query : public Object
{
public:
    Query();
    static Query * fromId(binding::GLuint id);

    static Query * current(binding::GLenum target);
    static Query * timestamp();
	
    static binding::GLint get(binding::GLenum target, binding::GLenum pname);
#ifdef GLOBJECTS_GL_BINDING
    static binding::GLint getIndexed(binding::GLenum target, binding::GLuint index, binding::GLenum pname);
#endif

    static binding::GLint getCounterBits(binding::GLenum target);

    virtual void accept(ObjectVisitor& visitor) override;

    void begin(binding::GLenum target) const;
    void end(binding::GLenum target) const;

#ifdef GLOBJECTS_GL_BINDING
    void beginIndexed(binding::GLenum target, binding::GLuint index) const;
    void endIndexed(binding::GLenum target, binding::GLuint index) const;
#endif
	
    static bool isQuery(binding::GLuint id);

    binding::GLuint get(binding::GLenum pname) const;
#ifdef GLOBJECTS_GL_BINDING
    binding::GLuint64 get64(binding::GLenum pname) const;
#endif
	
	bool resultAvailable() const;
    void wait() const;
    void wait(const std::chrono::duration<int, std::nano> & timeout) const;
	
    binding::GLuint waitAndGet(binding::GLenum pname) const;
    binding::GLuint waitAndGet(const std::chrono::duration<int, std::nano> & timeout, binding::GLenum pname) const;
    binding::GLuint waitAndGet(binding::GLenum pname, const std::chrono::duration<int, std::nano> & timeout) const;

#ifdef GLOBJECTS_GL_BINDING
    binding::GLuint64 waitAndGet64(binding::GLenum pname) const;
    binding::GLuint64 waitAndGet64(const std::chrono::duration<int, std::nano> & timeout, binding::GLenum pname) const;
    binding::GLuint64 waitAndGet64(binding::GLenum pname, const std::chrono::duration<int, std::nano> & timeout) const;
#endif
	
    void counter() const;

#ifdef GLOBJECTS_GL_BINDING
    virtual binding::GLenum objectType() const override;
#endif

protected:

    Query(IDResource * resource);
    virtual ~Query();

    static binding::GLuint genQuery();

    void counter(binding::GLenum target) const;
};

} // namespace globjects
