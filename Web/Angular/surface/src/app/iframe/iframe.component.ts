import { Component, Input, ViewChild, ElementRef, HostListener, OnInit } from '@angular/core';

@Component({
  selector: 'app-iframe',
  templateUrl: './iframe.component.html',
  styleUrls: ['./iframe.component.css']
})
export class IframeComponent implements OnInit {
  @Input() src: string;
  @ViewChild('frame') frameElement: ElementRef;

  containerMinWidth = 0;
  containerMinHeight = 0;
  containerWidth: number = this.containerMinWidth;
  containerHeight: number = this.containerMinHeight;

  ngOnInit() {
    this.onResize(window.innerWidth, window.innerHeight);
  }

  @HostListener('window:resize', ['$event.target.innerWidth', '$event.target.innerHeight'])
  onResize(width: number, height: number): void {
    const top = this.frameElement.nativeElement.offsetTop;
    const left = this.frameElement.nativeElement.offsetLeft;

    this.containerWidth = Math.max(width - left, this.containerMinWidth);
    this.containerHeight = Math.max(height - top, this.containerMinHeight);
  }
}
