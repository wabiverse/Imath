//
// SPDX-License-Identifier: BSD-3-Clause
// Copyright Contributors to the OpenEXR Project.
//

//
// Convenience functions that call GL with Imath types
//

#ifndef INCLUDED_IMATHGL_H
#define INCLUDED_IMATHGL_H

#if defined(__APPLE__)
#    include <TargetConditionals.h>
#    if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
#        if !defined(IMATH_HAS_OPENGL)
#            define IMATH_HAS_OPENGL 0
#        endif /* !defined(IMATH_HAS_OPENGL) */
#        include <OpenGLES/ES1/gl.h>
#    else /* !TARGET_OS_IPHONE && !TARGET_IPHONE_SIMULATOR */
#        if !defined(IMATH_HAS_OPENGL)
#            define IMATH_HAS_OPENGL 1
#        endif /* !defined(IMATH_HAS_OPENGL) */
#        include <OpenGL/gl.h>
#    endif /* TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR */
#else
#    if !defined(IMATH_HAS_OPENGL)
#        define IMATH_HAS_OPENGL 1
#    endif /* !defined(IMATH_HAS_OPENGL) */
#    if defined(_WIN32)
#        define WIN32_LEAN_AND_MEAN
#        include <windows.h>
#        if !defined(GL_GLEXT_PROTOTYPES)
#            define GL_GLEXT_PROTOTYPES
#        endif // !defined(GL_GLEXT_PROTOTYPES)
#    endif // defined(_WIN32)
#    include <GL/gl.h>
#    if defined(_WIN32)
#        if !defined(GL_TEXTURE0)
#            define GL_TEXTURE0 0x84C0
#        endif // !defined(GL_TEXTURE0)
#        if !defined(GL_TEXTURE1)
#            define GL_TEXTURE1 0x84C1
#        endif // !defined(GL_TEXTURE1)
#        if !defined(glActiveTexure)
#            ifdef __cplusplus
             extern "C" {
#            endif // __cplusplus

             __declspec(dllimport) void __stdcall glActiveTexture (GLenum texture);

#            ifdef __cplusplus
             }
#            endif // __cplusplus
#        endif // !defined(glActiveTexure)
#    endif // defined(_WIN32)
#endif

#include "ImathFun.h"
#include "ImathMatrix.h"
#include "ImathNamespace.h"
#include "ImathVec.h"

/// Call glVertex3f
inline void
glVertex (const IMATH_INTERNAL_NAMESPACE::V3f& v)
{
#if IMATH_HAS_OPENGL
    glVertex3f (v.x, v.y, v.z);
#endif /* IMATH_HAS_OPENGL */
}

/// Call glVertex2f
inline void
glVertex (const IMATH_INTERNAL_NAMESPACE::V2f& v)
{
#if IMATH_HAS_OPENGL
    glVertex2f (v.x, v.y);
#endif /* IMATH_HAS_OPENGL */
}

/// Call glNormal3f
inline void
glNormal (const IMATH_INTERNAL_NAMESPACE::V3f& n)
{
#if IMATH_HAS_OPENGL
    glNormal3f (n.x, n.y, n.z);
#endif /* IMATH_HAS_OPENGL */
}

/// Call glColor3f
inline void
glColor (const IMATH_INTERNAL_NAMESPACE::V3f& c)
{
#if IMATH_HAS_OPENGL
    glColor3f (c.x, c.y, c.z);
#endif /* IMATH_HAS_OPENGL */
}

/// Call glTranslatef
inline void
glTranslate (const IMATH_INTERNAL_NAMESPACE::V3f& t)
{
#if IMATH_HAS_OPENGL
    glTranslatef (t.x, t.y, t.z);
#endif /* IMATH_HAS_OPENGL */
}

/// Call glTexCoord2f
inline void
glTexCoord (const IMATH_INTERNAL_NAMESPACE::V2f& t)
{
#if IMATH_HAS_OPENGL
    glTexCoord2f (t.x, t.y);
#endif /* IMATH_HAS_OPENGL */
}

/// Disable GL textures
inline void
glDisableTexture ()
{
#if IMATH_HAS_OPENGL
    glActiveTexture (GL_TEXTURE1);
    glBindTexture (GL_TEXTURE_2D, 0);
    glDisable (GL_TEXTURE_2D);

    glActiveTexture (GL_TEXTURE0);
#endif /* IMATH_HAS_OPENGL */
}

