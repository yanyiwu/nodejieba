# NodeJieba "结巴"中文分词的Node.js版本

## 概述

`NodeJieba`只是[CppJieba]简单包装而成的`node`扩展，用来进行中文分词。

详见[NodeJiebaBlog]

## 安装和使用

`npm install nodejieba`

## 使用实例

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

## 测试

在`node v0.10.2`下测试通过

## 演示

http://cppjieba-webdemo.herokuapp.com/
(chrome is suggested)

## 鸣谢

[Jieba中文分词]

## 客服

wuyanyi09@gmail.com

[NodeJiebaBlog]:http://aszxqw.github.io/jekyll/update/2014/02/22/nodejs-cpp-addon-nodejieba.html
[CppJieba]:https://github.com/aszxqw/cppjieba.git
[cnpm]:http://cnpmjs.org
[Jieba中文分词]:https://github.com/fxsjy/jieba
