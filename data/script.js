const cardquestion = document.querySelector("#questioncard")
const choiceA = document.querySelector("#A")
const choiceB = document.querySelector("#B")
const choiceC = document.querySelector("#C")
const choiceD = document.querySelector("#D")


fetch('/textQAA')
    .then(res => { response.text() })
    .then(data => {
        // We do something here for the data
        // this fetch can be done only once
    })



document.getElementById('actionBtn').addEventListener('click', () => {
    // Example fetch to get data from ESP32 background APIs later
    fetch('/textQAA')
        .then(response => { response.text() })
        .then(data => {
            output.innerText = data;
        })
        .catch(err => {
            output.innerText = "Error contacting ESP32 server.";
        });
});



