module.exports = {
  extends: ['standard', 'standard-jsx'],
  env: {
    browser: true,
    node: true,
    es6: true,
    jest: true
  },
  rules: {
    'no-unused-expressions': 0,
    'no-useless-constructor': 0
  },
  settings: {

  },
  parser: 'babel-eslint'
}
