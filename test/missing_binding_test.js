var fs = require("fs");
var os = require("os");
var path = require("path");
var should = require("should");

describe("nodejieba missing binding", function() {
  it("loads without the native binding until first use", function() {
    var fixtureDir = fs.mkdtempSync(path.join(os.tmpdir(), "nodejieba-missing-binding-"));
    try {
      var fixtureIndex = path.join(fixtureDir, "index.js");

      fs.copyFileSync(path.join(__dirname, "..", "index.js"), fixtureIndex);

      var nodejieba = require(fixtureIndex);

      should(nodejieba.DEFAULT_DICT).type("string");
      should(nodejieba.cut).type("function");

      var firstError;
      var secondError;

      try {
        nodejieba.cut("南京市长江大桥");
      } catch (err) {
        firstError = err;
      }

      try {
        nodejieba.cut("南京市长江大桥");
      } catch (err) {
        secondError = err;
      }

      should(firstError).be.an.Error();
      firstError.message.should.match(/nodejieba native binding was not found/);
      firstError.code.should.equal("BINDING_NOT_FOUND");
      should(secondError).equal(firstError);
    } finally {
      fs.rmSync(fixtureDir, { recursive: true, force: true });
    }
  });
});
