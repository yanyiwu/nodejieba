import { describe, bench } from "vitest";

import {
  cut,
  cutAll,
  cutForSearch,
  cutHMM,
  cutSmall,
  insertWord,
  tag,
  extract,
  textRankExtract,
} from "../src/index.js";

const sentence =
  "我是拖拉机学院手扶拖拉机专业的。不用多久，我就会升职加薪，当上CEO，走上人生巅峰。";
const topN = 5;

describe("nodejieba", () => {
  bench("cut", () => {
    cut(sentence);
  });
  bench("cut#strict", () => {
    cut(sentence, true);
  });

  bench("cutHMM", () => {
    cutHMM(sentence);
  });

  bench("cutAll", () => {
    cutAll(sentence);
  });

  bench("cutSmall#2", () => {
    cutSmall("南京市长江大桥", 2);
  });
  bench("cutSmall#3", () => {
    cutSmall("南京市长江大桥", 3);
  });
  bench("cutSmall#4", () => {
    cutSmall("南京市长江大桥", 4);
  });

  bench("cutForSearch", () => {
    cutForSearch(sentence);
  });

  bench("tag", () => {
    tag(sentence);
  });

  bench("extract", () => {
    extract(sentence, topN);
  });

  bench("textRankExtract", () => {
    textRankExtract(sentence, topN);
  });

  bench("insertWord", () => {
    insertWord("男默女泪");
  });
});
