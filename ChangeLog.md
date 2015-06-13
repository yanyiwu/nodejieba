# ChangeLog

## v1.0.3

* Merge Pull Request [pull28]，显示声明依赖的是 node 后缀的文件，解决一些库重写了 require 的问题。

## v1.0.2

* 修复在 windows 上编译不通过的问题，提升兼容性。

## v1.0.1

* 修复在iojs v2.2.1 上编译不通过的问题，提升兼容性。

## v1.0.0

* 使用[CppJieba] v3.0.0 版本，使用更简洁的接口函数，可以使用参数指定切词方法。
* `require("nodejieba")` 时自动载入词典，用户无需再烦心字典的事情，实现即插即用。
* 听从 [issue23] 的建议，废除异步调用的接口，现在的接口函数都是同步调用函数，分别是 `cut`, `tag`, `extract` 。因为分词毕竟是CPU密集型的事情，没必要使用异步调用。

## v0.2.13

* 升级[nan]到 `^v1.8.0` 以支持 `iojs-v2.x`

## v0.2.12

* 新增以下默认词典地址，让使用者不需要自己写词典的相对地址。
* nodejieba.DEFAULT_DICT
* nodejieba.DEFAULT_HMM_DICT
* nodejieba.DEFAULT_USER_DICT
* nodejieba.DEFAULT_IDF_DICT
* nodejieba.DEFAULT_STOP_WORD_DICT

## v0.2.11

* 更新 [CppJieba] 。
* 打印更详细的初始化错误日志信息。

## v0.2.10

* 避免一些在Mac系统下的词典载入日志，更干净的用户体验。

## v0.2.9

* 支持vs2012编译。

## v0.2.8(deleted)

* 支持vs2012编译。

## v0.2.7

* 关键词抽取支持自定义词典(可选参数)。

## v0.2.6

* 修复不同Node版本的兼容性问题，在v0.11.13下测试通过。
* 支持自定义词典(可选参数)。
* 增加关键词抽取功能。

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

[CppJieba]:http://github.com/yanyiwu/cppjieba.git
[nan]:https://github.com/nodejs/nan/
[issue23]:https://github.com/yanyiwu/nodejieba/issues/23
[pull28]:https://github.com/yanyiwu/nodejieba/pull/28
