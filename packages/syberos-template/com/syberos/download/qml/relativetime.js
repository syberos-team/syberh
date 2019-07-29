.pragma library

function timeSince(date) {
    var seconds = Math.floor(Math.max(0, (new Date() - date)) / 1000);
    return timeInterval(seconds);
}

function timeLeft(date) {
    var seconds = Math.floor(Math.max(0, (date - new Date())) / 1000);
    return timeInterval(seconds);
}

function timeFraction(date, total) {
    var seconds = Math.floor(Math.max(0, (date - new Date())) / 1000);
    return seconds / total;
}

function timeSinceObject(date) {
    var seconds = Math.floor(Math.max(0, (new Date() - date)) / 1000);
    return timeObject(seconds);
}

function timeLeftObject(date) {
    var seconds = Math.floor(Math.max(0, (date - new Date())) / 1000);
    return timeObject(seconds);
}

function timeObject(seconds) {
    var days = Math.floor(seconds / 86400);
    seconds -= (days * 86400);
    var hours = Math.floor(seconds / 3600);
    seconds -= (hours * 3600);
    var minutes = Math.floor(seconds / 60);
    seconds -= (minutes * 60);
    var time = {
        "days" : days,
        "hours" : hours,
        "minutes" : minutes,
        "seconds" : seconds
    };
    return time;
}

function timeInterval(seconds) {
    var intervalType;

    var interval = Math.floor(seconds / 31536000);
    if (interval >= 1) {
        intervalType = 'year';
    } else {
        interval = Math.floor(seconds / 2592000);
        if (interval >= 1) {
            intervalType = 'month';
        } else {
            interval = Math.floor(seconds / 86400);
            if (interval >= 1) {
                intervalType = 'day';
            } else {
                interval = Math.floor(seconds / 3600);
                if (interval >= 1) {
                    intervalType = "hour";
                } else {
                    interval = Math.floor(seconds / 60);
                    if (interval >= 1) {
                        intervalType = "min";
                    } else {
                        interval = seconds;
                        intervalType = "sec";
                    }
                }
            }
        }
    }

    if (interval > 1 || interval === 0) {
        intervalType += 's';
    }

    return interval + ' ' + intervalType;
}
