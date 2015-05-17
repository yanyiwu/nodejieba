var nodejieba = require("../index.js");
nodejieba.queryLoadDict(nodejieba.DEFAULT_DICT, nodejieba.DEFAULT_HMM_DICT);
console.log("非阻塞的:");
nodejieba.queryCut("小明硕士毕业于中国科学院计算所，后在日本京都大学深造",  function(tl){
	for(var i = 0; i < tl.length; i++) {
		console.log(i + " => " + tl[i]);
	}
});
console.log("阻塞的:");
var tl = nodejieba.queryCutSync("小明硕士毕业于中国科学院计算所，后在日本京都大学深造");
for(var i = 0; i < tl.length; i++) {
		console.log(i + " == " + tl[i]);
}

