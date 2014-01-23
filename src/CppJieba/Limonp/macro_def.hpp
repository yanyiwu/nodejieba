#ifndef LIMONP_MACRO_DEF_H
#define LIMONP_MACRO_DEF_H

#define XX_GET_SET(varType, varName, funName)\
private: varType varName;\
public: inline varType get##funName(void) const {return varName;}\
public: inline void set##funName(varType var) {varName = var;}

#define XX_GET(varType, varName, funName)\
private: varType varName;\
public: inline varType get##funName(void) const {return varName;}

#define XX_SET(varType, varName, funName)\
private: varType varName;\
public: inline void set##funName(varType var) {varName = var;}

#define XX_GET_SET_BY_REF(varType, varName, funName)\
private: varType varName;\
public: inline const varType& get##funName(void) const {return varName;}\
public: inline void set##funName(const varType& var){varName = var;}

#endif
