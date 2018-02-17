function approve(approver, resolve, reject) {
    setTimeout(function () {
        if (new Date().getMilliseconds() % 2 == 1) { //函数执行到这一行时的毫秒数是奇数时进入该条件分支
            // console.log("enter successful branch!")//此处可以加入若干代码用于异步执行
            resolve(`${approver}: agree`);
        } else {
            let r = ["内容不准确", "材料不全", "其它"];
            //...此处也可以加入若干代码用于异步执行
            reject(`${approver}: reject, reason is ${r[Math.trunc(Math.random()*r.length)]}`); // 最终产生随机值介于[0,2]之间，所以都是数组合理范围内
        }
    }, 1000);
}

console.log("prepare to submit...");

new Promise(function(resolve,reject){ //这里是把函数作为参数传入，这也是Promise语法规定，其参数resolver和reject是自动传入的，不需要多虑
    console.log("start process...");
    approve("处长", resolve, reject);
}) //function(resolver,reject)就是传入Promise的executor参数，JS随时牢记“函数是一等公民”

//以下的每个then分支都是顺序执行
.then(function(option){ //等上一个Promise的resolve通知，option就是resolve中传入参数
    console.log(option); //实际应用中，比如读取一个文件，读完后需要做什么操作可以放到这里
})

.then(function(){ //上一个then执行完毕后再创建一个Promise
    return new Promise(function(resolve,reject){
        approve("部长", resolve, reject);
    })
})

.then(function(value){//上一个Promise的resolve通知后执行次部，value就是resolve传入参数（可以写成value与上一个option不同，就是让大家知道这个名字可以随意）
    console.log(value);
    console.log("执行流程相应操作");
})

.catch(function(error){ //一旦进入reject分支就会直接进入此处 //无论几个Promise，被拒绝后总是寻找最近的一个catch执行
    console.log(error); //reject后有什么需要善后的可以在这里处理
    console.log("重新修改资料")
})

console.log("虽然这是在Promise后面的代码，但是在Promise创建后就执行，不用等到Promise的then或catch执行完毕，因为这就是异步");

//总结：NodeJs程序都是一个单线程进程，类似IO读写或者网络访问等待时间很长，如果采用同步逐行执行，这就意味着不能这些操作要等待
//             这将大大浪费效率，而异步则可以确保主进程继续执行下去，异步的归异步执行，互不干涉，从而避免等待阻塞