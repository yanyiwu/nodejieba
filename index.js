var path = require('path');
var BINARY_PATH = path.join(__dirname, 'build/Release/nodejieba.node');
var nodejieba;
var bindingLoadError;

function getNodejieba() {
  if (nodejieba) {
    return nodejieba;
  }
  if (bindingLoadError) {
    throw bindingLoadError;
  }
  try {
    nodejieba = require(BINARY_PATH);
    return nodejieba;
  } catch (err) {
    if (err && err.code === 'MODULE_NOT_FOUND' && err.message && err.message.indexOf(BINARY_PATH) !== -1) {
      bindingLoadError = new Error(
        "nodejieba native binding was not found at " + BINARY_PATH + ". " +
        "This usually means install scripts were skipped or the native binary failed to download/build. " +
        "Try reinstalling without --ignore-scripts or run `npm rebuild nodejieba`."
      );
      bindingLoadError.code = 'BINDING_NOT_FOUND';
      bindingLoadError.cause = err;
      throw bindingLoadError;
    }
    throw err;
  }
}

var isDictLoaded = false;

var DICT_DIR = __dirname + "/submodules/cppjieba/dict/";

var exports = {
  DEFAULT_DICT: DICT_DIR + "jieba.dict.utf8",
  DEFAULT_HMM_DICT: DICT_DIR + "hmm_model.utf8",
  DEFAULT_USER_DICT: DICT_DIR + "user.dict.utf8",
  DEFAULT_IDF_DICT: DICT_DIR + "idf.utf8",
  DEFAULT_STOP_WORD_DICT: DICT_DIR + "stop_words.utf8",

  load: function (dictJson) {
    if (!dictJson) {
      dictJson = {};
    }
    dict         = dictJson.dict       || exports.DEFAULT_DICT;
    hmmDict      = dictJson.hmmDict    || exports.DEFAULT_HMM_DICT;
    userDict     = dictJson.userDict   || exports.DEFAULT_USER_DICT;
    idfDict      = dictJson.idfDict    || exports.DEFAULT_IDF_DICT;
    stopWordDict = dictJson.stopWordDict || exports.DEFAULT_STOP_WORD_DICT;

    var result = getNodejieba().load(dict, hmmDict, userDict, idfDict, stopWordDict);
    isDictLoaded = true;
    return result;
  }
};

function wrapWithDictLoad(functName) {
  exports[functName] = function () {
    if (!isDictLoaded) {
      exports.load();
    }
    return getNodejieba()[functName].apply(this, arguments);
  }
}

wrapWithDictLoad("cut");
wrapWithDictLoad("cutAll");
wrapWithDictLoad("cutHMM");
wrapWithDictLoad("cutForSearch");
wrapWithDictLoad("cutSmall");
wrapWithDictLoad("tag");
wrapWithDictLoad("extract");
wrapWithDictLoad("textRankExtract");
wrapWithDictLoad("insertWord");

module.exports = exports;
