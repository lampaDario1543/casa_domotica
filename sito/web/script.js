isOn=true;
function cucina() {
    eel.cucina(isOn)(() => {
        isOn=!isOn;
        document.getElementById("cucina").style.backgroundColor = isOn? "green" : "red";
        //document.getElementById("heading").innerText = setdata; //imposta il testo con il testo ricevuto da python
    })
}
setInterval(function() {
    eel.getTemperature()(function(result) {
        var temperature = result[0];
        var humidity = result[1];
      document.getElementById("temperature").innerText = temperature;
      document.getElementById("humidity").innerText = humidity;
    })
  }, 1000);//richiede la temperatura ogni secondo