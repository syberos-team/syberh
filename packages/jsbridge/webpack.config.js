const pkg = require('./package.json');
const Webpack = require('webpack');
const Path = require('path');
const CopyWebpackPlugin = require('copy-webpack-plugin');

module.exports = {
  mode: 'production',
  devtool: false,
  entry: {
    syberh: Path.resolve(__dirname, './src/index.js'),
  },
  output: {
    path: Path.resolve(__dirname, './dist'),
    filename: '[name].min.js',
    library: 'syberh',
    libraryTarget: 'umd',
    umdNamedDefine: true,
  },
  module: {
    rules: [
      {
        test: /\.html$/,
        loader: 'html-loader?minimize=false',
      },
      {
        test: /\.js$/,
        loader: 'babel-loader',
      },
      {
        test: /\.less$/,
        loader: 'style-loader!css-loader!less-loader',
      },
    ],
  },
  stats: {
    colors: true,
  },
  plugins: [
    new Webpack.BannerPlugin(
      [
        `@syberos/jsbridge v${pkg.version} (${pkg.homepage})`,
        '',
        'YuanXin is pleased to support the open source community by making @syberos/jsbridge available.',
        'Copyright (C) 2019 THL A29 Limited, a Yuanxin company. All rights reserved.',
        'Licensed under the MIT License (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at',
        'http://opensource.org/licenses/MIT',
        'Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License.',
      ].join('\n'),
    ),
    new CopyWebpackPlugin([
      {
        // copy到cli/templates/default/lib/syberh.min.js
        from: Path.resolve(__dirname, './dist/syberh.min.js'),
        to: Path.join(
          Path.dirname(Path.resolve(__dirname)),
          'cli/templates/default/lib/syberh.min.js',
        ),
      },
      {
        from: Path.resolve(__dirname, './dist/syberh.min.js'),
        to: Path.join(
          Path.dirname(Path.resolve(__dirname)),
          'syberos/app/www/lib/syberh.min.js',
        ),
      },
    ]),
    new Webpack.DefinePlugin({
      'JVERSION': JSON.stringify(pkg.version)
    }),
  ],
};
