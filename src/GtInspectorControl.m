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

#import "GtInspectorControl.h"

#import "GtInspectorBoolControl.h"
#import "GtInspectorColorControl.h"
#import "GtInspectorEnumControl.h"
#import "GtInspectorItem.h"
#import "GtInspectorNumberControl.h"
#import "GtInspectorStringControl.h"
#import "GtInspectorViewController.h"

@implementation GtInspectorControl
{
  GtInspectorItem *_item;
  __weak GtInspectorViewController *_controller;
}

static Class
controlClass(GtInspectorItem *item)
{
  static NSDictionary *dict;

  if (dict == nil)
    {
      dict = @{
	@"bool": [GtInspectorBoolControl class],
	@"float": [GtInspectorNumberControl class],
	@"double": [GtInspectorNumberControl class],
	@"CGFloat": [GtInspectorNumberControl class],
	@"string": [GtInspectorStringControl class],
	@"enum": [GtInspectorEnumControl class],
	@"CGColor": [GtInspectorColorControl class],
      };
    }

  return dict[item.type];
}

+ (instancetype)controlForItem:(GtInspectorItem *)item
    controller:(GtInspectorViewController *)controller
{
  Class cls = controlClass(item);

  if (cls != nil)
    return [cls controlForItem:item controller:controller];
  else
    return nil;
}

+ (CGFloat)controlHeightForItem:(GtInspectorItem *)item
{
  Class cls = controlClass(item);

  if (cls != nil)
    return [cls controlHeightForItem:item];
  else
    return 0;
}

+ (CGFloat)controlWidth
{
  return 50;
}

- (id)initWithItem:(GtInspectorItem *)item
    controller:(GtInspectorViewController *)controller
{
  self = [super initWithFrame:NSZeroRect];
  if (self == nil)
    return nil;

  _item = item;
  _controller = controller;

  return self;
}

- (id)objectValue
{
  return nil;
}

- (void)setObjectValue:(id)obj
{
}

- (void)layoutSubviews
{
}

- (void)setFrame:(NSRect)r
{
  [super setFrame:r];

  [self layoutSubviews];
}

- (IBAction)takeValue:(id)sender
{
  [_controller setInspectedValue:self.objectValue forKey:self.item.key];
}

@end
