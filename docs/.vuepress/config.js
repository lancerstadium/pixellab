import { viteBundler } from '@vuepress/bundler-vite'
import { defaultTheme } from '@vuepress/theme-default'
import { defineUserConfig } from 'vuepress'


export default defineUserConfig({
    bundler: viteBundler(),
    theme: defaultTheme(),

    lang: 'zh-CN',
    title: 'Pixel Lab',
    base: '/pixellab/' ,
    description: 'Pixel Lab Website',
})
