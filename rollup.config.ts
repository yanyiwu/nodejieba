import esbuild from "rollup-plugin-esbuild";
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
        target: "node18",
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
