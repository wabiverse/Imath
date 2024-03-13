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
#    include <GL/gl.h>
#    include <GL/glu.h>
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
