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

#import "MgBase.h"

MG_EXTERN_C_BEGIN

MG_EXTERN CGColorRef MgBlackColor(void);
MG_EXTERN CGColorRef MgWhiteColor(void);

MG_EXTERN CGColorRef MgCreateSRGBColor(CGFloat r, CGFloat g, CGFloat b,
    CGFloat a) CF_RETURNS_RETAINED;

MG_EXTERN CGColorSpaceRef MgSRGBColorSpace(void);

MG_EXTERN void MgContextSetLineDash(CGContextRef ctx, CFArrayRef pattern,
    CGFloat phase);

MG_EXTERN CGGradientRef MgCreateGradient(CFArrayRef colors,
    CFArrayRef locations) CF_RETURNS_RETAINED;

MG_EXTERN bool MgAffineTransformIsRectilinear(const CGAffineTransform *m);

MG_EXTERN void MgRectGetCorners(CGRect r, CGPoint p[4]);

MG_EXTERN CGPathRef MgPathCreateWithRoundRect(CGRect rect, CGFloat radius)
    CF_RETURNS_RETAINED;

MG_EXTERN CGImageRef MgImageCreateByDrawing(size_t w, size_t, bool opaque,
    void (^block)(CGContextRef ctx)) CF_RETURNS_RETAINED;

MG_EXTERN_C_END