import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import Qt.labs.platform 1.1
import com.example 1.0


ApplicationWindow {
    visible: true
    width: 800
    height: 600
    title: "Image Viewer"

    ListModel {
        id: imageModel
    }

    ImageFetcher {
        id: fetcher
    }

    StackView {
        id: stackView
        anchors.fill: parent

        Component.onCompleted: {
            push(folderChooser.createObject(null, {"width": width, "height": height}));
        }
    }

    Component {
        id: folderChooser
        Rectangle {
            ColumnLayout {
                spacing: 10
                anchors.centerIn: parent

                FolderDialog {
                    id: folderDialog
                    onAccepted: {
                        console.log("Selected folder: " + folderDialog.folder);
                        loadImages(folderDialog.folder);
                        // On successful load, push the next view
                        stackView.push(imageChoiceView.createObject(null, {"width": stackView.width, "height": stackView.height}));
                    }
                }

                Button {
                    text: "Choose Image Folder"
                    onClicked: folderDialog.open()
                }
            }
        }
    }

    Component {
        id: imageChoiceView
        Rectangle {
            ColumnLayout {
                spacing: 10
                anchors.centerIn: parent

                Button {
                    text: "List View"
                    onClicked: stackView.push(imageListView.createObject(null, {"width": stackView.width, "height": stackView.height}))
                }

                Button {
                    text: "Grid View"
                    onClicked: stackView.push(imageGridView.createObject(null, {"width": stackView.width, "height": stackView.height}))
                }

                Button {
                    text: "Path View"
                    onClicked: stackView.push(imagePathView.createObject(null, {"width": stackView.width, "height": stackView.height}))
                }

                Button {
                    text: "Exit"
                    onClicked: Qt.quit()
                }
            }
        }
    }

    function loadImages(folder) {
        console.log("Loading images from folder: " + folder);
        imageModel.clear();
        var imageFiles = fetcher.getImageList(folder.toString());
        for (var i = 0; i < imageFiles.length; ++i) {
            imageModel.append({ "imagePath": "file:///" + imageFiles[i] });
        }
    }

    Component {
        id: imageListView
        ListView {
            model: imageModel
            delegate: imageDelegate
        }
    }

    Component {
        id: imageGridView
        GridView {
            model: imageModel
            delegate: imageDelegate
            cellWidth: 100
            cellHeight: 100
        }
    }

    Component {
        id: imagePathView
        PathView {
            model: imageModel
            delegate: imageDelegate
            pathItemCount: imageModel.count
            preferredHighlightBegin: 0.5
            preferredHighlightEnd: 0.5
            highlightRangeMode: PathView.StrictlyEnforceRange
            path: Path {
                startX: PathView.position * (width / (imageModel.count - 1))
                PathAttribute { name: "iconScale"; value: 0.1 }
                PathLine{x: width; y: height/2}
            }
        }
    }



    Component {
        id: imageDelegate
        Rectangle {
            width: 100
            height: 100

            Image {
                anchors.fill: parent
                source: imagePath
                fillMode: Image.PreserveAspectFit
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    var view = imageViewer.createObject(stackView, { "imagePath": model.imagePath }); // Change this line
                    stackView.push(view);
                }
            }
        }
    }

    Component {
        id: imageViewer
        Rectangle {
            Image {
                source: imagePath
                anchors.fill: parent
                fillMode: Image.PreserveAspectFit
            }

            property string imagePath

            Button {
                text: "Back"
                anchors {
                    top: parent.top
                    right: parent.right
                }
                onClicked: stackView.pop()
            }
        }
    }
}
