import { Injectable } from '@angular/core';
import { Bluetooth } from "nativescript-bluetooth";

@Injectable({
  providedIn: 'root'
})
export class BtService {

  constructor(private bluetooth: Bluetooth) { }
  connected = false;
  btColor = "red"; //shows if bt is connected to device
  btDeviceName = "Not connected";
  lastSentString = "None";

  showBTEnabled() { //shows color if device is connected
    if (this.connected) this.btColor = "green";
    else this.btColor = "red";
}

disconnectBT() { //disconnects from bluetooth
    this.bluetooth
        .disconnect({
            UUID: "3C:71:BF:9D:1D:5E",
        })
        .then(
            function () {
                this.btDeviceName = "Not connected"; //shows that device is not connected
                this.connected = false;
                this.showBTEnabled();
            }.bind(this)
        );
}

scanNConnect() {//scans bluetooth and connects to bluetooth module
    if (this.bluetooth.isBluetoothEnabled()) {
        this.bluetooth
            .startScanning({
                // serviceUUIDs: "38:01:95:01:0A:71",
                seconds: 4,
                onDiscovered: function (peripheral) {
                    console.log(
                        "Periperhal found with UUID: " +
                            peripheral.UUID +
                            " and name: " +
                            peripheral.name
                    ); // the peripheral object now has a list of available services:
                },
                skipPermissionCheck: false,
            })
            .then(
                function () {
                    console.log("scanning complete");
                },
                function (err) {
                    console.log("error while scanning: " + err);
                }
            );

        this.bluetooth.connect({
            UUID: "3C:71:BF:9D:1D:5E",
            onConnected: function (peripheral) {
                this.bluetooth.stopScanning(); //stops scanning if connected to device
                console.log(
                    "Periperhal connected with UUID: " + peripheral.UUID
                );

                // LISTS ALL SERVICES OF CONNECTED DEVICE
                // peripheral.services.forEach(function (service) {
                //     console.log(
                //         "service found: " + JSON.stringify(service)
                //     );
                //     console.log();
                // });

                this.btDeviceName = peripheral.name; //shows device name
                this.connected = true;
                this.showBTEnabled(); //shows color if connected
            }.bind(this), //enables accessing to this inside of Promise
            onDisconnected: function (peripheral) {
                console.log(
                    "Periperhal disconnected with UUID: " + peripheral.UUID
                );
                this.btDeviceName = "Not connected"; //shows that device is not connected
                this.connected = false;
                this.showBTEnabled();
            }.bind(this), //enables accessing to this inside of Promise
        });
    } else {
        this.btDeviceName = "Bluetooth is not enabled!";
    }
}

sendBTData(dataToSend) { //sends bluetooth data
    if (this.connected) {
        this.bluetooth
            .write({
                peripheralUUID: "3C:71:BF:9D:1D:5E", //peripheral UUID
                serviceUUID: "4fafc201-1fb5-459e-8fcc-c5c9c331914b", //service UUID inside characteristics
                characteristicUUID: "beb5483e-36e1-4688-b7f5-ea07361b26a8", //UUID inside characteristics
                value: dataToSend, // can be a string
            })
            .then(
                function (result) {
                    console.log("value written ");
                    this.lastSentString = dataToSend;
                }.bind(this),
                function (err) {
                    console.log("write error: " + err);
                }
            );
    } else {
        return false;
    }
}
}
