var nodejieba = require("../index.js");

//load参数都是可选的，如果没有对应的项则自动填充默认参数。
//nodejieba.load({
//  dict: nodejieba.DEFAULT_DICT,
//  hmmDict: nodejieba.DEFAULT_HMM_DICT,
//  userDict: __dirname + '/testdata/userdict.utf8',
//  idfDict: nodejieba.DEFAULT_IDF_DICT,
//  stopWordDict: nodejieba.DEFAULT_STOP_WORD_DICT,
//});

nodejieba.load({
  userDict: __dirname + '/testdata/userdict.utf8',
});

result = nodejieba.cut('红掌拨清波')
console.log(result);
