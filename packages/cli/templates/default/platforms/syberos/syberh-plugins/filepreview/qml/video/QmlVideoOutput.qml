/*!
 * Author: Mengcong
 * Date: 2013.11.21
 * Details: Player engine.
 */

import QtQuick 2.0
import QtMultimedia 5.0

Rectangle {
    id: player
    //signal endOfStream
    color: "black"
    property MediaPlayer sourceMedia

    function switchFillMode() {
        if(videoOutput.fillMode === VideoOutput.PreserveAspectFit) {
            videoOutput.fillMode = VideoOutput.Stretch
        } else {
            videoOutput.fillMode = VideoOutput.PreserveAspectFit
        }
    }

    function setFillMode(value) {
        if (value > 0) {
            console.log("stretch")
            videoOutput.fillMode = VideoOutput.Stretch
        } else {
            console.log("Fit")
            videoOutput.fillMode = VideoOutput.PreserveAspectFit
        }
    }

    VideoOutput {
        id: videoOutput

        source: sourceMedia
        anchors.fill: parent
        fillMode: VideoOutput.PreserveAspectFit
    }

}
