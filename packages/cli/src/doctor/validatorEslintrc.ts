module.exports = {
  'extends': ['syberh'],
  'rules': {
    'no-unused-vars': ['error', { 'varsIgnorePattern': 'syberh' }],
    'react/jsx-filename-extension': [1, { 'extensions': ['.js', '.jsx', '.tsx'] }]
  },
  'parser': 'babel-eslint',
  'plugins': ['typescript']
}
