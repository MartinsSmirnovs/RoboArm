import { Component, OnInit } from '@angular/core';
import { Bluetooth } from 'nativescript-bluetooth';
import { ActivatedRoute } from "@angular/router";

@Component({
  selector: 'ns-bt-page',
  templateUrl: './bt-page.component.html',
  styleUrls: ['./bt-page.component.css'],
  moduleId: module.id,
})
export class BtPageComponent implements OnInit {

  tapped = "false";
  public backParam: string;
  constructor(
      private bluetooth: Bluetooth,
      private route: ActivatedRoute
    ){
        this.route.params.subscribe((params)=>{
            this.backParam = params["backParam"]
        })
    }

  ngOnInit(): void {
  }

  checkBT(){
    this.bluetooth.isBluetoothEnabled().then(
        enabled => this.tapped = enabled.toString()
      );
  }


}
