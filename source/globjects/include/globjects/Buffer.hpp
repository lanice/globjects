#pragma once

#include <globjects/Buffer.h>

namespace globjects {

template <typename T>
void Buffer::setData(const std::vector<T> & data, binding::GLenum usage)
{
    setData(static_cast<binding::GLsizeiptr>(data.size() * sizeof(T)), data.data(), usage);
}

template <typename T, std::size_t Count>
void Buffer::setData(const std::array<T, Count> & data, binding::GLenum usage)
{
    setData(static_cast<binding::GLsizeiptr>(Count * sizeof(T)), data.data(), usage);
}

template <typename T>
void Buffer::setSubData(const std::vector<T> & data, binding::GLintptr offset)
{
    setSubData(offset, static_cast<binding::GLsizei>(data.size() * sizeof(T)), data.data());
}

template <typename T, std::size_t Count>
void Buffer::setSubData(const std::array<T, Count> & data, binding::GLintptr offset)
{
    setSubData(offset, static_cast<binding::GLsizei>(Count * sizeof(T)), data.data());
}

template <typename T>
void Buffer::setStorage(const std::vector<T> & data, binding::BufferStorageMask flags)
{
    setStorage(static_cast<binding::GLsizei>(data.size() * sizeof(T)), data.data(), flags);
}

template <typename T, std::size_t Count>
void Buffer::setStorage(const std::array<T, Count> & data, binding::BufferStorageMask flags)
{
    setStorage(static_cast<binding::GLsizei>(Count * sizeof(T)), data.data(), flags);
}

template <typename T>
const std::vector<T> Buffer::getSubData(binding::GLsizeiptr size, binding::GLintptr offset) const
{
    std::vector<T> data(size);

    getSubData(offset, size, data.data());

    return data;
}

template <typename T, std::size_t Count>
const std::array<T, Count> Buffer::getSubData(binding::GLintptr offset) const
{
    std::array<T, Count> data;

    getSubData(offset, static_cast<binding::GLsizeiptr>(Count * sizeof(T)), data.data());

    return data;
}

} // namespace globjects
