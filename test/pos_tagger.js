var nodejieba = require("../index.js");
// 第三个参数是可选参数
//nodejieba.taggerLoadDict("./dict/jieba.dict.utf8", "./dict/hmm_model.utf8", "./dict/user.dict.utf8");
nodejieba.taggerLoadDict("./dict/jieba.dict.utf8", "./dict/hmm_model.utf8");
nodejieba.tag("非阻塞的南京市长江大桥",  function(tl){
	for(var i = 0; i < tl.length; i++) {
		console.log(i + " => " + tl[i]);
	}
});
var tl = nodejieba.tagSync("阻塞的南京市长江大桥");
for(var i = 0; i < tl.length; i++) {
		console.log(i + " == " + tl[i]);
}

