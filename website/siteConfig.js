/**
 * Copyright (c) 2017-present, Facebook, Inc.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

// See https://docusaurus.io/docs/site-config.html for all the possible
// site configuration options.

/* List of projects/orgs using your project for the users page */
const users = [
  {
    caption: '',
    // You will need to prepend the image path with your baseUrl
    // if it is not '/', like: '/test-site/img/docusaurus.svg'.
    image: 'img/syberos.png',
    infoLink: 'http://hdoc.syberos.com',
    pinned: true
  }
]

const siteConfig = {
  editUrl: 'http://github.com/syberos-team/syberos-hybrid/edit/master/docs/',
  title: 'SyberOS Hybrid' /* title for your website */,
  tagline: 'SyberOS的 快速混合开发框架，助力SyberOS 应用生态。',
  url: 'http://hdoc.syberos.com' /* your website url */,
  baseUrl: '/' /* base url for your project */,
  // For github.io type URLs, you would set the url and baseUrl like:
  //   url: 'https://facebook.github.io',
  //   baseUrl: '/test-site/',

  // Used for publishing and more
  projectName: 'HybridDocs',
  organizationName: 'YuanXin',
  // For top-level user or org sites, the organization is still the same.
  // e.g., for the https://JoelMarcey.github.io site, it would be set like...
  //   organizationName: 'JoelMarcey'

  // For no header links in the top nav bar -> headerLinks: [],
  headerLinks: [
    { doc: 'README', label: '文档' },
    // { doc: 'components-desc', label: '组件库' },
    { doc: 'apis/about/desc', label: 'API' },
    { href: 'https://github.com/syberos-team/syberos-hybrid', label: 'GitHub' },
    { search: true }
  ],

  algolia: {
    apiKey: '64b6b45fe3daab30513f5da83fffd3a5',
    indexName: 'syberos-hybrid'
  },

  // If you have users set above, you add it here:
  users,

  /* path to images for header/footer */
  headerIcon: 'img/syberos.png',
  footerIcon: 'img/syberos.png',
  favicon: 'img/syberos.png',

  /* colors for website */
  colors: {
    primaryColor: 'rgb(40, 43, 46)',
    secondaryColor: '#4a72ea'
  },

  /* custom fonts for website */
  /* fonts: {
    myFont: [
      "Times New Roman",
      "Serif"
    ],
    myOtherFont: [
      "-apple-system",
      "system-ui"
    ]
  }, */

  // This copyright info is used in /core/Footer.js and blog rss/atom feeds.
  copyright: 'Copyright © ' + new Date().getFullYear() + ' ltp11',

  highlight: {
    // Highlight.js theme to use for syntax highlighting in code blocks
    theme: 'tomorrow-night-blue'
  },

  usePrism: true,

  // Add custom scripts here that would be placed in <script> tags
  scripts: ['https://buttons.github.io/buttons.js'],

  /* On page navigation for the current documentation page */
  onPageNav: 'separate',

  /* Open Graph and Twitter card images */
  ogImage: 'img/syberos.png',
  twitterImage: 'img/syberos.png',

  scrollToTop: true,
  docsSideNavCollapsible: true

  // You may provide arbitrary config keys to be used as needed by your
  // template. For example, if you need your repo's URL...
  //   repoUrl: 'https://github.com/facebook/test-site',
}

module.exports = siteConfig
