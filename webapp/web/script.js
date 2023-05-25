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
      states[4]={room:"allarme",state:result[4]};
      states[5]={room:"basculante",state:result[5]};
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
setInterval(getTemperature, 10000);//richiede la temperatura ogni 10 secondi
var waitTime=0;
var preValue=0;
function getBasculante(){
  const slider=document.getElementById("basculante-slider");
  value=slider.value;
  if(states[4].state==1){
    if(value>0){
      eel.alarm();
    }
    return;
  }
  $("#submit-button").prop('disabled', true);
  waitTime= Math.abs(value-preValue)*1600; //ogni 20% aspetta 1.5 secondi
  preValue=value;
  eel.setBasculante(value);
  setTimeout(() => {
    $("#submit-button").prop('disabled', false);
  }, waitTime);
}
function showModal() {
  const modal=document.getElementById("modal");
  modal.style.display="flex";
  const alarmSwitch=document.getElementById("allarme-switch");
  if(alarmSwitch.checked)
    alarmSwitch.checked=false;
  else
    alarmSwitch.checked=true;
}
function hideModal(){
  const modal=document.getElementById("modal");
  modal.style.display="none";
}
function alarm(){
  psw=document.getElementById("psw").value;
  if(psw!="1234"){
    hideModal();
    alert("Password sbagliata!");
    return;
  }
  hideModal();
  const alarmSwitch=document.getElementById("allarme-switch");
  if(alarmSwitch.checked)
    alarmSwitch.checked=false;
  else
    alarmSwitch.checked=true;
  if(states[4].state==0){
    states[4].state=1;
    const slider=document.getElementById("basculante-slider");
    slider.value=0;
    eel.setBasculante(0);
  }
  else{
    states[4].state=0;
    eel.stopAlarm();
  }
  eel.toggleAlarm();
}