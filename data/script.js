document.getElementById('actionBtn').addEventListener('click', () => {
    const output = document.getElementById('output');
    output.innerText = "Drawing card...";
    
    // Example fetch to get data from ESP32 background APIs later
    fetch('/api/draw')
        .then(response => response.text())
        .then(data => {
            output.innerText = data;
        })
        .catch(err => {
            output.innerText = "Error contacting ESP32 server.";
        });
});