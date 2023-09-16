#pragma once
#include <stdlib.h>

/**
 * @brief 类的前置声明
 *
 */
#define CLASS_DECLARE(name) typedef struct name name

/**
 * @brief struct的typedef封装
 *        在不配合其他宏的情况下，只能用于定义struct
 */
#define CLASS_IMPL(name, content) typedef struct name content name;

/**
 * @brief 声明类的方法
 *        类方法将自动获得一个this指针
 */
#define CLASS_METHOD_DECLARE(class_name, return_type, name) \
  return_type class_name##_##name(class_name* this)

/**
 * @brief 声明类的方法，带参数
 *        类方法将自动获得一个this指针
 */
#define CLASS_METHOD_WITH_ARGS_DECLARE(class_name, return_type, name, ...) \
  return_type class_name##_##name(class_name* this, __VA_ARGS__)

#define CLASS_METHOD_IMPL(class_name, return_type, name, expr) \
  return_type class_name##_##name(class_name* this) expr

#define CLASS_METHOD_WITH_ARGS_IMPL(class_name, return_type, name, expr, ...) \
  return_type class_name##_##name(class_name* this, __VA_ARGS__) expr

#define CLASS_CTOR_DECLARE(class_name) \
  class_name* class_name##_ctor(class_name* this)
#define CLASS_CTOR_WITH_ARGS_DECLARE(class_name, ...) \
  class_name* class_name##_ctor(class_name* this, __VA_ARGS__)

#define CLASS_CTOR_IMPL(class_name, expr)           \
  class_name* class_name##_ctor(class_name* this) { \
    if (this == NULL) {                             \
      this = malloc(sizeof(class_name));            \
    }                                               \
    do expr while (0);                              \
    return this;                                    \
  }

#define CLASS_CTOR_WITH_ARGS_IMPL(class_name, expr, ...)         \
  class_name* class_name##_ctor(class_name* this, __VA_ARGS__) { \
    if (this == NULL) {                                          \
      this = malloc(sizeof(class_name));                         \
    }                                                            \
    do expr while (0);                                           \
    return this;                                                 \
  }

#define CLASS_DTOR_DECLARE(class_name) void class_name##_dtor(class_name* this)

#define CLASS_DTOR_IMPL(class_name, expr)    \
  void class_name##_dtor(class_name* this) { \
    do expr while (0);                       \
    free(this);                              \
  }

#define CLASS_AUTO_CLEANUP_DTOR_DECLARE(class_name) \
  void class_name##_autoclean_dtor(class_name** this)

#define CLASS_AUTO_CLEANUP_DTOR_IMPL(class_name, expr)  \
  void class_name##_autoclean_dtor(class_name** this) { \
    do expr while (0);                                  \
    free(*this);                                        \
  }

#define DERIVE_DECLARE(base_name) base_name base_name##_base;

#define DERIVE_IMPL(base_name, instance)           \
  do {                                             \
    base_name##_ctor(&instance->base_name##_base); \
  } while (0)

#define DERIVE_WITH_ARGS_IMPL(base_name, instance, ...)         \
  do {                                                          \
    base_name##_ctor(&instance->base_name##_base, __VA_ARGS__); \
  } while (0)

#define CLASS_CALL(class_name, instance, method_name) \
  class_name##_##method_name(instance)

#define CLASS_CALL_WITH_ARGS(class_name, instance, method_name, ...) \
  class_name##_##method_name(instance, __VA_ARGS__)
