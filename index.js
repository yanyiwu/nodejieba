var segment = require("./build/Release/segment");
segment.DEFAULT_DICT = __dirname + "/dict/jieba.dict.utf8",
segment.DEFAULT_HMM_DICT = __dirname + "/dict/hmm_model.utf8",
segment.DEFAULT_USER_DICT = __dirname + "/dict/user.dict.utf8";
segment.DEFAULT_IDF_DICT = __dirname + "/dict/idf.utf8";
segment.DEFAULT_STOP_WORD_DICT = __dirname + "/dict/stop_words.utf8";

module.exports = segment;
