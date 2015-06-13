var nodejieba = require("./build/Release/nodejieba.node");
nodejieba.DEFAULT_DICT = __dirname + "/dict/jieba.dict.utf8",
nodejieba.DEFAULT_HMM_DICT = __dirname + "/dict/hmm_model.utf8",
nodejieba.DEFAULT_USER_DICT = __dirname + "/dict/user.dict.utf8";
nodejieba.DEFAULT_IDF_DICT = __dirname + "/dict/idf.utf8";
nodejieba.DEFAULT_STOP_WORD_DICT = __dirname + "/dict/stop_words.utf8";

nodejieba.load(nodejieba.DEFAULT_DICT, 
               nodejieba.DEFAULT_HMM_DICT, 
               nodejieba.DEFAULT_USER_DICT, 
               nodejieba.DEFAULT_IDF_DICT,
               nodejieba.DEFAULT_STOP_WORD_DICT);
module.exports = nodejieba;
