/**
 * 生成UUID
 */

function uuid(_length) {
  var leg = _length || 5

  return Number(
    Math.random()
      .toString()
      .substr(3, leg) + Date.now()
  ).toString(36)
  return uuid
}
