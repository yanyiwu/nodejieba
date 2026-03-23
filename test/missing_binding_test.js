var fs = require("fs");
var os = require("os");
var path = require("path");
var should = require("should");

describe("nodejieba missing binding", function() {
  it("loads without the native binding until first use", function() {
    var fixtureDir = fs.mkdtempSync(path.join(os.tmpdir(), "nodejieba-missing-binding-"));
    var fixtureIndex = path.join(fixtureDir, "index.js");

    fs.copyFileSync(path.join(__dirname, "..", "index.js"), fixtureIndex);

    var nodejieba = require(fixtureIndex);

    should(nodejieba.DEFAULT_DICT).be.a.String();
    nodejieba.cut.should.be.a.Function();

    (function() {
      nodejieba.cut("南京市长江大桥");
    }).should.throw(/nodejieba native binding was not found/);
  });
});
