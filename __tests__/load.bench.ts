import { dirname, resolve } from "node:path";
import { fileURLToPath } from "node:url";
import { bench } from "vitest";

import { load } from "../src/index.js";

const __dirname = dirname(fileURLToPath(import.meta.url));

bench("load", () => {
  load({
    userDict: resolve(__dirname, "./__fixtures__/userdict.utf8"),
  });
});
