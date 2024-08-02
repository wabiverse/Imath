//
// SPDX-License-Identifier: BSD-3-Clause
// Copyright Contributors to the OpenEXR Project.
//

//
// Convenience functions that call GLU with Imath types
//

#ifndef INCLUDED_IMATHGLU_H
#define INCLUDED_IMATHGLU_H

#if defined(__APPLE__)
#    include <TargetConditionals.h>
#    if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
#        if !defined(IMATH_HAS_OPENGL)
#            define IMATH_HAS_OPENGL 0
#        endif /* !defined(IMATH_HAS_OPENGL) */
#    else      /* !TARGET_OS_IPHONE && !TARGET_IPHONE_SIMULATOR */
#        if !defined(IMATH_HAS_OPENGL)
#            define IMATH_HAS_OPENGL 1
#        endif /* !defined(IMATH_HAS_OPENGL) */
#        include <OpenGL/gl.h>
#        include <OpenGL/glu.h>
#    endif /* TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR */
#else      /* !defined(__APPLE__) */
#    if !defined(IMATH_HAS_OPENGL)
#        define IMATH_HAS_OPENGL 1
#    endif /* !defined(IMATH_HAS_OPENGL) */
#    if defined(_WIN32)
        #define WIN32_LEAN_AND_MEAN
        #include <windows.h>
        #if !defined(GL_GLEXT_PROTOTYPES)
        #    define GL_GLEXT_PROTOTYPES
        #endif // !defined(GL_GLEXT_PROTOTYPES)
#    endif // defined(_WIN32)
#    include <GL/gl.h>
#    include <GL/glu.h>
#    if defined(_WIN32)
#        if !defined(GL_TEXTURE0)
#            define GL_TEXTURE0 0x84C0
#        endif // !defined(GL_TEXTURE0)
#        if !defined(GL_TEXTURE1)
#            define GL_TEXTURE1 0x84C1
#        endif // !defined(GL_TEXTURE1)
#    endif // defined(_WIN32)
#endif /* defined(__APPLE__) */

#include "ImathVec.h"

/// Call gluLookAt with the given position, interest, and up-vector.
inline void
gluLookAt (
    const IMATH_INTERNAL_NAMESPACE::V3f& pos,
    const IMATH_INTERNAL_NAMESPACE::V3f& interest,
    const IMATH_INTERNAL_NAMESPACE::V3f& up)
{
#if IMATH_HAS_OPENGL
    gluLookAt (
        pos.x,
        pos.y,
        pos.z,
        interest.x,
        interest.y,
        interest.z,
        up.x,
        up.y,
        up.z);
#endif /* IMATH_HAS_OPENGL */
}

#endif
