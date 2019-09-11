function getSizeStr(bytes) {
    var unit = ["B", "KB", "MB", "GB", "TB"]
    var i = 0
    if (bytes < 0) {
        print("bytes wrong: ", bytes)
        return "0"
    }

    while(bytes>1024 && i<unit.length) {
        bytes /= 1024.0
        i++
        //str = Number(bytes).toPrecision(4) + unit[i]
    }

    var precision = bytes >= 1000 ? 4 : 3
    return Number(bytes).toPrecision(precision) + unit[i]
}

function getDir(filePath) {
    if (filePath === "")
        return "";
    else
        return filePath.substr(0, filePath.lastIndexOf('/'));
}
