[![Build Status](https://travis-ci.org/yanyiwu/nodejieba.png?branch=master)](https://travis-ci.org/yanyiwu/nodejieba)
[![Financial Contributors on Open Collective](https://opencollective.com/nodejieba/all/badge.svg?label=financial+contributors)](https://opencollective.com/nodejieba) [![Author](https://img.shields.io/badge/author-@yanyiwu-blue.svg?style=flat)](http://yanyiwu.com/) 
[![Donate](https://img.shields.io/badge/donate-eos_gitdeveloper-orange.svg)](https://eosflare.io/account/gitdeveloper)
[![Platform](https://img.shields.io/badge/platform-Linux,%20OS%20X,%20Windows-green.svg?style=flat)](https://github.com/yanyiwu/nodejieba)
[![Performance](https://img.shields.io/badge/performance-excellent-brightgreen.svg?style=flat)](http://yanyiwu.com/work/2015/06/14/jieba-series-performance-test.html) 
[![License](https://img.shields.io/badge/license-MIT-yellow.svg?style=flat)](http://yanyiwu.mit-license.org)
[![NpmDownload Status](http://img.shields.io/npm/dm/nodejieba.svg)](https://www.npmjs.org/package/nodejieba)
[![NPM Version](https://img.shields.io/npm/v/nodejieba.svg?style=flat)](https://www.npmjs.org/package/nodejieba)
[![Code Climate](https://codeclimate.com/github/yanyiwu/nodejieba/badges/gpa.svg)](https://codeclimate.com/github/yanyiwu/nodejieba)
[![Coverage Status](https://coveralls.io/repos/yanyiwu/nodejieba/badge.svg?branch=master&service=github)](https://coveralls.io/github/yanyiwu/nodejieba?branch=master)
- - -

# NodeJieba "结巴"分词的Node.js版本 [English](README_EN.md)

[![logo](http://images.yanyiwu.com/NodeJiebaLogo-v1.png)](https://github.com/yanyiwu/nodejieba)

## 介绍 

`NodeJieba`是"结巴"中文分词的 Node.js 版本实现，
由[CppJieba]提供底层分词算法实现，
是兼具高性能和易用性两者的 Node.js 中文分词组件。

## 特点

+ 词典载入方式灵活，无需配置词典路径也可使用，需要定制自己的词典路径时也可灵活定制。
+ 底层算法实现是C++，性能高效。
+ 支持多种分词算法，各种分词算法见[CppJieba]的README.md介绍。
+ 支持动态补充词库。

对实现细节感兴趣的请看如下博文：

+ [Node.js的C++扩展初体验之NodeJieba] 
+ [由NodeJieba谈谈Node.js异步实现] 

## 下载

```sh
npm install nodejieba
```

因为`npm`速度很慢而且经常因为墙的原因出现莫名其妙的问题，可以试试使用[cnpm]，命令如下：

```sh
npm install nodejieba --registry=https://registry.npm.taobao.org --nodejieba_binary_host_mirror=https://npm.taobao.org/mirrors/nodejieba
```

## 用法

```js
var nodejieba = require("nodejieba");
var result = nodejieba.cut("南京市长江大桥");
console.log(result);
//["南京市","长江大桥"]
```

更详细的其他用法请看 [test/demo.js](test/demo.js)

### 词典载入可灵活配置

如果没有主动调用词典函数时，
则会在第一次调用cut等功能函数时，自动载入默认词典。

如果要主动触发词典载入，则使用以下函数主动触发。

```js
nodejieba.load();
```

以上用法会自动载入所有默认词典，
如果需要载入自己的词典，而不是默认词典。
比如想要载入自己的用户词典，则使用以下函数：

```js
nodejieba.load({
  userDict: './test/testdata/userdict.utf8',
});
```

字典载入函数load的参数项都是可选的，
如果没有对应的项则自动填充默认参数。
所以上面这段代码和下面这代代码是等价的。

```js
nodejieba.load({
  dict: nodejieba.DEFAULT_DICT,
  hmmDict: nodejieba.DEFAULT_HMM_DICT,
  userDict: './test/testdata/userdict.utf8',
  idfDict: nodejieba.DEFAULT_IDF_DICT,
  stopWordDict: nodejieba.DEFAULT_STOP_WORD_DICT,
});
```

#### 词典说明

+ dict: 主词典，带权重和词性标签，建议使用默认词典。
+ hmmDict: 隐式马尔科夫模型，建议使用默认词典。
+ userDict: 用户词典，建议自己根据需要定制。
+ idfDict: 关键词抽取所需的idf信息。
+ stopWordDict: 关键词抽取所需的停用词列表。

### 词性标注

```js
var nodejieba = require("nodejieba");
console.log(nodejieba.tag("红掌拨清波"));
//[ { word: '红掌', tag: 'n' },
//  { word: '拨', tag: 'v' },
//  { word: '清波', tag: 'n' } ]
```

更详细的其他用法请看 [test/demo.js](test/demo.js)

### 关键词抽取

```js
var nodejieba = require("nodejieba");
var topN = 4;
console.log(nodejieba.extract("升职加薪，当上CEO，走上人生巅峰。", topN));
//[ { word: 'CEO', weight: 11.739204307083542 },
//  { word: '升职', weight: 10.8561552143 },
//  { word: '加薪', weight: 10.642581114 },
//  { word: '巅峰', weight: 9.49395840471 } ]
```

更详细的其他用法请看 [test/demo.js](test/demo.js)

## 测试

以下版本中测试通过:

+ `node v10`
+ `node v12`
+ `node v14`
+ `node v15`

## 应用

+ 支持中文搜索的 gitbook 插件: [gitbook-plugin-search-pro]
+ 汉字拼音转换工具: [pinyin]

## 相关项目

+ [@node-rs/jieba](https://github.com/Brooooooklyn/node-rs/tree/master/packages/jieba)

## 性能评测

性能杠杠的，应该是目前性能最好的 Node.js 中文分词库，没有之一。
详见: [Jieba中文分词系列性能评测]

## 在线演示

http://cppjieba-webdemo.herokuapp.com/
(chrome is suggested)

## NodeJieba 在 Windows 上面的一系列安装问题和斗争成功过程参考

+ [win10 X64, VS2013, nodejieba@2.2.2 编译不成功](https://github.com/yanyiwu/nodejieba/issues/65)
+ [version 2.2.2 Can't build on Win 10 x64](https://github.com/yanyiwu/nodejieba/issues/64)
+ [nodejieba 在win7下的安装问题，有进展了](http://www.jianshu.com/p/d541c8585479)
+ [win10 npm安装报错](https://github.com/yanyiwu/nodejieba/issues/70)

## 客服

Email: `i@yanyiwu.com`

## 作者

- [YanyiWu]
- [contributors]

[由NodeJieba谈谈Node.js异步实现]:http://yanyiwu.com/work/2015/03/21/nodejs-asynchronous-insight.html
[Node.js的C++扩展初体验之NodeJieba]:http://yanyiwu.com/work/2014/02/22/nodejs-cpp-addon-nodejieba.html
[CppJieba]:https://github.com/yanyiwu/cppjieba.git
[cnpm]:http://cnpmjs.org
[Jieba中文分词]:https://github.com/fxsjy/jieba

[Jieba中文分词系列性能评测]:http://yanyiwu.com/work/2015/06/14/jieba-series-performance-test.html
[contributors]:https://github.com/yanyiwu/nodejieba/graphs/contributors
[YanyiWu]:http://yanyiwu.com
[gitbook-plugin-search-pro]:https://plugins.gitbook.com/plugin/search-pro
[pinyin]:https://github.com/hotoo/pinyin

## Contributors

### Code Contributors

This project exists thanks to all the people who contribute. [[Contribute](CONTRIBUTING.md)].
<a href="https://github.com/yanyiwu/nodejieba/graphs/contributors"><img src="https://opencollective.com/nodejieba/contributors.svg?width=890&button=false" /></a>

### Financial Contributors

Become a financial contributor and help us sustain our community. [[Contribute](https://opencollective.com/nodejieba/contribute)]

#### Individuals

<a href="https://opencollective.com/nodejieba"><img src="https://opencollective.com/nodejieba/individuals.svg?width=890"></a>

#### Organizations

Support this project with your organization. Your logo will show up here with a link to your website. [[Contribute](https://opencollective.com/nodejieba/contribute)]

<a href="https://opencollective.com/nodejieba/organization/0/website"><img src="https://opencollective.com/nodejieba/organization/0/avatar.svg"></a>
<a href="https://opencollective.com/nodejieba/organization/1/website"><img src="https://opencollective.com/nodejieba/organization/1/avatar.svg"></a>
<a href="https://opencollective.com/nodejieba/organization/2/website"><img src="https://opencollective.com/nodejieba/organization/2/avatar.svg"></a>
<a href="https://opencollective.com/nodejieba/organization/3/website"><img src="https://opencollective.com/nodejieba/organization/3/avatar.svg"></a>
<a href="https://opencollective.com/nodejieba/organization/4/website"><img src="https://opencollective.com/nodejieba/organization/4/avatar.svg"></a>
<a href="https://opencollective.com/nodejieba/organization/5/website"><img src="https://opencollective.com/nodejieba/organization/5/avatar.svg"></a>
<a href="https://opencollective.com/nodejieba/organization/6/website"><img src="https://opencollective.com/nodejieba/organization/6/avatar.svg"></a>
<a href="https://opencollective.com/nodejieba/organization/7/website"><img src="https://opencollective.com/nodejieba/organization/7/avatar.svg"></a>
<a href="https://opencollective.com/nodejieba/organization/8/website"><img src="https://opencollective.com/nodejieba/organization/8/avatar.svg"></a>
<a href="https://opencollective.com/nodejieba/organization/9/website"><img src="https://opencollective.com/nodejieba/organization/9/avatar.svg"></a>
