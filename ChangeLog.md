# NodeJieba ChangeLog

## v2.5.2

+ Merged [pull request 193](https://github.com/yanyiwu/nodejieba/pull/193)

## v2.5.1

+ Merged [pull request 179](https://github.com/yanyiwu/nodejieba/pull/179)
+ Since v2.5.0, [node-addon-api](https://github.com/nodejs/node-addon-api) is used, and only Node.js versions 10.0.0 and above are supported. There was an error in the previous description in the v2.5.0 version.

## v2.5.0

+ merged [pull request 177](https://github.com/yanyiwu/nodejieba/pull/177)
+ only supports Node.js 7.0.0 and above.

## v2.4.2

+ merged [pull request 173](https://github.com/yanyiwu/nodejieba/pull/173)

## v2.4.1

+ upgrade deps/limonp -> v0.6.3
+ upgrade deps/cppjieba -> v5.0.3
+ merged [pull request 148](https://github.com/yanyiwu/nodejieba/pull/148)

## v2.4.0

+ revert commit-6600629 to be compatiable with cppjieba.
+ upgrade deps/limonp -> v0.6.2
+ upgrade deps/cppjieba -> v5.0.2

## v2.3.5

+ merged [pull request 143](https://github.com/yanyiwu/nodejieba/pull/143)
+ add release deployment in travis

## v2.3.3

+ merged [pull request 142](https://github.com/yanyiwu/nodejieba/pull/142)

## v2.3.2

+ merged [pull request 140](https://github.com/yanyiwu/nodejieba/pull/140)

## v2.3.1

+ merged [pull request 132](https://github.com/yanyiwu/nodejieba/pull/132)

## v2.3.0

+ merged [pull request 125](https://github.com/yanyiwu/nodejieba/pull/125)

## v2.2.7

+ support typescript [pull request 118](https://github.com/yanyiwu/nodejieba/pull/118)

## v2.2.6

+ fix bug [pull request 113](https://github.com/yanyiwu/nodejieba/pull/113)

## v2.2.5

+ fix bug [pull request 89](https://github.com/yanyiwu/nodejieba/pull/89)

## v2.2.4

+ support "tag" in insertWord function. [pull request 71](https://github.com/yanyiwu/nodejieba/pull/71)

## v2.2.3

+ update cppjieba -> 4a755dff to try fixing [issue 65](https://github.com/yanyiwu/nodejieba/issues/65)

## v2.2.2

+ upgrade cppjieba -> v4.8.1
+ (word freq tag) format in user dict has been supported.

## v2.2.1

+ fix bug in v2.2.0 about 'cutSmall'

## v2.2.0

+ add api `cutSmall` to cut words in specific word length limit

## v2.1.0

+ function `tag,extract` return objects, instead of strings.
+ fix issue [issue 58](https://github.com/yanyiwu/nodejieba/issues/58)

## v2.0.0

+ Upgrade cppjieba -> v4.8.0
+ rewrite `cut` function:
+ add `cutAll` for old `cut(s, "FULL")` function.
+ add `cutHMM` for old `cut(s, "HMM")` function.
+ add `cutForSearch` for old `cut(s, "Query")` function.
 
## v1.4.11

+ Upgrade dependencies

+ "nan": "~2.2.0" -> "~2.3.0"

+ Upgrade devDependencies

+ "mocha": "~2.3.4" -> "~2.4.5"
+ "should": "~8.0.2" -> "~8.3.1"

+ Upgrade deps/

+ cppjieba -> v4.7.0
+ limonp -> v0.6.1

## v1.4.10

Upgrade to fix potential trouble:

+ limonp -> v0.5.6
+ cppjieba -> v4.5.2

## v1.4.9

Upgrade limonp and cppjieba to fix [issue48](https://github.com/yanyiwu/nodejieba/issues/48)

* limonp -> v0.5.4
* cppjieba -> v4.5.0

## v1.4.8

Upgrade:

* cppjieba -> v4.4.1 to fix bug, see details in [CppJieba ChangeLog v4.4.1](https://github.com/yanyiwu/cppjieba/blob/master/ChangeLog.md#v441)

## v1.4.7

Upgrade:

* limonp -> v0.5.3, fix incompatibility problem in Windows.

## v1.4.6

Change source codes layout

* lib/jieba/limonp -> deps/limonp
* lib/jieba -> deps/cppjieba

Upgrade:

* limonp -> v0.5.2, fix incompatibility problem of [issue45](https://github.com/yanyiwu/nodejieba/issues/45)
* cppjieba -> v4.3.2

## v1.4.5

* 修复多余日志输出的问题。

## v1.4.4

* 升级 [cppjieba] 到最新版本 v4.2.1

## v1.4.3

* 升级 [cppjieba] 到最新版本 v4.1.2

## v1.4.2

* 升级 package.json 里面的依赖库。

## v1.4.1

* [enhancement issue]: https://github.com/yanyiwu/nodejieba/issues/39

## v1.4.0

* 对MP算法的分词方式新增一个粒度参数，解决[issue29]关于细粒度分词的问题。

## v1.3.0

* 合并 [pr37], 修复 [issue36] 。 放弃对旧版本 `node.js v0.11` 的支持。

## v1.2.2

* 修复依赖的nan版本的问题。

## v1.2.1

* 修复load函数重复调用时内存没有释放的问题。

## v1.2.0

* 同时支持【不配置词典文件直接使用】和【灵活配置词典】的需求。

## v1.1.0

* 新增支持动态增加词库的API函数: `insertWord`

## v1.0.3

* Merge Pull Request [pr28]，显示声明依赖的是 node 后缀的文件，解决一些库重写了 require 的问题。

## v1.0.2

* 修复在 windows 上编译不通过的问题，提升兼容性。

## v1.0.1

* 修复在iojs v2.2.1 上编译不通过的问题，提升兼容性。

## v1.0.0

* 使用[cppjieba] v3.0.0 版本，使用更简洁的接口函数，可以使用参数指定切词方法。
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

* 更新 [cppjieba] 。
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

* 更新[cppjieba]，支持更低版本的g++。

## v0.1.2

* 更新[cppjieba]，使用`less_memory`这个branch来减少Trie树内存的开销。

## v0.1.1

* 依照node的c++扩展的常规写法，对cppjieba进行简单的包装，并已`npm publish`

[cppjieba]:http://github.com/yanyiwu/cppjieba.git
[nan]:https://github.com/nodejs/nan/
[issue23]:https://github.com/yanyiwu/nodejieba/issues/23
[pr28]:https://github.com/yanyiwu/nodejieba/pull/28
[issue36]:https://github.com/yanyiwu/nodejieba/issues/36
[issue29]:https://github.com/yanyiwu/nodejieba/issues/29
