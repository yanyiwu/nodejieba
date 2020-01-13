declare module "nodejieba" {
  export function load(dict: object): void;
  export function cut(sentence: string, strict?: boolean): any;
  export function cutHMM(sentence: string): any;
  export function cutAll(sentence: string): any;
  export function cutForSearch(sentence: string, strict?: boolean): any;
  export function tag(sentence: string): any;
  export function extract(sentence: string, threshold: number): any;
  export function insertWord(sentence: string): any;
  export function cutSmall(sentence: string, small: number): any;
}
