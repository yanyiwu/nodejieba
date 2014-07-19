var segment = require("../index.js");
segment.loadDict("./dict/jieba.dict.utf8", "./dict/hmm_model.utf8");
segment.cut("非阻塞的南京市长江大桥",  function(res){
    console.log(res);
});
console.log(segment.cutSync("阻塞的南京市长江大桥"));
