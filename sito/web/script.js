cucinaIsOn=true;
function init(){ //inizializza le varibili boolean facendo una richesta tramite python ad arduino, dello stato dei LED
}
init();
function cucina() {
    eel.cucina(cucinaIsOn)(() => {
        console.log("Mandato")
        cucinaIsOn=!cucinaIsOn;
        document.getElementById("cucina").style.backgroundColor = cucinaIsOn? "green" : "red";
    })
}
function showCucina(){
  const modal=document.getElementById("modalCucina");
  modal.style.display="flex";
  $(".cucina-container").show(500);
}

function hideCucina(){
  const modal=document.getElementById("modalCucina");
  $(".cucina-container").hide(500);
  modal.style.display="none";
}

function showGarage(){
  const modal=document.getElementById("modalGarage");
  modal.style.display="flex";
  $(".garage-container").show(500);
}

function hideGarage(){
  const modal=document.getElementById("modalGarage");
  $(".garage-container").hide(500);
    modal.style.display="none";
}
function setStatus(room){
  id="#"+room+"-switch"; //id del checkbox
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