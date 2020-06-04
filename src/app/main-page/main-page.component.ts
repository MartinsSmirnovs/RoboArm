import { Component, OnInit } from '@angular/core';
import { RadSideDrawer } from "nativescript-ui-sidedrawer";
import { sliders } from "../sliders";

@Component({
  selector: 'ns-main-page',
  templateUrl: './main-page.component.html',
  styleUrls: ['./main-page.component.css'],
  moduleId: module.id,
})

export class MainPageComponent implements OnInit {
  constructor() {}
  slider = sliders;
  ngOnInit(): void {

  }

  openDrawer(){
    const sideDrawer = new RadSideDrawer;
    sideDrawer.showDrawer();
  }


}
