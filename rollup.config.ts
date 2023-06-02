import esbuild from "rollup-plugin-esbuild";
// @ts-ignore
import dts from "rollup-plugin-dts";

export default [
  {
    input: "./src/index.ts",
    output: [
      {
        file: "./dist/index.cjs",
        format: "cjs",
        sourcemap: true,
      },
      {
        file: "./dist/index.mjs",
        format: "esm",
        sourcemap: true,
      },
    ],
    plugins: [
      esbuild({
        charset: "utf8",
        minify: true,
        target: "node16",
      }),
    ],
    external: ["node:module", "node:path", "node:url", "@mapbox/node-pre-gyp"],
  },
  {
    input: "./src/index.ts",
    output: [
      {
        file: "./dist/index.d.ts",
        format: "esm",
        sourcemap: true,
      },
      {
        file: "./dist/index.d.cts",
        format: "esm",
        sourcemap: true,
      },
      {
        file: "./dist/index.d.mts",
        format: "esm",
        sourcemap: true,
      },
    ],
    plugins: [
      dts({
        compilerOptions: {
          preserveSymlinks: false,
        },
      }),
    ],
  },
];
