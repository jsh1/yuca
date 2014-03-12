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

#import "MgNode.h"
#import "MgTiming.h"

@interface MgLayer : MgNode <MgTiming>

/** Geometry properties. **/

@property(nonatomic, assign) CGPoint position;
@property(nonatomic, assign) CGPoint anchor;
@property(nonatomic, assign) CGRect bounds;

@property(nonatomic, assign) CGFloat scale;
@property(nonatomic, assign) CGFloat squeeze;
@property(nonatomic, assign) CGFloat skew;
@property(nonatomic, assign) double rotation;

/** Compositing properties. **/

@property(nonatomic, assign) float alpha;
@property(nonatomic, assign) CGBlendMode blendMode;

@property(nonatomic, strong) MgLayer *mask;

/** Animations. **/

@property(nonatomic, copy) NSArray *animations;

- (void)insertAnimation:(MgAnimation *)anim atIndex:(NSInteger)idx;
- (void)removeAnimationAtIndex:(NSInteger)idx;

- (void)addAnimation:(MgAnimation *)anim;
- (void)removeAnimation:(MgAnimation *)anim;

/** Geometry methods. **/

/* The matrix that maps the layer's content into its containing
   coordinate space. */

@property(nonatomic, readonly) CGAffineTransform parentTransform;

/* Returns the new point created by mapping 'p' either into or out of
   the coordinate space containing the receiver. */

- (CGPoint)convertPointToParent:(CGPoint)p;
- (CGPoint)convertPointFromParent:(CGPoint)p;

/** Hit-testing and related. **/

/* Hit-testing. Does a depth-first search from top-to-bottom finding
   the deepest node that contains point 'p'. Point 'p' is defined in
   the coordinate space containing the receiver. */

- (MgLayer *)hitTest:(CGPoint)p;

/* Returns true if the receiver or any of its descendants contain point
   'p'. Point 'p' is defined in the coordinate space containing the
   receiver. */

- (BOOL)containsPoint:(CGPoint)p;

/** Rendering. **/

- (CFTimeInterval)renderInContext:(CGContextRef)ctx;
- (CFTimeInterval)renderInContext:(CGContextRef)ctx atTime:(CFTimeInterval)t;

/** Methods for subclasses to override. **/

- (BOOL)contentContainsPoint:(CGPoint)lp;
- (MgLayer *)hitTestContent:(CGPoint)lp;

@end
