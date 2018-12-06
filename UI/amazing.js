let urlmean = "https://api.particle.io/v1/devices/3c0063001051363036373538/mean?access_token=4dd7ab61aec7c8fe550071f985a66a124d2773a8"
let urlrecent = "https://api.particle.io/v1/devices/3c0063001051363036373538/recent?access_token=4dd7ab61aec7c8fe550071f985a66a124d2773a8"
let urlrange = "https://api.particle.io/v1/devices/3c0063001051363036373538/range?access_token=4dd7ab61aec7c8fe550071f985a66a124d2773a8"
let urlvalues = "https://api.particle.io/v1/devices/3c0063001051363036373538/values?access_token=4dd7ab61aec7c8fe550071f985a66a124d2773a8"

function controlLED(){
  console.log(urlvalues);
var xmlHttp = new XMLHttpRequest();
xmlHttp.open( "GET", urlmean, false ); // false for synchronous request
xmlHttp.send( null );
var obj = JSON.parse(xmlHttp.responseText)
console.log(obj.result)
document.getElementById("mean").innerHTML = obj.result

var xmlHttprecent = new XMLHttpRequest();
xmlHttprecent.open( "GET", urlrecent, false ); // false for synchronous request
xmlHttprecent.send( null );
var obj1 = JSON.parse(xmlHttprecent.responseText)
document.getElementById("recent").innerHTML = obj1.result

var xmlHttprange = new XMLHttpRequest();
xmlHttprange.open( "GET", urlrange, false ); // false for synchronous request
xmlHttprange.send( null );
var obj2 = JSON.parse(xmlHttprange.responseText)
console.log(obj.result)
document.getElementById("range").innerHTML = obj2.result
}

let url = "https://api.particle.io/v1/devices/3c0063001051363036373538/resetStat"

function reset(){

  let xhttp = new XMLHttpRequest()
  xhttp.open("POST", url, true)
  xhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
  xhttp.send("access_token=" + "4dd7ab61aec7c8fe550071f985a66a124d2773a8")
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      let resp = JSON.parse(this.responseText)
      controlLED();
    }
  }
}

let urlroll = "https://api.particle.io/v1/devices/3c0063001051363036373538/rollback"

function roll(){
  let xhttp = new XMLHttpRequest()
  xhttp.open("POST", urlroll, true)
  xhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
  xhttp.send("access_token=" + "4dd7ab61aec7c8fe550071f985a66a124d2773a8")
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      let resp = JSON.parse(this.responseText)
      controlLED();
    }
  }
}
