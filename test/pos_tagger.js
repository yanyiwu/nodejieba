var nodejieba = require("../index.js");
nodejieba.taggerLoadDict(nodejieba.DEFAULT_DICT, nodejieba.DEFAULT_HMM_DICT);
nodejieba.tag("非阻塞的南京市长江大桥",  function(tl){
	for(var i = 0; i < tl.length; i++) {
		console.log(i + " => " + tl[i]);
	}
});
var tl = nodejieba.tagSync("阻塞的南京市长江大桥");
for(var i = 0; i < tl.length; i++) {
		console.log(i + " == " + tl[i]);
}

