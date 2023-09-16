#pragma once

#define AUTO_PTR(type, func) __attribute__((cleanup(func))) type*
#define AUTO_CLASS_PTR(type) AUTO_PTR(type, type##_autoclean_dtor)
