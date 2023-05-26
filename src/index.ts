import { createRequire } from "node:module";
import { dirname, resolve } from "node:path";
import { fileURLToPath } from "node:url";

// @ts-ignore
import binary from "@mapbox/node-pre-gyp";

const __dirname = dirname(fileURLToPath(import.meta.url));
const bindingPath = binary.find(resolve(__dirname, "../package.json"));

const require = createRequire(import.meta.url);
const nodejieba: Record<
  string,
  (...args: unknown[]) => unknown
> = require(bindingPath);

let isDictLoaded = false;

export const DEFAULT_DICT = resolve(__dirname, "../dict/jieba.dict.utf8");
export const DEFAULT_HMM_DICT = resolve(__dirname, "../dict/hmm_model.utf8");
export const DEFAULT_USER_DICT = resolve(__dirname, "../dict/user.dict.utf8");
export const DEFAULT_IDF_DICT = resolve(__dirname, "../dict/idf.utf8");
export const DEFAULT_STOP_WORD_DICT = resolve(
  __dirname,
  "../dict/stop_words.utf8"
);

export interface LoadOptions {
  dict?: string;
  hmmDict?: string;
  userDict?: string;
  idfDict?: string;
  stopWordDict?: string;
}

export const load = ({
  dict = DEFAULT_DICT,
  hmmDict = DEFAULT_HMM_DICT,
  userDict = DEFAULT_USER_DICT,
  idfDict = DEFAULT_IDF_DICT,
  stopWordDict = DEFAULT_STOP_WORD_DICT,
}: LoadOptions = {}): void => {
  isDictLoaded = true;

  return <void>nodejieba.load(dict, hmmDict, userDict, idfDict, stopWordDict);
};

const wrapper = <T = unknown>(name: string, ...args: any[]): T => {
  if (!isDictLoaded) load();

  return <T>nodejieba[name].apply(this, args);
};

export const cut = (content: string, strict = false): string[] =>
  wrapper("cut", content, strict);
export const cutAll = (content: string): string[] => wrapper("cutAll", content);
export const cutHMM = (content: string): string[] => wrapper("cutHMM", content);
export const cutForSearch = (content: string, strict = false): string[] =>
  wrapper("cutForSearch", content, strict);
export const cutSmall = (content: string, limit: number): string[] =>
  wrapper("cutSmall", content, limit);

export interface TagResult {
  word: string;
  tag: string;
}

export const tag = (content: string): TagResult[] => wrapper("tag", content);

export const insertWord = (word: string): boolean =>
  wrapper("insertWord", word);

export interface ExtractResult {
  word: string;
  weight: number;
}

export const extract = (content: string, threshold: number): ExtractResult[] =>
  wrapper("extract", content, threshold);
export const textRankExtract = (
  content: string,
  threshold: number
): ExtractResult[] => wrapper("textRankExtract", content, threshold);
