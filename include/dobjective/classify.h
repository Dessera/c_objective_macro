#pragma once

#include <stdlib.h>

/**
 * @brief 声明自动析构的指针
 */
#define AUTO_PTR(type, func) __attribute__((cleanup(func))) type*

/**
 * @brief 声明自动析构的类指针，需要配合CLASS_*宏使用
 */
#define AUTO_CLASS_PTR(type) AUTO_PTR(type, type##_autoclean_dtor)

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
#define CLASS_METHOD_IMPL(class_name, return_type, name) \
  return_type class_name##_##name(class_name* this)

/**
 * @brief 实现类的方法，带参数
 *
 */
#define CLASS_METHOD_WITH_ARGS_IMPL(class_name, return_type, name, ...) \
  return_type class_name##_##name(class_name* this, __VA_ARGS__)

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
#define CLASS_CTOR_IMPL(class_name)                 \
  class_name* class_name##_ctor(class_name* this) { \
    if (this == NULL) {                             \
      this = malloc(sizeof(class_name));            \
    }

#define CLASS_CTOR_IMPL_END \
  return this;              \
  }

/**
 * @brief
 * 实现类的构造函数，会自动分配内存，也可以传入一个已经分配好的内存，带参数
 *
 */
#define CLASS_CTOR_WITH_ARGS_IMPL(class_name, ...)               \
  class_name* class_name##_ctor(class_name* this, __VA_ARGS__) { \
    if (this == NULL) {                                          \
      this = malloc(sizeof(class_name));                         \
    }

#define CLASS_CTOR_WITH_ARGS_IMPL_END \
  return this;                        \
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
#define CLASS_DTOR_IMPL(class_name) void class_name##_dtor(class_name* this) {
#define CLASS_DTOR_IMPL_END \
  free(this);               \
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
#define CLASS_AUTO_CLEANUP_DTOR_IMPL(class_name) \
  void class_name##_autoclean_dtor(class_name** this) {
#define CLASS_AUTO_CLEANUP_DTOR_IMPL_END \
  free(*this);                           \
  }

/**
 * @brief 在类实现中声明继承关系，只支持单继承
 *
 */
#define DERIVE_DECLARE(base_name) base_name base_name##_base

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

/**
 * @brief 类的虚函数表前置声明
 *
 */
#define CLASS_VTABLE_DECLARE(class_name) \
  typedef struct class_name##_vtable class_name##_vtable

/**
 * @brief 类的虚函数表实现
 *
 */
#define CLASS_VTABLE_IMPL(class_name, content) \
  typedef struct class_name##_vtable content class_name##_vtable

/**
 * @brief 在类的虚函数表中声明方法
 *
 */
#define CLASS_VTABLE_METHOD_DECLARE(class_name, return_type, name) \
  return_type (*name)(class_name * this)

/**
 * @brief 在类的虚函数表中声明带参数的方法
 *
 */
#define CLASS_VTABLE_METHOD_WITH_ARGS_DECLARE(class_name, return_type, name, \
                                              ...)                           \
  return_type (*name)(class_name * this, __VA_ARGS__)

/**
 * @brief 类的虚函数表实例前置声明
 *
 */
#define CLASS_CREATE_VTABLE_DECLARE(base_name, current_name) \
  extern const base_name##_vtable current_name##_vtable_instance

/**
 * @brief 类的虚函数表实例实现
 *
 */
#define CLASS_CREATE_VTABLE_IMPL(base_name, current_name) \
  const base_name##_vtable current_name##_vtable_instance =

/**
 * @brief 在类的虚函数表实例中插入类方法
 *
 */
#define CLASS_SET_VTABLE_METHOD(class_name, name) \
  .name = (void(*))class_name##_##name

/**
 * @brief 在类声明中启用虚函数表
 *
 */
#define ENABLE_VTABLE(class_name) class_name##_vtable* vtable

/**
 * @brief 在类构造中链接虚函数表
 *        记得在基类构造后调用
 *
 */
#define DERIVE_VTABLE(base_name, current_name, instance)    \
  do {                                                      \
    base_name* __##instance = (base_name*)instance;         \
    __##instance->vtable = &current_name##_vtable_instance; \
  } while (0)

/**
 * @brief 调用虚函数表中的方法
 *
 */
#define CLASS_CALL_VTABLE_METHOD(instance, name) \
  instance->vtable->name(instance)

/**
 * @brief 调用虚函数表中的带参数的方法
 *
 */
#define CLASS_CALL_VTABLE_METHOD_WITH_ARGS(instance, name, ...) \
  instance->vtable->name(instance, __VA_ARGS__)
