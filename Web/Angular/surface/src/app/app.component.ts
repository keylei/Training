import { Component } from '@angular/core';
import { DomSanitizer, SafeResourceUrl } from '@angular/platform-browser';


@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent {
  frameUrl: SafeResourceUrl;

  constructor(private sanitizer: DomSanitizer) {
    const url = '../assets/sphere-parametric-surface.html';

    // 只有不同的域名才需要这个
    this.frameUrl = this.sanitizer.bypassSecurityTrustHtml(url);
  }

}
