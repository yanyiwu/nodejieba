## v0.1.4

* 修复关于较低版本编译器需要使用`tr1/unordered_map`导致和`node-gyp`编译选项`-fno-rtti`冲突的编译错误问题。

## v0.1.3

* 更新[CppJieba]，支持更低版本的g++。

## v0.1.2

* 更新[CppJieba]，使用`less_memory`这个branch来减少Trie树内存的开销。

## v0.1.1

* 依照node的c++扩展的常规写法，对CppJieba进行简单的包装，并已`npm publish`

[CppJieba]:http://github.com/aszxqw/cppjieba.git
