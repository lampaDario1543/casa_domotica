function setStatus(room){
  eel.setStatus(room); //call python function
}
setInterval(function() {
  eel.getTemperature()(function(result) {
      var temperature = result[0];
      var humidity = result[1];
    document.getElementById("temperature").innerText = temperature;
    document.getElementById("humidity").innerText = humidity;
  })
}, 1000);//richiede la temperatura ogni secondo