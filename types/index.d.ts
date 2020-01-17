declare module "nodejieba" {
  export interface LoadOptions {
    dict?: string;
    hmmDict?: string;
    userDict?: string;
    idfDict?: string;
    stopWordDict?: string;
  }
  
  export interface TagResult {
    word: string;
    tag: string;
  }
  
  export interface ExtractResult {
    word: string;
    weight: number;
  }

  export function load(dict?: LoadOptions): void;
  export function cut(sentence: string, strict?: boolean): string[];
  export function cutHMM(sentence: string): string[];
  export function cutAll(sentence: string): string[];
  export function cutForSearch(sentence: string, strict?: boolean): string[];
  export function tag(sentence: string): TagResult[];
  export function extract(sentence: string, threshold: number): ExtractResult[];
  export function insertWord(sentence: string): boolean;
  export function cutSmall(sentence: string, small: number): boolean;
}
