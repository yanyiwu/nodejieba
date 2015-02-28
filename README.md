[![Build Status](https://travis-ci.org/yanyiwu/nodejieba.png?branch=master)](https://travis-ci.org/yanyiwu/nodejieba)
[![Dependency Status](https://david-dm.org/yanyiwu/nodejieba.png?theme=shields.io)](https://david-dm.org/yanyiwu/nodejieba)
[![devDependency Status](https://david-dm.org/yanyiwu/nodejieba/dev-status.png?theme=shields.io)](https://david-dm.org/yanyiwu/nodejieba#info=devDependencies)
[![NpmDownload Status](http://img.shields.io/npm/dm/nodejieba.svg)](https://www.npmjs.org/package/nodejieba)
- - -

# NodeJieba "结巴"分词的Node.js版本

## 介绍 

`NodeJieba`只是[CppJieba]简单包装而成的`node`扩展，用来进行中文分词。

详见[NodeJiebaBlog]

## 下载

```sh
npm install nodejieba
```

因为`npm`速度很慢而且经常因为墙的原因出现莫名其妙的问题，可以试试使用[cnpm]，命令如下：

```sh
npm --registry=http://r.cnpmjs.org install nodejieba
```

## 用法

### 默认分词算法

#### 初始化

```js
var nodejieba = require("nodejieba");
nodejieba.loadDict("./node_modules/nodejieba/dict/jieba.dict.utf8", "./node_modules/nodejieba/dict/hmm_model.utf8", "./node_modules/nodejieba/dict/user.dict.utf8");
```

#### 阻塞式调用

```js
var wordList = nodejieba.cutSync("阻塞模式分词");
if (wordList.constructor == Array) // just for tutorial, this is always be true 
{
    wordList.forEach(function(word) {
        console.log(word);     
    });
}
```

#### 非阻塞式调用

```js
nodejieba.cut("非阻塞模式分词", function(wordList) {
    wordList.forEach(function(word) {
        console.log(word);     
    });
});
```

### 搜索引擎分词算法

#### 初始化

```js
var nodejieba = require("nodejieba");
nodejieba.queryLoadDict("./node_modules/nodejieba/dict/jieba.dict.utf8", "./node_modules/nodejieba/dict/hmm_model.utf8", "./node_modules/nodejieba/dict/user.dict.utf8");
```

#### 阻塞式调用

```js
var wordList = nodejieba.queryCutSync("阻塞模式分词");
if (wordList.constructor == Array) // just for tutorial, this is always be true 
{
    wordList.forEach(function(word) {
        console.log(word);     
    });
}
```

#### 非阻塞式调用

```js
nodejieba.queryCut("非阻塞模式分词", function(wordList) {
    wordList.forEach(function(word) {
        console.log(word);     
    });
});
```

具体用法可以参考 `test/segment.js test/query_segment.js`

### 词性标注

具体用法可以参考 `test/pos_tagger.js`

### 关键词抽取

具体用法可以参考 `test/keyword.js`

## 测试

在`node v0.10.2`, `node v0.11.13`, `iojs v1.3.0` 下测试通过。

## 在线演示

http://cppjieba-webdemo.herokuapp.com/
(chrome is suggested)

## 鸣谢

[Jieba中文分词]

## 作者

- YanyiWu   http://yanyiwu.com   i@yanyiwu.com
- myl2821  https://github.com/myl2821  myl2821@gmail.com

[NodeJiebaBlog]:http://www.yanyiwu.com/work/2014/02/22/nodejs-cpp-addon-nodejieba.html
[CppJieba]:https://github.com/yanyiwu/cppjieba.git
[cnpm]:http://cnpmjs.org
[Jieba中文分词]:https://github.com/fxsjy/jieba
