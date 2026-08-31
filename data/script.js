const cardquestion = document.querySelector('#questioncard')
const choiceA = document.querySelector('#A')
const choiceB = document.querySelector('#B')
const choiceC = document.querySelector('#C')
const choiceD = document.querySelector('#D')


function loadNewQuestion() {
    fetch('/textQAA')
        .then(res => res.json())
        .then(data => {
            // We do something here for the data
            // this fetch can be done only once
    
            cardquestion.textContent = data.question
            choiceA.textContent = data.a
            choiceB.textContent = data.b
            choiceC.textContent = data.c
            choiceD.textContent = data.d
        })
        .catch(err => console.error('Error fetching question'))
}


document.getElementById('button-next').addEventListener('click', loadNewQuestion);

window.addEventListener('DOMContentLoaded', loadNewQuestion)