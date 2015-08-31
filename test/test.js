var should = require("should");
var nodejieba = require("../index.js");

describe("nodejieba", function() {

  var sentence = "我是拖拉机学院手扶拖拉机专业的。不用多久，我就会升职加薪，当上CEO，走上人生巅峰。";

  it("nodejieba.cut(sentence)", function() {
    nodejieba.cut(sentence).should.eql([ '我',
      '是',
      '拖拉机',
      '学院',
      '手扶拖拉机',
      '专业',
      '的',
      '。',
      '不用',
      '多久',
      '，',
      '我',
      '就',
      '会',
      '升职',
      '加薪',
      '，',
      '当上',
      'CEO',
      '，',
      '走上',
      '人生',
      '巅峰',
      '。' ]);
  });

  it("nodejieba.cut('南京市长江大桥')", function() {
    nodejieba.cut('南京市长江大桥').should.eql([ '南京市', '长江大桥' ]);
  });

  it("nodejieba.cut('南京市长江大桥', 'MP')", function() {
    nodejieba.cut('南京市长江大桥', 'MP').should.eql([ '南京市', '长江大桥' ]);
  });

  it("nodejieba.cut('南京市长江大桥', 'HMM')", function() {
    nodejieba.cut('南京市长江大桥', 'HMM').should.eql([ '南京市', '长江大桥' ]);
  });

  it("nodejieba.cut('南京市长江大桥', 'MIX')", function() {
    nodejieba.cut('南京市长江大桥', 'MIX').should.eql([ '南京市', '长江大桥' ]);
  });

  it("nodejieba.cut('南京长江大桥')", function() {
    nodejieba.cut('南京长江大桥').should.eql([ '南京长江大桥' ]);
  });

  it("nodejieba.cut('南京长江大桥', 'MP')", function() {
    nodejieba.cut('南京长江大桥', 'MP').should.eql([ '南京长江大桥' ]);
  });

  it("nodejieba.cut('南京长江大桥', 'HMM')", function() {
    nodejieba.cut('南京长江大桥', 'HMM').should.eql([ '南京长', '江大桥' ]);
  });

  it("nodejieba.cut('南京长江大桥', 'MIX')", function() {
    nodejieba.cut('南京长江大桥', 'MIX').should.eql([ '南京长江大桥' ]);
  });

  it('nodejieba.cut(sentence, "MP")', function() {
    nodejieba.cut(sentence, "MP").should.eql([ '我',
      '是',
      '拖拉机',
      '学院',
      '手扶拖拉机',
      '专业',
      '的',
      '。',
      '不用',
      '多久',
      '，',
      '我',
      '就',
      '会',
      '升职',
      '加薪',
      '，',
      '当',
      '上',
      'C',
      'E',
      'O',
      '，',
      '走上',
      '人生',
      '巅峰',
      '。' ]);
  })

  it('nodejieba.cut(sentence, "HMM")', function() {
    nodejieba.cut(sentence, "HMM").should.eql([ '我',
      '是',
      '拖拉机',
      '学院',
      '手',
      '扶',
      '拖拉机',
      '专业',
      '的',
      '。',
      '不用',
      '多久',
      '，',
      '我',
      '就',
      '会升',
      '职加薪',
      '，',
      '当上',
      'CEO',
      '，',
      '走上',
      '人生',
      '巅峰',
      '。' ]);
  });

  it('nodejieba.cut(sentence, "MIX")', function() {
    nodejieba.cut(sentence, "MIX").should.eql([ '我',
      '是',
      '拖拉机',
      '学院',
      '手扶拖拉机',
      '专业',
      '的',
      '。',
      '不用',
      '多久',
      '，',
      '我',
      '就',
      '会',
      '升职',
      '加薪',
      '，',
      '当上',
      'CEO',
      '，',
      '走上',
      '人生',
      '巅峰',
      '。' ]);
  });

  it('nodejieba.cut(sentence, "FULL")', function() {
    nodejieba.cut(sentence, "FULL").should.eql([ '我',
      '是',
      '拖拉',
      '拖拉机',
      '学院',
      '手扶',
      '手扶拖拉机',
      '拖拉',
      '拖拉机',
      '专业',
      '的',
      '。',
      '不用',
      '多久',
      '，',
      '我',
      '就',
      '会升',
      '升职',
      '加薪',
      '，',
      '当上',
      'C',
      'E',
      'O',
      '，',
      '走上',
      '人生',
      '巅峰',
      '。' ]);
  });

  it('nodejieba.cut(sentence, "QUERY")', function() {
    nodejieba.cut(sentence, "QUERY").should.eql([ '我',
      '是',
      '拖拉机',
      '学院',
      '手扶',
      '手扶拖拉机',
      '拖拉',
      '拖拉机',
      '专业',
      '的',
      '。',
      '不用',
      '多久',
      '，',
      '我',
      '就',
      '会',
      '升职',
      '加薪',
      '，',
      '当上',
      'CEO',
      '，',
      '走上',
      '人生',
      '巅峰',
      '。' ]);
  });

  it('nodejieba.tag(sentence)', function() {
    nodejieba.tag(sentence).should.eql([ '我:r',
      '是:v',
      '拖拉机:n',
      '学院:n',
      '手扶拖拉机:n',
      '专业:n',
      '的:uj',
      '。:x',
      '不用:v',
      '多久:m',
      '，:x',
      '我:r',
      '就:d',
      '会:v',
      '升职:v',
      '加薪:nr',
      '，:x',
      '当上:t',
      'CEO:eng',
      '，:x',
      '走上:v',
      '人生:n',
      '巅峰:n',
      '。:x' ]);
  });

  it('nodejieba.extract(sentence, 5)', function() {
    nodejieba.extract(sentence, 5).should.eql([ 'CEO:11.7392',
      '升职:10.8562',
      '加薪:10.6426',
      '手扶拖拉机:10.0089',
      '巅峰:9.49396' ]);
  });

  it('nodejieba.cut("红掌拨清波")', function() {
    nodejieba.cut("红掌拨清波").should.eql([
      '红掌',
      '拨',
      '清波',
    ]);
  });

  it('nodejieba.cut("男默女泪")', function() {
    nodejieba.cut("男默女泪").should.eql([ '男默',
      '女泪' ]);
  });
  it('nodejieba.insertWord("男默女泪")', function() {
    nodejieba.insertWord("男默女泪").should.eql(true);
  });
  it('nodejieba.cut("男默女泪")', function() {
    nodejieba.cut("男默女泪").should.eql([ '男默女泪' ]);
  });

  it('nodejieba.cut("南京市长江大桥")', function() {
    nodejieba.cut("南京市长江大桥", "MP", 3).should.eql([ '南京市', '长江', '大桥' ]);
  });
});
