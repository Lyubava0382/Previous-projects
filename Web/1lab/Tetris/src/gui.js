export default class GUI{
    static clrs = {
        '1': 'cyan',
        '8': 'yellow',
        '4': 'purple',
        '2': 'red',
        '5': 'darkblue',
        '7': 'orange',
        '9': 'green'
    };
    constructor(component, width, height, bar, column){
        this.component = component;
        this.height = height;
        this.width = width;
        this.canvas = document.createElement('canvas');
        this.canvas.height = this.height;
        this.canvas.width = this.width;
        this.context = this.canvas.getContext('2d');
        this.component.appendChild(this.canvas);
        this.gameboardFrameWidth = 4;
        this.gameboardX = this.gameboardFrameWidth;
        this.gameboardY = this.gameboardFrameWidth;
        this.gameboardWidth = (this.width / 2);
        this.gameboardHeight = this.height;
        this.itemH = this.gameboardHeight / bar;
        this.itemW = this.gameboardWidth / column;
        this.gameboardInW = this.gameboardWidth - this.gameboardFrameWidth * 2;
        this.gameboardInH = this.gameboardHeight - this.gameboardFrameWidth * 2;
        this.resumeX = this.gameboardWidth + 10;
        this.resumeY = 0;
        this.resumeWidth = this.width / 3;
        this.resumeHeight = this.height;
    }

    display(condition){
        this.emptyBoard();
        this.displayGameboard(condition);
        this.displayResume(condition);
    }

    emptyBoard(){
        this.context.clearRect(0,0,this.width,this.height);
    }

    displayGameboard({gameboard}){
        this.context.fillStyle = 'rgba(248, 205, 250, 0.8)';;
        this.context.fillRect(0, 0, this.gameboardWidth + 5, this.gameboardHeight + 5);
        for (let y = 0; y < gameboard.length; y++){
            const bar = gameboard[y];
            for (let x = 0; x < bar.length; x++){
                const item = bar[x];
                if (item){
                    this.displayItem(this.gameboardX + x * this.itemW, this.gameboardY + y * this.itemH, this.itemW, this.itemH, GUI.clrs[item]);
                }
            }
        }
        this.context.strokeStyle = 'black';
        this.context.lineWidth = this.gameboardFrameWidth;
        this.context.strokeRect(0, 0, this.gameboardWidth + 5, this.gameboardHeight + 5)
    }

    displayItem(x,y,itemW,itemH,clr){
        this.context.fillStyle = clr;
        this.context.strokeStyle = 'white';
        this.context.lineWidth = 2;
        this.context.fillRect(x, y, itemW, itemH);
        this.context.strokeRect(x, y, itemW, itemH);
    }


displayResume({ lvl, points, rangs, comingItem}){
    this.context.textAlign = 'start';
    this.context.textBaseline = 'top';
    this.context.fillStyle = 'black';
    this.context.font = '14px "Press Start 2P"';
    this.context.fillText('Score: ' + points, this.resumeX,this.resumeY);   
    this.context.fillText('Rangs: ' + rangs, this.resumeX,this.resumeY + 24); 
    this.context.fillText('Level: ' + lvl, this.resumeX,this.resumeY + 48); 
    this.context.fillText('Next:', this.resumeX,this.resumeY + 96); 
    for (let y = 0; y < comingItem.bloc.length; y++){
        for (let x = 0; x < comingItem.bloc[y].length; x++){
        const item = comingItem.bloc[y][x];
        if (item){
            this.displayItem(
                this.resumeX + (x * this.itemW * 0.7 + 20),
                this.resumeY + (y * this.itemH * 0.7) + 130,
                this.itemW * 0.7,
                this.itemH * 0.7,
                GUI.clrs[item]
            );
        }
        }
    }
}

displayStart(){
    this.context.fillStyle = 'black';
    this.context.font = '15px "Press Start 2P"';
    this.context.textAlign = 'center';
    this.context.textBaseline = 'middle';
    this.context.fillText('Press [ENTER] to start', this.width * 0.5, this.height * 0.5);
}

displayStop(){
    this.context.fillStyle = 'rgba(248, 205, 250, 0.25)';
    this.context.fillRect(0, 0, this.width, this.height);
    this.context.fillStyle = 'black';
    this.context.font = '15px "Press Start 2P"';
    this.context.textAlign = 'center';
    this.context.textBaseline = 'middle'; 
    this.context.fillText('Press [ENTER] to continue', this.width * 0.5, this.height * 0.5);
}

displayOver({points}){
    this.emptyBoard();
    this.context.fillStyle = 'black';
    this.context.font = '15px "Press Start 2P"';
    this.context.textAlign = 'center';
    this.context.textBaseline = 'middle';
    this.context.fillText('GAME OVER', this.width * 0.5, this.height * 0.5 - 50);
    this.context.fillText('Score: ' + points, this.width * 0.5, this.height * 0.5 );
}
}