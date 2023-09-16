#pragma once

#include "dobjective/class.h"
#include "dobjective/vtable.h"

CLASS_DECLARE(Shape);
CLASS_VTABLE_DECLARE(Shape);
CLASS_CREATE_VTABLE_DECLARE(Shape, Shape);
CLASS_IMPL(Shape, {
  ENABLE_VTABLE(Shape);
  int x;
  int y;
  int width;
  int height;
});
CLASS_VTABLE_IMPL(Shape, {
  CLASS_VTABLE_METHOD_DECLARE(Shape, void, draw);
  CLASS_VTABLE_METHOD_WITH_ARGS_DECLARE(Shape, void, move, int, int);
});
CLASS_METHOD_DECLARE(Shape, void, draw);
CLASS_METHOD_WITH_ARGS_DECLARE(Shape, void, move, int, int);
CLASS_CTOR_WITH_ARGS_DECLARE(Shape, int, int, int, int);
CLASS_DTOR_DECLARE(Shape);
CLASS_AUTO_CLEANUP_DTOR_DECLARE(Shape);


CLASS_DECLARE(Rectangle);
CLASS_CREATE_VTABLE_DECLARE(Shape, Rectangle);
CLASS_IMPL(Rectangle, {
  DERIVE_DECLARE(Shape);
});
CLASS_METHOD_DECLARE(Rectangle, void, draw);
CLASS_METHOD_WITH_ARGS_DECLARE(Rectangle, void, move, int, int);
CLASS_CTOR_DECLARE(Rectangle);
CLASS_DTOR_DECLARE(Rectangle);
CLASS_AUTO_CLEANUP_DTOR_DECLARE(Rectangle);
