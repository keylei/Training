import { Component, OnInit } from '@angular/core';

declare var echarts: any;

@Component({
  selector: 'app-chart',
  templateUrl: './chart.component.html',
  styleUrls: ['./chart.component.css']
})
// export class ChartComponent implements OnInit {
//   options: any;

//   constructor() { }

//   ngOnInit() {
//     const xAxisData = [];
//     const data1 = [];
//     const data2 = [];

//     for (let i = 0; i < 100; i++) {
//       xAxisData.push('category' + i);
//       data1.push((Math.sin(i / 5) * (i / 5 - 10) + i / 6) * 5);
//       data2.push((Math.cos(i / 5) * (i / 5 - 10) + i / 6) * 5);
//     }

//     this.options = {
//       legend: {
//         data: ['bar', 'bar2'],
//         align: 'left'
//       },
//       tooltip: {},
//       xAxis: {
//         data: xAxisData,
//         silent: false,
//         splitLine: {
//           show: false
//         }
//       },
//       yAxis: {
//       },
//       series: [{
//         name: 'bar',
//         type: 'bar',
//         data: data1,
//         animationDelay: function (idx) {
//           return idx * 10;
//         }
//       }, {
//         name: 'bar2',
//         type: 'bar',
//         data: data2,
//         animationDelay: function (idx) {
//           return idx * 10 + 100;
//         }
//       }],
//       animationEasing: 'elasticOut',
//       animationvUpdate: function (idx) {
//         return idx * 5;
//       }
//     };
//   }
// }

export class ChartComponent implements OnInit {
  options: any;
  isLoading = true;

  constructor() { }

  ngOnInit() {

    setTimeout(() => { this.isLoading = false; }, 5000);

    const dataAxis = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T'];
    const data = [220, 182, 191, 234, 290, 330, 310, 123, 442, 321, 90, 149, 210, 122, 133, 334, 198, 123, 125, 220];
    const yMax = 500;
    const dataShadow = [];

    for (let i = 0; i < data.length; i++) {
      dataShadow.push(yMax);
    }

    this.options = {
      title: {
        text: 'Check Console for Events'
      },
      xAxis: {
        data: dataAxis,
        axisLabel: {
          inside: true,
          textStyle: {
            color: '#fff'
          }
        },
        axisTick: {
          show: false
        },
        axisLine: {
          show: false
        },
        z: 10
      },
      yAxis: {
        axisLine: {
          show: false
        },
        axisTick: {
          show: false
        },
        axisLabel: {
          textStyle: {
            color: '#999'
          }
        }
      },
      dataZoom: [
        {
          type: 'inside'
        }
      ],
      series: [
        { // For shadow
          type: 'bar',
          itemStyle: {
            normal: { color: 'rgba(0,0,0,0.05)' }
          },
          barGap: '-100%',
          barCategoryGap: '40%',
          data: dataShadow,
          animation: false
        },
        {
          type: 'bar',
          itemStyle: {
            normal: {
              color: new echarts.graphic.LinearGradient(
                0, 0, 0, 1,
                [
                  { offset: 0, color: '#83bff6' },
                  { offset: 0.5, color: '#188df0' },
                  { offset: 1, color: '#188df0' }
                ]
              )
            },
            emphasis: {
              color: new echarts.graphic.LinearGradient(
                0, 0, 0, 1,
                [
                  { offset: 0, color: '#2378f7' },
                  { offset: 0.7, color: '#2378f7' },
                  { offset: 1, color: '#83bff6' }
                ]
              )
            }
          },
          data: data
        }
      ]
    };
  }

  onChartEvent(event: any, type: string) {
    console.log('chart event:', type, event);
  }
}


