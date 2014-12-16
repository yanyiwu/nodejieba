## v0.2.5

* 增加词性标注功能

## v0.2.4

* 更新 package 兼容更低版本的 npm

## v0.2.3

* 更新 cppjieba ，减少内存使用。

## v0.2.2

* 在queryLoadDict 函数中增加query模式的粒度阈值作为可选参数。 

## v0.2.1

* 增加搜索引擎分词模式，分别对应的调用函数是 `queryLoadDict, queryCutSync, queryCut`。 

## v0.2.0

* 将原来的 cut 阻塞分词模式改为非阻塞模式
* 阻塞分词模型的函数名为 cutSync

## v0.1.4

* 修复关于较低版本编译器需要使用`tr1/unordered_map`导致和`node-gyp`编译选项`-fno-rtti`冲突的编译错误问题。

## v0.1.3

* 更新[CppJieba]，支持更低版本的g++。

## v0.1.2

* 更新[CppJieba]，使用`less_memory`这个branch来减少Trie树内存的开销。

## v0.1.1

* 依照node的c++扩展的常规写法，对CppJieba进行简单的包装，并已`npm publish`

[CppJieba]:http://github.com/aszxqw/cppjieba.git
