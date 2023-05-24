states=[] //stati dei vari bottoni e range.
function init(){
  getTemperature();
  setTimeout(() => {
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
  }, 1000);
}
init();
function setStatus(room){
  eel.setStatus(room); //call python function
}
function getTemperature() {
  eel.getTemperature()(function(result) {
      var temperature = result[0];
      var humidity = result[1];
    document.getElementById("temperature").innerText = temperature;
    document.getElementById("humidity").innerText = humidity;
  })
}
setInterval(getTemperature, 5000);//richiede la temperatura ogni 5 secondi

function getBasculante(){
  $("#submit-button").prop('disabled', true);
  const slider=document.getElementById("basculante-slider");
  eel.setBasculante(slider.value);
  setTimeout(() => {
    $("#submit-button").prop('disabled', false);
  }, 5000);
}