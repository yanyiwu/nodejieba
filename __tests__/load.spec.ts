import { resolve } from "node:path";
import { expect, it } from "vitest";

import { cut, load } from "../src/index.js";

load({
  userDict: resolve(__dirname, "./__fixtures__/userdict.utf8"),
});

it("load", () => {
  expect(cut("红掌拨清波")).toEqual(["红掌拨清波"]);
});
