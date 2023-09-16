#pragma once
#include <stdlib.h>

/**
 * @brief 类的前置声明
 *
 */
#define CLASS_DECLARE(name) typedef struct name name

/**
 * @brief 类的实现
 */
#define CLASS_IMPL(name, content) typedef struct name content name

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

/**
 * @brief 实现类的方法
 *
 */
#define CLASS_METHOD_IMPL(class_name, return_type, name, expr) \
  return_type class_name##_##name(class_name* this) expr

/**
 * @brief 实现类的方法，带参数
 *
 */
#define CLASS_METHOD_WITH_ARGS_IMPL(class_name, return_type, name, expr, ...) \
  return_type class_name##_##name(class_name* this, __VA_ARGS__) expr

/**
 * @brief 声明类的构造函数
 *
 */
#define CLASS_CTOR_DECLARE(class_name) \
  class_name* class_name##_ctor(class_name* this)

/**
 * @brief 声明类的构造函数，带参数
 *
 */
#define CLASS_CTOR_WITH_ARGS_DECLARE(class_name, ...) \
  class_name* class_name##_ctor(class_name* this, __VA_ARGS__)

/**
 * @brief 实现类的构造函数，会自动分配内存，也可以传入一个已经分配好的内存
 *
 */
#define CLASS_CTOR_IMPL(class_name, expr)           \
  class_name* class_name##_ctor(class_name* this) { \
    if (this == NULL) {                             \
      this = malloc(sizeof(class_name));            \
    }                                               \
    do expr while (0);                              \
    return this;                                    \
  }

/**
 * @brief
 * 实现类的构造函数，会自动分配内存，也可以传入一个已经分配好的内存，带参数
 *
 */
#define CLASS_CTOR_WITH_ARGS_IMPL(class_name, expr, ...)         \
  class_name* class_name##_ctor(class_name* this, __VA_ARGS__) { \
    if (this == NULL) {                                          \
      this = malloc(sizeof(class_name));                         \
    }                                                            \
    do expr while (0);                                           \
    return this;                                                 \
  }

/**
 * @brief 声明类的析构函数
 * 
 */
#define CLASS_DTOR_DECLARE(class_name) void class_name##_dtor(class_name* this)

/**
 * @brief 实现类的析构函数，会自动释放内存
 * 
 */
#define CLASS_DTOR_IMPL(class_name, expr)    \
  void class_name##_dtor(class_name* this) { \
    do expr while (0);                       \
    free(this);                              \
  }

/**
 * @brief 声明类的自动清理析构函数
 *        该函数是为了配合__attribute__((cleanup))使用的
 */
#define CLASS_AUTO_CLEANUP_DTOR_DECLARE(class_name) \
  void class_name##_autoclean_dtor(class_name** this)

/**
 * @brief 实现类的自动清理析构函数，会自动释放内存
 * 
 */
#define CLASS_AUTO_CLEANUP_DTOR_IMPL(class_name, expr)  \
  void class_name##_autoclean_dtor(class_name** this) { \
    do expr while (0);                                  \
    free(*this);                                        \
  }

/**
 * @brief 在类实现中声明继承关系，只支持单继承
 * 
 */
#define DERIVE_DECLARE(base_name) base_name base_name##_base;

/**
 * @brief 在构造时调用基类的构造函数
 * 
 */
#define DERIVE_IMPL(base_name, instance)           \
  do {                                             \
    base_name##_ctor(&instance->base_name##_base); \
  } while (0)

/**
 * @brief 在构造时调用基类的构造函数，带参数
 * 
 */
#define DERIVE_WITH_ARGS_IMPL(base_name, instance, ...)         \
  do {                                                          \
    base_name##_ctor(&instance->base_name##_base, __VA_ARGS__); \
  } while (0)

/**
 * @brief 调用类的方法
 * 
 */
#define CLASS_CALL(class_name, instance, method_name) \
  class_name##_##method_name(instance)

/**
 * @brief 调用类的方法，带参数
 * 
 */
#define CLASS_CALL_WITH_ARGS(class_name, instance, method_name, ...) \
  class_name##_##method_name(instance, __VA_ARGS__)
