import { defineUserConfig } from "vuepress";
import theme from "./theme.js";

export default defineUserConfig({
  base: "/pixellab/",

  lang: "zh-CN",
  title: "Pixel Lab",
  description: "Pixel Lab Website",

  theme,

  // 和 PWA 一起启用
  // shouldPrefetch: false,
});
