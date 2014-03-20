var segment = require("../index.js");
segment.loadDict("./dict/jieba.dict.utf8", "./dict/hmm_model.utf8");
console.log(segment.cut("南京市长江大桥"));
