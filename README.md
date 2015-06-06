[![Build Status](https://travis-ci.org/yanyiwu/nodejieba.png?branch=master)](https://travis-ci.org/yanyiwu/nodejieba)
[![Dependency Status](https://david-dm.org/yanyiwu/nodejieba.png?theme=shields.io)](https://david-dm.org/yanyiwu/nodejieba)
[![devDependency Status](https://david-dm.org/yanyiwu/nodejieba/dev-status.png?theme=shields.io)](https://david-dm.org/yanyiwu/nodejieba#info=devDependencies)
[![NpmDownload Status](http://img.shields.io/npm/dm/nodejieba.svg)](https://www.npmjs.org/package/nodejieba)
- - -

# NodeJieba "结巴"分词的Node.js版本

## 介绍 

`NodeJieba` 是由 [CppJieba] 包装而成的 `node` 扩展，用来支持 Node.js 的中文分词功能。

## 特点

+ `require("nodejieba")` 时自动载入词典，即插即用。
+ 底层算法实现是C++，性能高效。

对实现细节感兴趣的请看如下博文：

+ [Node.js的C++扩展初体验之NodeJieba] 
+ [由NodeJieba谈谈Node.js异步实现] 

## 下载

```sh
npm install nodejieba
```

因为`npm`速度很慢而且经常因为墙的原因出现莫名其妙的问题，可以试试使用[cnpm]，命令如下：

```sh
npm --registry=http://r.cnpmjs.org install nodejieba
```

## 用法

### 初始化

```js
var nodejieba = require("nodejieba");
# require 时自动载入词典。
```

### 词性标注

具体用法参考 `test/test.js`

### 关键词抽取

具体用法参考 `test/test.js`

## 测试

在`node v0.10.2`, `node v0.11.13`, `node v0.12.1`, `iojs v1.3.0` 下测试通过。

## 在线演示

http://cppjieba-webdemo.herokuapp.com/
(chrome is suggested)

## 许可证

MIT http://yanyiwu.mit-license.org

## 鸣谢

[Jieba中文分词]

## 作者

- YanyiWu   http://yanyiwu.com   i@yanyiwu.com
- myl2821  https://github.com/myl2821  myl2821@gmail.com

[由NodeJieba谈谈Node.js异步实现]:http://yanyiwu.com/work/2015/03/21/nodejs-asynchronous-insight.html
[Node.js的C++扩展初体验之NodeJieba]:http://yanyiwu.com/work/2014/02/22/nodejs-cpp-addon-nodejieba.html
[CppJieba]:https://github.com/yanyiwu/cppjieba.git
[cnpm]:http://cnpmjs.org
[Jieba中文分词]:https://github.com/fxsjy/jieba
