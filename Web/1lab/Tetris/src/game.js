export default class Tetris{
    points = 0;
    rangs = 0;
    boardWeight = 10;
    boardHeight = 20;
    field = this.newBoard(this.boardHeight, this.boardWeight);
    out = false;
    item = this.newItem();
    comingItem = this.newItem();

    static score = {
        '1': 60,
        '2': 170,
        '3': 310,
        '4': 1000
    };

    level(){
        return Math.floor(this.rangs / 10);
    }

    newItem(){
        const rand = Math.floor(Math.random() * 7);
        const option = '8142579'[rand];
        const item = {x: 0, y: 0};
        switch (option){
            case "1":
                item.bloc = [
                [0,0,0,0],
                [1,1,1,1],
                [0,0,0,0],
                [0,0,0,0]
                ];
                break;
            case "8":
                item.bloc = [
                [8,8],
                [8,8]
                ];
                break;
            case "4":
                item.bloc = [
                [0,4,0],
                [4,4,4],
                [0,0,0]
                ];
                break;
            case "2":
                item.bloc = [
                [2,2,0],
                [0,2,2],
                [0,0,0]
                ];
                break;
            case "5":
                item.bloc = [
                [0,5,5],
                [5,5,0],
                [0,0,0]
                ];
                break;
            case "7":
                item.bloc = [
                [7,7,0],
                [0,7,0],
                [0,7,0]
                ];
                break;
            case "9":
                item.bloc = [
                [0,9,0],
                [0,9,0],
                [9,9,0]
                ];
                break;
        }
        item.x = Math.floor((this.boardWeight - item.bloc[0].length) / 2);
        item.y = 0;
        return item;
    }

    turnItem(){
        const bloc = this.item.bloc;
        const lenbloc = bloc.length;
        const replace = [];
        for (let index = 0; index < lenbloc; index++){
            replace[index] = new Array(lenbloc).fill(0);
        }
        for (let y = 0; y < lenbloc; y++){
            for (let x = 0; x < lenbloc; x++){
                replace[x][y] = bloc[lenbloc - y - 1][x];
            }
        }
        this.item.bloc = replace;
        if (this.Conflict()){
            this.item.bloc = bloc;
        }
    }

    goRight(){
        this.item.x += 1;
        if (this.Conflict()){
            this.item.x -= 1;
        }
    }

    goLeft(){
        this.item.x -= 1;
        if (this.Conflict()){
            this.item.x += 1;
        }
    }

    goDown(){
        if (this.out) return;
        this.item.y += 1;
        if (this.Conflict()){
            this.item.y -= 1;
            this.fixItem();
            const deletedRangs = this.deleteRands();
            this.upgratePoints(deletedRangs);
            this.upgrate();
        }
        if (this.Conflict()){
            this.out = true;
        }
    }

    Conflict(){
        const { y: itemY, x: itemX, bloc} = this.item;
        for (let y = 0; y < bloc.length; y++){
            for (let x = 0; x < bloc[y].length; x++){
                if (
                    bloc[y][x] && 
                    ((this.field[itemY + y] === undefined ||
                        this.field[itemY + y][itemX + x] === undefined) ||
                        this.field[itemY + y][itemX + x])
                ) return true;
            }
        }
        return false;
    }

    fixItem(){
        const { y: itemY, x: itemX, bloc} = this.item;
        for (let y = 0; y < bloc.length; y++){
            for (let x = 0; x < bloc[y].length; x++){
                if (bloc[y][x]) {
                   this.field[itemY + y][itemX + x] = bloc[y][x]; 
                }
            }
        }
    }

    upgrate(){
        this.item = this.comingItem;
        this.comingItem = this.newItem();
    }

    upgratePoints(deletedRangs){
        if (deletedRangs > 0){
            this.points += Tetris.score[deletedRangs] * (this.level() + 1);
            this.rangs += deletedRangs;
        }
    }

    deleteRands(){
        let deletedRangs = []; 
        for (let y = this.boardHeight - 1; y >= 0; y--){
            let itemCount = 0;
            for (let x = 0; x < this.boardWeight; x++){
                if (this.field[y][x]) itemCount++;
            }
            if (itemCount === 0) break;
            else if (itemCount < this.boardWeight) continue;
            else deletedRangs.unshift(y);
        } 
        for (let i of deletedRangs){
            this.field.splice(i,1);
            this.field.unshift(new Array(this.boardWeight).fill(0));
        }
        return deletedRangs.length;
    }

    status(){
        const gameboard = this.newBoard(this.boardHeight,this.boardWeight);
        const { y: itemY, x: itemX, bloc } = this.item;
        for (let y = 0; y < this.field.length; y++){
            gameboard[y] = [];
            for (let x = 0; x < this.field[y].length; x++){
                gameboard[y][x] = this.field[y][x];
            }
        }
        for (let y = 0; y < bloc.length; y++){
            for (let x = 0; x < bloc[y].length; x++){
                if (bloc[y][x]){
                    gameboard[itemY + y][itemX + x] = bloc[y][x];
                }
            }
        }
        return {
            points: this.points,
            lvl: this.level(),
            rangs: this.rangs,
            comingItem: this.comingItem,
            gameboard,
            gameOver: this.out
        };
    }

    newBoard(yHeigth,xWidth){
        const gameboard = [];
        for (let y = 0; y < yHeigth; y++){
            gameboard[y] = [];
            for (let x = 0; x < xWidth; x++)
            gameboard[y][x] = 0;
        }
        return gameboard;
    }
}