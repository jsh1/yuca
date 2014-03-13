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

#import "MgDrawingLayer.h"

#import "MgLayerInternal.h"
#import "MgNodeInternal.h"

@implementation MgDrawingLayer
{
  MgLayerRenderState *_rs;
}

- (void)setNeedsDisplay
{
  [self incrementVersion];
}

- (void)drawWithState:(id<MgDrawingState>)obj
{
}

- (void)clipWithState:(id<MgDrawingState>)obj
{
}

- (void)_renderLayerWithState:(MgLayerRenderState *)rs
{
  _rs = rs;

  CGContextSaveGState(rs->ctx);

  [self drawWithState:(id)self];

  CGContextRestoreGState(rs->ctx);

  _rs = NULL;
}

- (void)_renderLayerMaskWithState:(MgLayerRenderState *)rs
{
  _rs = rs;

  float alpha = rs->alpha * self.alpha;

  if (alpha != 1)
    {
      [super _renderLayerMaskWithState:rs];
      return;
    }

  /* Can't save/restore gstate, need clip changes. */

  [self clipWithState:(id)self];

  _rs = NULL;
}

/** MgDrawingState methods. **/

- (CGContextRef)context
{
  return _rs != NULL ? _rs->ctx : NULL;
}

- (CFTimeInterval)currentTime
{
  return _rs != NULL ? _rs->t : 0;
}

- (CFTimeInterval)nextTime
{
  return _rs != NULL ? _rs->tnext : 0;
}

- (void)setNextTime:(CFTimeInterval)t
{
  if (_rs != NULL && t < _rs->tnext)
    _rs->tnext = t;
}

@end