namespace
{

const float GL_FLOAT_MAX = 1.8e+19; // sqrt (FLT_MAX)

inline bool
badFloat (float f)
{
    return !IMATH_INTERNAL_NAMESPACE::finitef (f) || f < -GL_FLOAT_MAX ||
           f > GL_FLOAT_MAX;
}

} // namespace

/// Throw an exception if m is not a valid matrix for GL
inline void
throwBadMatrix (const IMATH_INTERNAL_NAMESPACE::M44f& m)
{
    if (badFloat (m[0][0]) || badFloat (m[0][1]) || badFloat (m[0][2]) ||
        badFloat (m[0][3]) || badFloat (m[1][0]) || badFloat (m[1][1]) ||
        badFloat (m[1][2]) || badFloat (m[1][3]) || badFloat (m[2][0]) ||
        badFloat (m[2][1]) || badFloat (m[2][2]) || badFloat (m[2][3]) ||
        badFloat (m[3][0]) || badFloat (m[3][1]) || badFloat (m[3][2]) ||
        badFloat (m[3][3]))
        throw std::invalid_argument ("GL matrix overflow");
}

/// Call glMultmatrixf. Throw an exception if m is not a valid matrix for GL.
inline void
glMultMatrix (const IMATH_INTERNAL_NAMESPACE::M44f& m)
{
#if IMATH_HAS_OPENGL
    throwBadMatrix (m);
    glMultMatrixf ((GLfloat*) m[0]);
#endif /* IMATH_HAS_OPENGL */
}

/// Call glMultmatrixf. Throw an exception if m is not a valid matrix for GL.
inline void
glMultMatrix (const IMATH_INTERNAL_NAMESPACE::M44f* m)
{
#if IMATH_HAS_OPENGL
    throwBadMatrix (*m);
    glMultMatrixf ((GLfloat*) (*m)[0]);
#endif /* IMATH_HAS_OPENGL */
}

/// Call glLoadmatrixf. Throw an exception if m is not a valid matrix for GL.
inline void
glLoadMatrix (const IMATH_INTERNAL_NAMESPACE::M44f& m)
{
#if IMATH_HAS_OPENGL
    throwBadMatrix (m);
    glLoadMatrixf ((GLfloat*) m[0]);
#endif /* IMATH_HAS_OPENGL */
}

/// Call glLoadmatrixf. Throw an exception if m is not a valid matrix for GL.
inline void
glLoadMatrix (const IMATH_INTERNAL_NAMESPACE::M44f* m)
{
#if IMATH_HAS_OPENGL
    throwBadMatrix (*m);
    glLoadMatrixf ((GLfloat*) (*m)[0]);
#endif /* IMATH_HAS_OPENGL */
}

IMATH_INTERNAL_NAMESPACE_HEADER_ENTER

///
/// A class object that pushes/pops the GL matrix. This object assists with
/// proper cleanup of the state when exceptions are thrown.
///

class GLPushMatrix
{
public:
    GLPushMatrix ()
    {
#if IMATH_HAS_OPENGL
        glPushMatrix ();
#endif /* IMATH_HAS_OPENGL */
    }

    ~GLPushMatrix ()
    {
#if IMATH_HAS_OPENGL
        glPopMatrix ();
#endif /* IMATH_HAS_OPENGL */
    }
};

///
/// A class object that pushes/pops the current GL attribute state. This object assists with
/// proper cleanup of the state when exceptions are thrown.
///

class GLPushAttrib
{
public:
    /// call glPushAttrib()
    GLPushAttrib (GLbitfield mask)
    {
#if IMATH_HAS_OPENGL
        glPushAttrib (mask);
#endif /* IMATH_HAS_OPENGL */
    }

    /// call glPopAttrib()
    ~GLPushAttrib ()
    {
#if IMATH_HAS_OPENGL
        glPopAttrib ();
#endif /* IMATH_HAS_OPENGL */
    }
};

///
/// A class object that wraps glBegin/glEnd. The constructor calls
/// glBegin(). The destructor calls glEnd().
///

class GLBegin
{
public:
    /// Call glBegin()
    GLBegin (GLenum mode)
    {
#if IMATH_HAS_OPENGL
        glBegin (mode);
#endif /* IMATH_HAS_OPENGL */
    }

    /// Call glEnd()
    ~GLBegin ()
    {
#if IMATH_HAS_OPENGL
        glEnd ();
#endif /* IMATH_HAS_OPENGL */
    }
};

IMATH_INTERNAL_NAMESPACE_HEADER_EXIT

#endif
