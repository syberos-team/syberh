/* eslint-disable no-unused-vars */

function getFileName(filePath) {
  if(!filePath){
    return ''
  }
  return filePath.substring(filePath.lastIndexOf("/")+1, filePath.length);
}

function getFileNameNoSuffix(filePath) {
  var fileName = getFileName(filePath);
  if (fileName.indexOf(".") < 0) {
      return fileName;
  } else {
      return fileName.substring(0, fileName.lastIndexOf("."));
  }
}
