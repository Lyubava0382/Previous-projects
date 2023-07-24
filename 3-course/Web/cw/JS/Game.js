let mapManager = new MapManager();
// объект для управления спрайтами (объектами)
let spriteManager = new SpriteManager();
let physicManager = new PhysicManager();
let eventsManager = new EventsManager();
let soundManager = new SoundManager();
let gameManager = new GameManager();


function updateWorld() {
    gameManager.update();
    if (gameManager.next_level) {
        gameManager.loadForSecondLevel();
        gameManager.next_level = false;
    }
}

gameManager.play();




