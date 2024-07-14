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

---

# NodeJieba [简体中文](README.md)

[![logo](http://images.yanyiwu.com/NodeJiebaLogo-v1.png)](https://github.com/yanyiwu/nodejieba)

## Introduction

`NodeJieba` provides chinese word segmentation for Node.js based on [CppJieba].

## Install

```sh
npm install nodejieba
```

Or with `npmmirror.com`:

```sh
npm install nodejieba --registry=https://registry.npmmirror.com --nodejieba_binary_host_mirror=https://registry.npmmirror.com/-/binary/nodejieba/
```

## Usage

```js
import { cut } from "nodejieba";

const result = cut("南京市长江大桥");
console.log(result);
//["南京市","长江大桥"]
```

See details in [test cases](__tests__/api.spec.ts)

### Initialization

Initialization is optional and will be executed once `cut` is called with the default dictionaries.

Loading the default dictionaries can be called explicitly by

```js
import { load } from "nodejieba";

load();
```

If a dictionary parameter is missing, its default value will be uesd.

#### Dictionary description

- dict: the main dictionary with weight and lexical tags, it's recommended to use the default dictionary
- hmmDict: hidden markov model, it's recommended to use the default dictionary
- userDict: user dictionary, it's recommended to modify it to your use case
- idfDict: idf information for keyword extraction
- stopWordDict: list of stop words for keyword extraction

### POS Tagging

```js
import { tag } from "nodejieba";

console.log(tag("红掌拨清波"));
//[ { word: '红掌', tag: 'n' },
//  { word: '拨', tag: 'v' },
//  { word: '清波', tag: 'n' } ]
```

See details in [test cases](__tests__/api.spec.ts)

### Keyword Extractor

```js
import { extract, textRankExtract } from "nodejieba";

const topN = 4;

console.log(extract("升职加薪，当上CEO，走上人生巅峰。", topN));
//[ { word: 'CEO', weight: 11.739204307083542 },
//  { word: '升职', weight: 10.8561552143 },
//  { word: '加薪', weight: 10.642581114 },
//  { word: '巅峰', weight: 9.49395840471 } ]

console.log(textRankExtract("升职加薪，当上CEO，走上人生巅峰。", topN));
//[ { word: '当上', weight: 1 },
//  { word: '不用', weight: 0.9898479330698993 },
//  { word: '多久', weight: 0.9851260595435759 },
//  { word: '加薪', weight: 0.9830464899847804 },
//  { word: '升职', weight: 0.9802777682279076 } ]
```

See details in [test cases](__tests__/api.spec.ts)

## Node.js Support

- `v16`
- `v18`
- `v20`

## Use Cases

- [gitbook-plugin-search-pro]
- [pinyin]

## Similar projects

- [@node-rs/jieba](https://github.com/Brooooooklyn/node-rs/tree/master/packages/jieba)

## Performance

It is supposed to have the best performance out of all available Node.js modules. There is a post available in mandarin [Jieba 中文分词系列性能评测].

## Online Demo

<http://cppjieba-webdemo.herokuapp.com/> (chrome is suggested)

## Contact

Email: `i@yanyiwu.com`

## Author

- [YanyiWu]
- [contributors]

[CppJieba]: https://github.com/yanyiwu/cppjieba.git
[contributors]: https://github.com/yanyiwu/nodejieba/graphs/contributors
[YanyiWu]: http://yanyiwu.com
[gitbook-plugin-search-pro]: https://plugins.gitbook.com/plugin/search-pro
[pinyin]: https://github.com/hotoo/pinyin

## Contributors

### Code Contributors

This project exists thanks to all the people who contribute.

<a href="https://github.com/yanyiwu/nodejieba/graphs/contributors"><img src="https://opencollective.com/nodejieba/contributors.svg?width=890&button=false" /></a>

### Financial Contributors

Become a financial contributor and help us sustain our community. [[Contribute](https://opencollective.com/nodejieba/contribute)]

#### Individuals

<a href="https://opencollective.com/nodejieba"><img src="https://opencollective.com/nodejieba/individuals.svg?width=890"></a>

#### Organizations

Support this project with your organization. Your logo will show up here with a link to your website. [Contribute](https://opencollective.com/nodejieba/contribute)

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
