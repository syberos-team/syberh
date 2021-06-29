import QtQuick 2.3
import com.syberos.basewidgets 2.0
import com.syberos.multimedia.photos 2.1
import com.syberos.photos.extension 1.0

CEditGridViewPage {
    id: albumPage

    property Item parentItem

    signal selected(var files)
    signal cancelled()

    Component {
        id: previewPage
        CPreviewPage {
            toolButtonNames: []
        }
    }

    onClicked: {
        if(!albumPage.editing){
            pageStack.push(previewPage, {'model': albumPage.model, 'currentIndex': index});
        }
    }

    onToolButtonClicked: {
        if(index < 0 || albumPage.selectedCount <= 0){
            return
        }
        var filesPath = [];
        for(var i in albumPage.selectedIndexes){
            var data = model.get(albumPage.selectedIndexes[i]);
            if(data){
                filesPath.push(infoTools.urlToLocalFile(data.url));
            }
        }
        if(filesPath.length > 0){
            selected(filesPath);
            pageStack.pop();
        }
    }


    Component.onDestruction: {
        cancelled();
    }
}
