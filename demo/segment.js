var segment = require("../build/Release/segment");
segment.loadDict("./dict/jieba.dict.utf8", "./dict/hmm_model.utf8");
console.log(segment.cut("你好世界"));
console.log(segment.cut("你好世界"));
