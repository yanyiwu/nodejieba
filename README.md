[![Build Status](https://travis-ci.org/aszxqw/nodejieba.png?branch=master)](https://travis-ci.org/aszxqw/nodejieba)
[![Dependency Status](https://david-dm.org/aszxqw/nodejieba.png?theme=shields.io)](https://david-dm.org/aszxqw/nodejieba)
[![devDependency Status](https://david-dm.org/aszxqw/nodejieba/dev-status.png?theme=shields.io)](https://david-dm.org/aszxqw/nodejieba#info=devDependencies)
[![NpmDownload Status](http://img.shields.io/npm/dm/nodejieba.svg)](https://www.npmjs.org/package/nodejieba)
- - -

# NodeJieba "结巴"分词的Node.js版本

## Introduction

`NodeJieba`只是[CppJieba]简单包装而成的`node`扩展，用来进行中文分词。

详见[NodeJiebaBlog]

## Example

```sh
npm install nodejieba
```

因为`npm`速度很慢而且经常因为墙的原因出现莫名其妙的问题，在此强烈建议使用[cnpm]，命令如下：

```sh
npm --registry=http://r.cnpmjs.org install nodejieba
```


demo.js示例

```js
var segment = require("nodejieba");
segment.loadDict("./node_modules/nodejieba/dict/jieba.dict.utf8", "./node_modules/nodejieba/dict/hmm_model.utf8");
console.log(segment.cut("南京市长江大桥"));
```

## Testing

在`node v0.10.2`下测试通过

## Demo

http://cppjieba-webdemo.herokuapp.com/
(chrome is suggested)

## Thanks

[Jieba中文分词]

## Contact

wuyanyi09@gmail.com

[NodeJiebaBlog]:http://www.aszxqw.com/jekyll/update/2014/02/22/nodejs-cpp-addon-nodejieba.html
[CppJieba]:https://github.com/aszxqw/cppjieba.git
[cnpm]:http://cnpmjs.org
[Jieba中文分词]:https://github.com/fxsjy/jieba
