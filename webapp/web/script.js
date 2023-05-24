states=[] //stati dei vari bottoni e range.
function init(){
  getTemperature();
  setTimeout(() => {
    eel.getAllStates()(function(result) {
      console.log(result);
      //imposto i valori ricevuti, l'ultima posizione dell'array è riservata alla basculante
      states[0]={room:"cucina",state:result[0]};
      states[1]={room:"bagno",state:result[1]};
      states[2]={room:"camera",state:result[2]};
      states[3]={room:"garage",state:result[3]};
      states[4]={room:"basculante",state:result[4]};
      for(let i=0;i<states.length-1;i++){ //fino a states.length-1 perchè l'ultimo elemento è la basculante
        if(states[i].state==1){
          $("#"+states[i].room+"-switch").prop('checked', true);
        }
        else{
          $("#"+states[i].room+"-switch").prop('checked', false);
        }
      }
      //imposto il valore della basculante nello slider
      const slider=document.getElementById("basculante-slider");
      slider.value=(states[states.length-1].state/20);
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