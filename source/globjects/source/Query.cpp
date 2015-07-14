#include <globjects/Query.h>

#include <globjects/binding/functions.h>
#include <globjects/binding/boolean.h>
#include <globjects/binding/enum.h>

#include <globjects/ObjectVisitor.h>

#include "Resource.h"


namespace globjects
{

using namespace binding;

Query::Query()
: Object(new QueryResource)
{
}

Query::Query(IDResource * resource)
: Object(resource)
{
}

Query * Query::fromId(const GLuint id)
{
    return new Query(new ExternalResource(id));
}

Query::~Query()
{
}

Query * Query::current(const GLenum target)
{
    GLint id = get(target, GL_CURRENT_QUERY);

    if (id <= 0)
    {
        return nullptr;
    }
	
    // TODO: fetch correct query from object registry
    return Query::fromId(id);
}

Query * Query::timestamp()
{
    Query * query = new Query();
#ifdef GLOBJECTS_GL_BINDING
    query->counter(GL_TIMESTAMP);
#else
    query->counter(GL_TIMESTAMP_EXT);
#endif

    return query;
}

int Query::getCounterBits(const GLenum target)
{
#ifdef GLOBJECTS_GL_BINDING
    return get(target, GL_QUERY_COUNTER_BITS);
#else
    return get(target, GL_QUERY_COUNTER_BITS_EXT);
#endif
}

GLuint Query::genQuery()
{
	GLuint id;

    glGenQueries(1, &id);

	return id;
}

GLint Query::get(const GLenum target, const GLenum pname)
{
    GLint value = 0;

    glGetQueryiv(target, pname, &value);

    return value;
}

#ifdef GLOBJECTS_GL_BINDING
GLint Query::getIndexed(const GLenum target, const GLuint index, const GLenum pname)
{
    GLint value = 0;

    glGetQueryIndexediv(target, index, pname, &value);

    return value;
}
#endif

void Query::accept(ObjectVisitor& visitor)
{
	visitor.visitQuery(this);
}

void Query::begin(const GLenum target) const
{
    glBeginQuery(target, id());
}

void Query::end(const GLenum target) const
{
    glEndQuery(target);
}

#ifdef GLOBJECTS_GL_BINDING
void Query::beginIndexed(const GLenum target, const GLuint index) const
{
    glBeginQueryIndexed(target, index, id());
}

void Query::endIndexed(const GLenum target, const GLuint index) const
{
    glEndQueryIndexed(target, index);
}
#endif

GLuint Query::get(const GLenum pname) const
{
    GLuint value = 0;
	
    glGetQueryObjectuiv(id(), pname, &value);
	
	return value;
}

#ifdef GLOBJECTS_GL_BINDING
GLuint64 Query::get64(const GLenum pname) const
{
    GLuint64 value = 0;
	
    glGetQueryObjectui64v(id(), pname, &value);
	
	return value;
}
#endif

bool Query::resultAvailable() const
{
    return static_cast<GLboolean>(get(GL_QUERY_RESULT_AVAILABLE)) == GL_TRUE;
}

void Query::wait() const
{
    while (!resultAvailable());
}

void Query::wait(const std::chrono::duration<int, std::nano> & timeout) const
{
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

    std::chrono::high_resolution_clock::time_point current;
    while (!resultAvailable() && start + timeout > current)
    {
        current = std::chrono::high_resolution_clock::now();
    }
}

GLuint Query::waitAndGet(const GLenum pname) const
{
    wait();
	
	return get(pname);
}

#ifdef GLOBJECTS_GL_BINDING
GLuint64 Query::waitAndGet64(const GLenum pname) const
{
    wait();
	
    return get64(pname);
}
#endif

GLuint Query::waitAndGet(const std::chrono::duration<int, std::nano> & timeout, const GLenum pname) const
{
    return waitAndGet(pname, timeout);
}

#ifdef GLOBJECTS_GL_BINDING
GLuint64 Query::waitAndGet64(const std::chrono::duration<int, std::nano> & timeout, const GLenum pname) const
{
    return waitAndGet64(pname, timeout);
}
#endif

GLuint Query::waitAndGet(const GLenum pname, const std::chrono::duration<int, std::nano> & timeout) const
{
    wait(timeout);

    return get(pname);
}

#ifdef GLOBJECTS_GL_BINDING
GLuint64 Query::waitAndGet64(const GLenum pname, const std::chrono::duration<int, std::nano> & timeout) const
{
    wait(timeout);

    return get64(pname);
}
#endif

void Query::counter() const
{
#ifdef GLOBJECTS_GL_BINDING
    counter(GL_TIMESTAMP);
#else
    counter(GL_TIMESTAMP_EXT);
#endif
}

void Query::counter(const GLenum target) const
{
#ifdef GLOBJECTS_GL_BINDING
    glQueryCounter(id(), target);
#else
    glQueryCounterEXT(id(), target);
#endif
}

bool Query::isQuery(const GLuint id)
{
    return glIsQuery(id) == GL_TRUE;
}

#ifdef GLOBJECTS_GL_BINDING
GLenum Query::objectType() const
{
    return GL_QUERY;
}
#endif

} // namespace globjects
