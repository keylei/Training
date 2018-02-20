import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
import { NgxEchartsModule } from 'ngx-echarts';

import { AppComponent } from './app.component';
import { ChartComponent } from './chart/chart.component';
import { ThemeComponent } from './theme/theme.component';
import { UpdateChartComponent } from './update-chart/update-chart.component';


@NgModule({
  declarations: [
    AppComponent,
    ChartComponent,
    ThemeComponent,
    UpdateChartComponent
  ],
  imports: [
    BrowserModule,
    NgxEchartsModule
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }
