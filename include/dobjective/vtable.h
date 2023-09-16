#pragma once

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
#define CLASS_CREATE_VTABLE_IMPL(base_name, current_name, content) \
  const base_name##_vtable current_name##_vtable_instance = content

/**
 * @brief 在类的虚函数表实例中插入类方法
 * 
 */
#define CLASS_SET_VTABLE_METHOD(class_name, name) .name = (void(*))class_name##_##name,

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
#define CLASS_CALL_VTABLE_METHOD(instance, name) instance->vtable->name(instance)

/**
 * @brief 调用虚函数表中的带参数的方法
 * 
 */
#define CLASS_CALL_VTABLE_METHOD_WITH_ARGS(instance, name, ...) \
  instance->vtable->name(instance, __VA_ARGS__)
