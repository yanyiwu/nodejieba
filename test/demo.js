var nodejieba = require("../index.js");

var sentence = "我是拖拉机学院手扶拖拉机专业的。不用多久，我就会升职加薪，当上CEO，走上人生巅峰。";

var result;

// 没有主动调用nodejieba.load载入词典的时候，
// 会在第一次调用cut或者其他需要词典的函数时，自动载入默认词典。
// 词典只会被加载一次。
result = nodejieba.cut(sentence);
console.log(result);

result = nodejieba.cut(sentence, "MP");
console.log(result);

result = nodejieba.cut(sentence, "HMM");
console.log(result);

result = nodejieba.cut(sentence, "MIX");
console.log(result);

result = nodejieba.cut(sentence, "FULL");
console.log(result);

result = nodejieba.cut(sentence, "QUERY");
console.log(result);

result = nodejieba.tag(sentence);
console.log(result);

result = nodejieba.extract(sentence, 5);
console.log(result);

result = nodejieba.cut("男默女泪");
console.log(result);
nodejieba.insertWord("男默女泪");
result = nodejieba.cut("男默女泪");
console.log(result);

result = nodejieba.cut("南京市长江大桥", "MP", 3);
console.log(result);
