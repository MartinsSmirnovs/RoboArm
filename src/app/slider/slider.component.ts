import { ActivatedRoute } from '@angular/router';
import { Component, OnInit } from "@angular/core";
import { sliders } from "../sliders";

@Component({
    selector: "ns-slider",
    templateUrl: "./slider.component.html",
    styleUrls: ["./slider.component.css"],
    moduleId: module.id,
})
export class SliderComponent implements OnInit {
    slider = sliders;

    constructor(private route: ActivatedRoute) {}

    ngOnInit(): void {
        // this.route.paramMap.subscribe( params =>{
        //     this.slider = sliders[+params.get('id')];
        // }
        // );
    }
}
