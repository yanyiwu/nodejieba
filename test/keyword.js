var nodejieba = require("../index.js");
//nodejieba.keywordLoadDict("./dict/jieba.dict.utf8", "./dict/hmm_model.utf8", "./dict/idf.utf8", "./dict/stop_words.utf8");
nodejieba.keywordLoadDict("./dict/jieba.dict.utf8", "./dict/hmm_model.utf8", "./dict/idf.utf8", "./dict/stop_words.utf8", "./dict/user.dict.utf8");
nodejieba.extract("非阻塞的南京市长江大桥",  5, function(tl){
	for(var i = 0; i < tl.length; i++) {
		console.log(i + " => " + tl[i]);
	}
});
var tl = nodejieba.extractSync("阻塞的南京市长江大桥", 5);
for(var i = 0; i < tl.length; i++) {
		console.log(i + " == " + tl[i]);
}
