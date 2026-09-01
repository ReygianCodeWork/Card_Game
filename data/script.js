const cardquestion = document.querySelector('#questioncard')
const choiceA = document.querySelector('#A')
const choiceB = document.querySelector('#B')
const choiceC = document.querySelector('#C')
const choiceD = document.querySelector('#D')


function loadNewQuestion(pressed) {
    if (pressed) {
        fetch('/textPress', {
            method: 'POST',
            headers: {
                'Content-Type': 'text/plain'
            },
            body: 'press'
        })
            .then(res => {
                if (!res.ok) {
                    throw new Error(`HTTP ERROR! Status: ${res.status}`)
                }
                return res.text()
            })
            .then(result => {

                console.log('Success', result)
                fetchCard()

            }).catch(err => {
            console.error('Error: ', err)
        })
    }
    else {
        fetchCard()
    }
}

function fetchCard() {
    fetch('/textQAA')
        .then(res => res.json())
        .then(data => {
            // We do something here for the data
            // this fetch can be done only once
            if (data.nonext != 'NONEXT') {
                cardquestion.textContent = data.question
                choiceA.textContent = data.a
                choiceB.textContent = data.b
                choiceC.textContent = data.c
                choiceD.textContent = data.d
            }
            else {
                alert(`No next card. count: ${data.count}`)
            }
        })
        .catch(err => console.error('Error fetching question'))
}

// We are going to send a data back to our ESP32 webserver
// we are going to use the fetch method to send an instruction
// that the next button is pressed. The server detects this and send the
// next question card.

document.getElementById('button-next').addEventListener('click', () => loadNewQuestion(true));

window.addEventListener('DOMContentLoaded', () => loadNewQuestion(false))