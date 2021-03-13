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

# NodeJieba [简体中文](README.md)

[![logo](http://images.yanyiwu.com/NodeJiebaLogo-v1.png)](https://github.com/yanyiwu/nodejieba)

## Introduction

`NodeJieba` provides chinese word segmentation for Node.js based on [CppJieba].

## Install

```sh
npm install nodejieba
```

Or [cnpm] instead of npm

```sh
npm install nodejieba --registry=https://registry.npm.taobao.org --nodejieba_binary_host_mirror=https://npm.taobao.org/mirrors/nodejieba
```

## Usage

```js
var nodejieba = require("nodejieba");
var result = nodejieba.cut("南京市长江大桥");
console.log(result);
//["南京市","长江大桥"]
```

See details in [test/demo.js](test/demo.js)

### Initialization

Initialization is optional and will be executed once `cut` is called with the default dictionaries.

Loading the default dictionaries can be called explicitly by

```js
nodejieba.load();
```

This is similar to the internal call of

```js
nodejieba.load({
  dict: './dict/jieba.dict.utf8',
  hmmDict: './dict/hmm_model.utf8',
  userDict: './dict/userdict.utf8',
  idfDict: './dict/idf.utf8',
  stopWordDict: './dict/stop_words.utf8',
});
```

If a dictionary parameter is missing, its default value will be uesd.

#### Dictionary description

+ dict: the main dictionary with weight and lexical tags, it's recommended to use the default dictionary
+ hmmDict: hidden markov model, it's recommended to use the default dictionary
+ userDict: user dictionary, it's recommended to modify it to your use case
+ idfDict: idf information for keyword extraction
+ stopWordDict: list of stop words for keyword extraction

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

```js
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

+ `node v10`
+ `node v12`
+ `node v14`
+ `node v15`

## Use Cases

+ [gitbook-plugin-search-pro]
+ [pinyin]

## Similar projects

+ [@node-rs/jieba](https://github.com/Brooooooklyn/node-rs/tree/master/packages/jieba)

## Performance

It is supposed to have the best performance out of all available Node.js modules. There is a post available in mandarin [Jieba中文分词系列性能评测].

## Online Demo

http://cppjieba-webdemo.herokuapp.com/
(chrome is suggested)

## Contact

Email: `i@yanyiwu.com`

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
