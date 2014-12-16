[![Build Status](https://travis-ci.org/aszxqw/nodejieba.png?branch=master)](https://travis-ci.org/aszxqw/nodejieba)
[![Dependency Status](https://david-dm.org/aszxqw/nodejieba.png?theme=shields.io)](https://david-dm.org/aszxqw/nodejieba)
[![devDependency Status](https://david-dm.org/aszxqw/nodejieba/dev-status.png?theme=shields.io)](https://david-dm.org/aszxqw/nodejieba#info=devDependencies)
[![NpmDownload Status](http://img.shields.io/npm/dm/nodejieba.svg)](https://www.npmjs.org/package/nodejieba)
- - -

# NodeJieba "结巴"分词的Node.js版本

## Introduction

`NodeJieba`只是[CppJieba]简单包装而成的`node`扩展，用来进行中文分词。

详见[NodeJiebaBlog]

## Install

```sh
npm install nodejieba
```

因为`npm`速度很慢而且经常因为墙的原因出现莫名其妙的问题，在此强烈建议使用[cnpm]，命令如下：

```sh
npm --registry=http://r.cnpmjs.org install nodejieba
```

## Usage

### 默认分词算法

#### 初始化

```js
var segment = require("nodejieba");
segment.loadDict("./node_modules/nodejieba/dict/jieba.dict.utf8", "./node_modules/nodejieba/dict/hmm_model.utf8");
```

#### 阻塞式调用

```js
var wordList = segment.cutSync("阻塞模式分词");
if (wordList.constructor == Array) // just for tutorial, this is always be true 
{
    wordList.forEach(function(word) {
        console.log(word);     
    });
}
```

#### 非阻塞式调用

```js
segment.cut("非阻塞模式分词", function(wordList) {
    wordList.forEach(function(word) {
        console.log(word);     
    });
});
```

### 搜索引擎分词算法

#### 初始化

```js
var segment = require("nodejieba");
segment.queryLoadDict("./node_modules/nodejieba/dict/jieba.dict.utf8", "./node_modules/nodejieba/dict/hmm_model.utf8");
```

#### 阻塞式调用

```js
var wordList = segment.queryCutSync("阻塞模式分词");
if (wordList.constructor == Array) // just for tutorial, this is always be true 
{
    wordList.forEach(function(word) {
        console.log(word);     
    });
}
```

#### 非阻塞式调用

```js
segment.queryCut("非阻塞模式分词", function(wordList) {
    wordList.forEach(function(word) {
        console.log(word);     
    });
});
```

具体用法可以参考 `test/segment.js test/query_segment.js`

### 词性标注

具体用法可以参考 `test/pos_tagger.js`

## Testing

在`node v0.10.2`下测试通过

## Demo

http://cppjieba-webdemo.herokuapp.com/
(chrome is suggested)

## Thanks

[Jieba中文分词]

## Author

- aszxqw   https://github.com/aszxqw   wuyanyi09@gmail.com
- myl2821  https://github.com/myl2821  myl2821@gmail.com

[NodeJiebaBlog]:http://www.aszxqw.com/work/2014/02/22/nodejs-cpp-addon-nodejieba.html
[CppJieba]:https://github.com/aszxqw/cppjieba.git
[cnpm]:http://cnpmjs.org
[Jieba中文分词]:https://github.com/fxsjy/jieba
