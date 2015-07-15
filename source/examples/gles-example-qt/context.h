#pragma once

using EGLWindow = unsigned long;

void createGLContext(EGLWindow window);
void createGLESContext(EGLWindow window);

void makeCurrent();
void doneCurrent();

void swapBuffers();

void releaseContext();
