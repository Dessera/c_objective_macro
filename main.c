#include <stdio.h>
#include <stdlib.h>

#include "dobjective/class.h"
#include "dobjective/cleanup.h"
#include "dobjective/vtable.h"
#include "test.h"

int main(void) {
  AUTO_CLASS_PTR(Shape)
  shape = CLASS_CALL_WITH_ARGS(Shape, NULL, ctor, 0, 0, 100, 100);

  AUTO_CLASS_PTR(Shape) rectangle = CLASS_CALL(Rectangle, NULL, ctor);

  CALL_VTABLE_METHOD(shape, draw);
  CALL_VTABLE_METHOD_WITH_ARGS(shape, move, 10, 10);

  CALL_VTABLE_METHOD(rectangle, draw);
  CALL_VTABLE_METHOD_WITH_ARGS(rectangle, move, 10, 10);

  return 0;
}
