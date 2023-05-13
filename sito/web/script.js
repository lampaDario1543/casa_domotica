isOn=true;
function cucina() {
    eel.cucina(isOn)((setdata) => {
        isOn=!isOn;
        document.getElementById("cucina").style.backgroundColor = isOn? "green" : "red";
        console.log(setdata);
        //document.getElementById("heading").innerText = setdata; //imposta il testo con il testo ricevuto da python
    })
}