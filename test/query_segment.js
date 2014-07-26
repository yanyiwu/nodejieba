var segment = require("../index.js");
segment.queryLoadDict("./dict/jieba.dict.utf8", "./dict/hmm_model.utf8");
console.log("非阻塞的:");
segment.queryCut("小明硕士毕业于中国科学院计算所，后在日本京都大学深造",  function(tl){
	for(var i = 0; i < tl.length; i++) {
		console.log(i + " => " + tl[i]);
	}
});
console.log("阻塞的:");
var tl = segment.queryCutSync("小明硕士毕业于中国科学院计算所，后在日本京都大学深造");
for(var i = 0; i < tl.length; i++) {
		console.log(i + " == " + tl[i]);
	}

