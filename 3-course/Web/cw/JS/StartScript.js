document.addEventListener('DOMContentLoaded', function() {
    loadLeaderboard();
})
function loadLeaderboard() {
    let tmp = localStorage['game.leaderBoard'];
    const tableBox = document.getElementById('leaderboard-results');

    if (!tmp) { // if leaderboard is empty
        let p = document.createElement('p');
        p.innerHTML = 'Nobody has played yet';
        p.classList.add('leaderboard-string')
        tableBox.appendChild(p);
    } else {
        let arr = JSON.parse(localStorage.getItem('game.leaderBoard'));
        let newStr = '';
        let len = arr.length;
        if (len > 10) len = 10;

        for(let i = 0; i < len; i++){
            newStr = newStr + (i+1) + '. ' + arr[i][0] + ': ' + arr[i][1] + '<br>';
        }
        let p = document.createElement('p');
        p.innerHTML = newStr;
        p.classList.add('leaderboard-string')
        tableBox.appendChild(p);
    }
}
function store(form) {
    localStorage['username.game'] = form.inputName.value;
}