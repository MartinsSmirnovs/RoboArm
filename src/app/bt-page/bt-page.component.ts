import { Component, OnInit } from "@angular/core";
import { Bluetooth } from "nativescript-bluetooth";
import { ActivatedRoute } from "@angular/router";

@Component({
    selector: "ns-bt-page",
    templateUrl: "./bt-page.component.html",
    styleUrls: ["./bt-page.component.css"],
    moduleId: module.id,
})
export class BtPageComponent implements OnInit {
    btColor = "red"; //shows if bt is connected to device
    btDeviceName = "Not connected";
    //   tapped = "false";
    public backParam: string;
    constructor(private bluetooth: Bluetooth, private route: ActivatedRoute) {
        this.route.params.subscribe((params) => {
            this.backParam = params["backParam"];
        });
    }

    ngOnInit(): void {
        this.checkBTEnabled();
    }

    checkBTEnabled() {
        // this.bluetooth.isBluetoothEnabled().then( //checks if bluetooth is enabled and shows green or led color
        //   enabled => {
        //       if(enabled){
        //         this.btColor="green";
        //         return true;
        //       }
        //       else {
        //         this.btColor="red";
        //         return false;
        //       }
        //     }
        // );
    }

    scanNConnect() {
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
                        );
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
                    this.btColor = "green";
                    console.log(
                        "Periperhal connected with UUID: " + peripheral.UUID
                    );
                    this.btDeviceName = peripheral.name;
                },
                onDisconnected: function (peripheral) {
                    this.btColor = "red";
                    console.log(
                        "Periperhal disconnected with UUID: " + peripheral.UUID
                    );
                    this.btDeviceName = "Not connected";
                },
            });
        } else {
            this.btDeviceName = "Bluetooth is not enabled!";
        }
    }
}
