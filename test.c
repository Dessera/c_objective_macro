#include "test.h"

#include <stdio.h>
#include <stdlib.h>

#include "dobjective/classify.h"

CLASS_CREATE_VTABLE_IMPL(Shape, Shape){CLASS_SET_VTABLE_METHOD(Shape, draw),
                                       CLASS_SET_VTABLE_METHOD(Shape, move)};

CLASS_CTOR_WITH_ARGS_IMPL(Shape, int x, int y, int width, int height) {
  printf("Shape::ctor()\n");
  DERIVE_VTABLE(Shape, Shape, this);
  this->x = x;
  this->y = y;
  this->width = width;
  this->height = height;
}
CLASS_CTOR_WITH_ARGS_IMPL_END

CLASS_DTOR_IMPL(Shape) { printf("Shape::dtor()\n"); }
CLASS_DTOR_IMPL_END

CLASS_AUTO_CLEANUP_DTOR_IMPL(Shape) { printf("Shape::cleanup_dtor()\n"); }
CLASS_AUTO_CLEANUP_DTOR_IMPL_END

CLASS_METHOD_IMPL(Shape, void, draw) { printf("Shape::draw()\n"); }

CLASS_METHOD_WITH_ARGS_IMPL(Shape, void, move, int x, int y) {
  printf("Shape::move()\n");
}

CLASS_CREATE_VTABLE_IMPL(Shape, Rectangle){
    CLASS_SET_VTABLE_METHOD(Rectangle, draw),
    CLASS_SET_VTABLE_METHOD(Rectangle, move)};
CLASS_CTOR_IMPL(Rectangle) {
  printf("Rectangle::ctor()\n");
  DERIVE_WITH_ARGS_IMPL(Shape, this, 1, 2, 3, 4);
  DERIVE_VTABLE(Shape, Rectangle, this);
}
CLASS_CTOR_IMPL_END
CLASS_DTOR_IMPL(Rectangle) { printf("Rectangle::dtor()\n"); }
CLASS_DTOR_IMPL_END
CLASS_AUTO_CLEANUP_DTOR_IMPL(Rectangle) {
  printf("Rectangle::cleanup_dtor()\n");
}
CLASS_AUTO_CLEANUP_DTOR_IMPL_END

CLASS_METHOD_IMPL(Rectangle, void, draw) { printf("Rectangle::draw()\n"); }

CLASS_METHOD_WITH_ARGS_IMPL(Rectangle, void, move, int x, int y) {
  printf("Rectangle::move()\n");
}
