const pkg = require('./package.json')
const Webpack = require('webpack')
const Path = require('path')
const CopyWebpackPlugin = require('copy-webpack-plugin')

module.exports = {
  mode: 'production',
  devtool: false,
  entry: {
    syberos: Path.resolve(__dirname, './src/syber.js')
  },
  output: {
    path: Path.resolve(__dirname, '../dist'),
    filename: '[name].js',
    libraryTarget: 'umd',
    umdNamedDefine: true
  },
  module: {
    rules: [
      {
        test: /\.html$/,
        loader: 'html-loader?minimize=false'
      },
      {
        test: /\.js$/,
        loader: 'babel-loader'
      },
      {
        test: /\.less$/,
        loader: 'style-loader!css-loader!less-loader'
      }
    ]
  },
  stats: {
    colors: true
  },
  plugins: []
}
