#ifndef LIMONP_HANDY_MACRO_HPP
#define LIMONP_HANDY_MACRO_HPP

#include <cstdio>
#include <cstdlib>

#define LIMONP_CHECK(exp) \
    if(!(exp)){fprintf(stderr, "File:%s, Line:%d Exp:[" #exp "] is true, abort.\n", __FILE__, __LINE__); abort();}

#define print(x) cout<< #x": " << x <<endl
/*
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
*/

#endif
