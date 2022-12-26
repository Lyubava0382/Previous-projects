export default class ControlUnit {
    constructor (tetris, gui){
        this.tetris = tetris;
        this.gui = gui;
        this.timeID = null;
        this.process = false;


        document.addEventListener('keydown', this.manageKey.bind(this));
        document.addEventListener('keyup', this.manageKeyUP.bind(this));
        this.gui.displayStart();
    }
    upgrate(){
        this.tetris.goDown();
        this.upgrateGUI();
    }

    play(){
        this.process = true;
        this.timerOn();
        this.upgrateGUI();
    }

    stop(){
        this.process = false;
        this.timerOff();
        this.upgrateGUI();
    }
    
    upgrateGUI(){
        const condition = this.tetris.status();
        if (condition.gameOver){
            this.gui.displayOver(condition);
            localStorage.setItem( localStorage.key(localStorage.length - 1),'' + this.tetris.status().points);
        }
        else if (! this.process){
            this.gui.displayStop();
        } else {
            this.gui.display(condition);
        }
    }

    timerOn(){
        const velocity = 1000 - this.tetris.status().lvl * 100;
        if (!this.timeID){
            this.timeID = setInterval(() => {
                this.upgrate();
            }, velocity > 0 ? velocity : 100);
        }
    }

    timerOff(){
        if (this.timeID){
            clearInterval(this.timeID);
        this.timeID = null;
        }
    }

        manageKey(event){
            switch (event.key){
                case "Enter":
                    if (this.process){
                        this.stop();
                    } else
                    this.play();
                    break;
                case "ArrowLeft":
                    tetris.goLeft();
                    this.upgrateGUI();
                    break;
                case "ArrowUp":
                    tetris.turnItem();
                    this.upgrateGUI();
                    break;
                case "ArrowRight":
                    tetris.goRight();
                    this.upgrateGUI();
                    break;
                case "ArrowDown":
                    tetris.goDown();
                    this.upgrateGUI();
                    break;
            }
        }

        manageKeyUP(event){
            switch (event.key){
                case "ArrowDown":
                    timerOn();
                    break;
            }
        }
    
}