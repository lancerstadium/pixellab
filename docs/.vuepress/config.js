import { viteBundler } from '@vuepress/bundler-vite'
import { defaultTheme } from '@vuepress/theme-default'
import { defineUserConfig } from 'vuepress'


export default defineUserConfig({
    bundler: viteBundler(),
    theme: defaultTheme({
        navbar: [
            { text: '主页', link: '/' },
            { text: '教程', link: '/pages/tutorial/' },
            { text: '博客', link: '/pages/blog/' },
            { text: '关于', link: '/pages/about/' },
        ],
        sidebar: 'auto',
    }),

    lang: 'zh-CN',
    title: 'Pixel Lab',
    base: '/pixellab/',
    description: 'Pixel Lab Website',
})
