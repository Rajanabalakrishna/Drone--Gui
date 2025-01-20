import QtQuick 2.15
import QtQuick.Controls 2.15
import QtPositioning 5.15
import QtLocation 5.15

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: "Live Location"

    property string currentPosition: "Fetching location..."

    PositionSource {
        id: positionSource
        active: true
        updateInterval: 1000

        onPositionChanged: {
            currentPosition = "Lat: " + position.coordinate.latitude +
                              ", Lon: " + position.coordinate.longitude
        }

        onErrorOccurred: {
            currentPosition = "Error fetching location: " + errorString
        }
    }

    Column {
        anchors.centerIn: parent
        spacing: 20

        Text {
            text: parent.currentPosition
            font.pixelSize: 16
            horizontalAlignment: Text.AlignHCenter
        }

        Map {
            id: map
            width: parent.width * 0.9
            height: 300
            plugin: Plugin {
                name: "osm"
            }
            center: QtPositioning.coordinate(0, 0)
            zoomLevel: 15

            Component.onCompleted: {
                positionSource.start()
            }

            MapQuickItem {
                coordinate: QtPositioning.coordinate(
                    positionSource.position.coordinate.latitude,
                    positionSource.position.coordinate.longitude
                )
                anchorPoint.x: image.width / 2
                anchorPoint.y: image.height
                sourceItem: Image {
                    source: "marker.png"
                    width: 32
                    height: 32
                }
            }
        }
    }
}
