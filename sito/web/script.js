states=[]
function init(){ //inizializza le varibili boolean facendo una richesta tramite python ad arduino, dello stato dei LED
  eel.getAllStates()(function(result) {
    console.log(result);
    states[0]={room:"cucina",state:result[0]};
    states[1]={room:"bagno",state:result[1]};
    states[2]={room:"camera",state:result[2]};
    states[3]={room:"garage",state:result[3]};
    for(let i=0;i<states.length;i++){
      if(states[i].state==true){
        $("#"+states[i].room+"-switch").prop('checked', true);
      }
      else{
        $("#"+states[i].room+"-switch").prop('checked', false);
      }
    }
  })
  setInterval(function() {
    eel.getTemperature()(function(result) {
        var temperature = result[0];
        var humidity = result[1];
      document.getElementById("temperature").innerText = temperature;
      document.getElementById("humidity").innerText = humidity;
    })
  }, 1000);//richiede la temperatura ogni secondo
}
init();
function setStatus(room){ //cambia lo stato dei LED
  eel.setStatus(room); //call python function
}