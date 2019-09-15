var should = require("should");
var nodejieba = require("../index.js");

describe("nodejieba", function() {

  var sentence = "我是拖拉机学院手扶拖拉机专业的。不用多久，我就会升职加薪，当上CEO，走上人生巅峰。";

  it("nodejieba.cut(sentence, true)", function() {
    nodejieba.cut(sentence, true).should.eql([ '我',
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

  it("nodejieba.cut('南京市长江大桥')", function() {
    nodejieba.cut('南京市长江大桥').should.eql([ '南京市', '长江大桥' ]);
  });

  it("nodejieba.cutHMM('南京市长江大桥')", function() {
    nodejieba.cutHMM('南京市长江大桥').should.eql([ '南京市', '长江大桥' ]);
  });

  it("nodejieba.cut('南京市长江大桥', true)", function() {
    nodejieba.cut('南京市长江大桥', true).should.eql([ '南京市', '长江大桥' ]);
  });

  it("nodejieba.cut('南京长江大桥')", function() {
    nodejieba.cut('南京长江大桥').should.eql([ '南京长江大桥' ]);
  });

  it("nodejieba.cut('南京长江大桥')", function() {
    nodejieba.cut('南京长江大桥').should.eql([ '南京长江大桥' ]);
  });

  it("nodejieba.cutHMM('南京长江大桥')", function() {
    nodejieba.cutHMM('南京长江大桥').should.eql([ '南京长', '江大桥' ]);
  });

  it("nodejieba.cut('南京长江大桥', true)", function() {
    nodejieba.cut('南京长江大桥', true).should.eql([ '南京长江大桥' ]);
  });

  it('nodejieba.cut(sentence)', function() {
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

  it('nodejieba.cutHMM(sentence)', function() {
    nodejieba.cutHMM(sentence).should.eql([ '我',
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

  it('nodejieba.cut(sentence, true)', function() {
    nodejieba.cut(sentence, true).should.eql([ '我',
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

  it('nodejieba.cutAll(sentence)', function() {
    nodejieba.cutAll(sentence).should.eql([ '我',
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

  it('nodejieba.cutForSearch(sentence)', function() {
    nodejieba.cutForSearch(sentence).should.eql([ '我',
      '是',
      '拖拉',
      '拖拉机',
      '学院',
      '手扶',
      '拖拉',
      '拖拉机',
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
  });

  it('nodejieba.cutForSearch(sentence, true)', function() {
    nodejieba.cutForSearch(sentence, true).should.eql([ '我',
      '是',
      '拖拉',
      '拖拉机',
      '学院',
      '手扶',
      '拖拉',
      '拖拉机',
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

  it('nodejieba.tag(sentence)', function() {
    nodejieba.tag(sentence).should.eql([ { word: '我', tag: 'r' },
      { word: '是', tag: 'v' },
      { word: '拖拉机', tag: 'n' },
      { word: '学院', tag: 'n' },
      { word: '手扶拖拉机', tag: 'n' },
      { word: '专业', tag: 'n' },
      { word: '的', tag: 'uj' },
      { word: '。', tag: 'x' },
      { word: '不用', tag: 'v' },
      { word: '多久', tag: 'm' },
      { word: '，', tag: 'x' },
      { word: '我', tag: 'r' },
      { word: '就', tag: 'd' },
      { word: '会', tag: 'v' },
      { word: '升职', tag: 'v' },
      { word: '加薪', tag: 'nr' },
      { word: '，', tag: 'x' },
      { word: '当上', tag: 't' },
      { word: 'CEO', tag: 'eng' },
      { word: '，', tag: 'x' },
      { word: '走上', tag: 'v' },
      { word: '人生', tag: 'n' },
      { word: '巅峰', tag: 'n' },
      { word: '。', tag: 'x' } ]);
  });

  it('nodejieba.extract(sentence, 5)', function() {
    nodejieba.extract(sentence, 5).should.eql([
          {
              "weight": 11.739204307083542,
              "word": "CEO"
          },
          {
              "weight": 10.8561552143,
              "word": "升职"
          },
          {
              "weight": 10.642581114,
              "word": "加薪"
          },
          {
              "weight": 10.0088573539,
              "word": "手扶拖拉机"
          },
          {
              "weight": 9.49395840471,
              "word": "巅峰"
          }]);
  });

  it('nodejieba.cut("红掌拨清波")', function() {
    nodejieba.cut("红掌拨清波").should.eql([
      '红掌',
      '拨',
      '清波',
    ]);
  });

  it('nodejieba.cut("男默女泪")', function() {
    nodejieba.cut("男默女泪").should.eql([ '男', '默',
      '女', '泪' ]);
  });
  it('nodejieba.insertWord("男默女泪")', function() {
    nodejieba.insertWord("男默女泪").should.eql(true);
  });
  it('nodejieba.cut("男默女泪")', function() {
    nodejieba.cut("男默女泪").should.eql([ '男默女泪' ]);
  });

  it('nodejieba.cut("今天天气很好，🙋 我们去郊游。")', function() {
    nodejieba.cut("今天天气很好，🙋 我们去郊游。").should.eql([ '今天天气', '很', '好', '，', '🙋', ' ', '我们', '去', '郊游', '。' ]);
  });

  it('nodejieba.cutSmall("南京市长江大桥", 3)', function() {
    nodejieba.cutSmall("南京市长江大桥", 3).should.eql([ '南京市', 
    '长江',
    '大桥']);
  });

  it('nodejieba.cut("区块链")', function() {
    nodejieba.cut("区块链").should.eql(['区块链']);
  });
  it('nodejieba.tag("区块链")', function() {
    nodejieba.tag("区块链").should.eql([ { word: '区块链', tag: 'nz' }]);
  });
  it('nodejieba.cut("访问www.baidu.com进行搜索")',function(){
    nodejieba.cut("访问www.baidu.com进行搜索", true).should.eql([
        '访问', 'www', '.', 'baidu', '.', 'com', '进行', '搜索',
    ]);
  });
});
