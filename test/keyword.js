var nodejieba = require("../index.js");
nodejieba.keywordLoadDict(nodejieba.DEFAULT_DICT, nodejieba.DEFAULT_HMM_DICT, nodejieba.DEFAULT_IDF_DICT, nodejieba.DEFAULT_STOP_WORD_DICT, nodejieba.DEFAULT_USER_DICT);
nodejieba.extract("非阻塞的南京市长江大桥",  5, function(tl){
	for(var i = 0; i < tl.length; i++) {
		console.log(i + " => " + tl[i]);
	}
});
var tl = nodejieba.extractSync("阻塞的南京市长江大桥", 5);
for(var i = 0; i < tl.length; i++) {
		console.log(i + " == " + tl[i]);
}
