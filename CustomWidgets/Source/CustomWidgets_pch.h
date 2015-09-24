#pragma once

#if defined(CUSTOM_WIDGETS_PLUGIN)
#  define WIDGET_EXPORT __declspec(dllexport)
#else
#  define WIDGET_EXPORT
#endif

/*!
  \brief макрос для генерирования set/get функций для Q_PROPERTY
  \param type тип свойства
  \param name_get название функции геттера, указанной в Q_PROPERTY
  \param name_set название фукнции сеттера, указанной в Q_PROPERTY
  \param var_name связанная с свойством функция, которая должна быть объявлена в секции private
  */

#define setget(type, name_get, name_set, var_name) void name_set(type value) {var_name = value;} type name_get() const {return var_name;}

