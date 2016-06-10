[![Build Status](https://travis-ci.org/yanyiwu/nodejieba.png?branch=master)](https://travis-ci.org/yanyiwu/nodejieba)
[![Author](https://img.shields.io/badge/author-@yanyiwu-blue.svg?style=flat)](http://yanyiwu.com/) 
[![Platform](https://img.shields.io/badge/platform-Linux,%20OS%20X,%20Windows-green.svg?style=flat)](https://github.com/yanyiwu/nodejieba)
[![Performance](https://img.shields.io/badge/performance-excellent-brightgreen.svg?style=flat)](http://yanyiwu.com/work/2015/06/14/jieba-series-performance-test.html) 
[![License](https://img.shields.io/badge/license-MIT-yellow.svg?style=flat)](http://yanyiwu.mit-license.org)
[![Dependency Status](https://david-dm.org/yanyiwu/nodejieba.png?theme=shields.io)](https://david-dm.org/yanyiwu/nodejieba)
[![devDependency Status](https://david-dm.org/yanyiwu/nodejieba/dev-status.png?theme=shields.io)](https://david-dm.org/yanyiwu/nodejieba#info=devDependencies)
[![NpmDownload Status](http://img.shields.io/npm/dm/nodejieba.svg)](https://www.npmjs.org/package/nodejieba)
[![NPM Version](https://img.shields.io/npm/v/nodejieba.svg?style=flat)](https://www.npmjs.org/package/nodejieba)
- - -

# NodeJieba [简体中文](README.md)

## Introduction

The Jieba Chinese Word Segmentation Implemented By Node.js .

## Download

```sh
npm install nodejieba
```

Or [cnpm] instead of npm

```sh
npm --registry=http://r.cnpmjs.org install nodejieba
```

## Usage

```js
var nodejieba = require("nodejieba");
var result = nodejieba.cut("南京市长江大桥");
console.log(result);
//["南京市","长江大桥"]
```

See details in [test/demo.js](test/demo.js)

### POS Tagging

```js
var nodejieba = require("nodejieba");
console.log(nodejieba.tag("红掌拨清波"));
//[ { word: '红掌', tag: 'n' },
//  { word: '拨', tag: 'v' },
//  { word: '清波', tag: 'n' } ]
```

See details in [test/demo.js](test/demo.js)

### Keyword Extractor

```
var nodejieba = require("nodejieba");
var topN = 4;
console.log(nodejieba.extract("升职加薪，当上CEO，走上人生巅峰。", topN));
//[ { word: 'CEO', weight: 11.739204307083542 },
//  { word: '升职', weight: 10.8561552143 },
//  { word: '加薪', weight: 10.642581114 },
//  { word: '巅峰', weight: 9.49395840471 } ]
```

See details in [test/demo.js](test/demo.js)

## Testing

Testing passed in the following version:

+ `node v0.10.2`
+ `node v0.12.1`
+ `iojs v1.3.0`
+ `iojs v2.2.1`
+ `node v4.0.0`

## Cases

+ [gitbook-plugin-search-pro]
+ [pinyin]

## Performance

It is supposed to be the best in the angle of high performance, because its basic foundation is powered by C++.

## Online Demo

http://cppjieba-webdemo.herokuapp.com/
(chrome is suggested)

## Contact

Email: `i@yanyiwu.com`
QQ: 64162451

![image](http://7viirv.com1.z0.glb.clouddn.com/5a7d1b5c0d_yanyiwu_personal_qrcodes.jpg)

## Licens

MIT http://yanyiwu.mit-license.org

## Thanks

- [Jieba]

## Author

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
