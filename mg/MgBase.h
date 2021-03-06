/* -*- c-style: gnu -*-

   Copyright (c) 2014 John Harper <jsh@unfactored.org>

   Permission is hereby granted, free of charge, to any person
   obtaining a copy of this software and associated documentation files
   (the "Software"), to deal in the Software without restriction,
   including without limitation the rights to use, copy, modify, merge,
   publish, distribute, sublicense, and/or sell copies of the Software,
   and to permit persons to whom the Software is furnished to do so,
   subject to the following conditions:

   The above copyright notice and this permission notice shall be
   included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
   NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
   BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
   ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
   CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE. */

#ifndef MG_BASE_H
#define MG_BASE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <float.h>

#include <CoreFoundation/CoreFoundation.h>
#include <CoreGraphics/CoreGraphics.h>
#ifdef __OBJC__
# include <Foundation/NSObject.h>
#endif

#ifdef __cplusplus
# define MG_EXTERN_C_BEGIN extern "C" {
# define MG_EXTERN_C_END   }
#else
# define MG_EXTERN_C_BEGIN
# define MG_EXTERN_C_END
#endif

#ifdef __GNUC__
# define MG_GNUC(major, minor) \
  (__GNUC__ > (major) || (__GNUC__ == (major) && __GNUC_MINOR__ >= (minor)))
#else
# define MG_GNUC(major, minor) 0
#endif

#ifndef MG_EXTERN
# define MG_EXTERN extern
#endif

#ifndef MG_INLINE
# if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#  define MG_INLINE static inline
# else
#  define MG_INLINE static    
# endif
#endif

#ifndef MG_HIDDEN
# if MG_GNUC (4,0)
#  define MG_HIDDEN __attribute__ ((visibility ("hidden")))
# else
#  define MG_HIDDEN /* no hidden */
# endif
#endif

#ifdef __OBJC__

# ifndef MG_HIDDEN_CLASS
#  define MG_HIDDEN_CLASS MG_HIDDEN
# endif

@class NSArray, NSMutableArray, NSData, NSMutableData, NSDictionary,
    NSMutableDictionary, NSMapTable, NSSet, NSMutableSet, NSIndexSet,
    NSMutableIndexSet, NSPointerArray, NSURL;
@class MgActiveTransition, MgBezierTimingFunction, MgDrawingLayer,
    MgFunction, MgGradientLayer, MgGradientLayerState, MgGroupLayer,
    MgGroupLayerState, MgImageLayer, MgImageLayerState, MgImageProvider,
    MgLayer, MgLayerState, MgModuleLayer, MgModuleState, MgNode,
    MgNodeState, MgNodeTransition, MgPathLayer, MgPathLayerState,
    MgRectLayer, MgRectLayerState, MgSpringFunction, MgTimingFunction,
    MgTransitionTiming, MgViewContext;
@class CALayer;

@protocol MgDrawingState, MgImageProvider;

/* Graph copying scheme, i.e. to avoid copying each object more
   than once.

   -graphCopy: should be implemented by classes as an unconditional
   copy, but calling -mg_graphCopy: for sub-objects.

   -mg_graphCopy is the convenience entry-point to call for the
   top-level object, i.e. it allocates a table, calls -mg_graphCopy:
   and returns the result.

   -mg_graphCopy: dereferences the table to test if each copied object
   has already been duplicated, if not a copy is made and inserted into
   the table.

   -mg_conditionalGraphCopy: is similar, but doesn't copy the object
   if it's not already been copied and inserted into the table, in
   which case it returns the original object. */

@interface NSObject (MgGraphCopying)
- (id)mg_graphCopy;
- (id)mg_graphCopy:(NSMapTable *)map;
- (id)mg_conditionalGraphCopy:(NSMapTable *)map;
@end

@protocol MgGraphCopying
- (id)graphCopy:(NSMapTable *)map;
@end

#endif /* __OBJC__ */
#endif /* MG_BASE_H */
