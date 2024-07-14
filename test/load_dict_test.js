var should = require("should");
var nodejieba = require("../index.js");

describe("nodejieba", function() {
  var userDict = __dirname + '/testdata/userdict.utf8';
  nodejieba.load({
    userDict: userDict,
  });
  it('nodejieba.cut("红掌拨清波")', function() {
    nodejieba.cut("红掌拨清波").should.eql([
      '红掌拨清波',
    ]);
  });
});
