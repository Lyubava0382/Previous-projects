class SpriteManager {
    constructor() {
        this.image = new Image(); // рисунок с объектами
        this.sprites = []; // массив объектов для отображения
        this.imgLoaded = false; // изображения загружены
        this.jsonLoaded = false; // JSON загружен
    }

    // загрузка атласа изображения, atlasJson - путь к файлу атласа в формате JSON, путь к ищображению - atlasImg
    loadAtlas(atlasJson, atlasImg) {
        var request = new XMLHttpRequest(); // подготовить запрос на разбор атласа
        request.onreadystatechange = function () {
            if (request.readyState === 4 && request.status === 200) {
                spriteManager.parseAtlas(request.responseText); // успешно получили атлас и парсим его
            }
        };
        request.open("GET", atlasJson, true); // асинхронный запрос на разбор атласа
        request.send(); // отправили запрос
        this.loadImg(atlasImg); // загрузка изображения
    }sprites

    loadImg(imgName) { // загрузка изображения (imgName - путь к зображению атласа)
        this.image.onload = function () {
            spriteManager.imgLoaded = true; // когда изображение загружено - установить true
        };
        this.image.src = imgName; // загрузка изображения,
        // полю src присваивается путь к изображению, после чего JS начинает загрузку изображения
    }

    parseAtlas(atlasJSON) { // разобрать атлас с объектами
        var atlas = JSON.parse(atlasJSON);
        for (var name in atlas.frames) { // проход по всем именам в frames
            var frame = atlas.frames[name].frame; // получение спрайта и сохранение в frame
            // сохранение характеристик frame в виде объекта
            this.sprites.push({name: name, x: frame.x, y: frame.y, w: frame.w, h: frame.h});
        }
        this.jsonLoaded = true; // когдра разобрали весь атлас - true
    }

    // принимает контекст, имя отображаемого объекта и координаты на карте, где объект необходимо отобразить
    drawSprite(ctx, name, x, y) {

        // если изображение не загружено, то повторить запрос через 100 мсек
        if (!this.imgLoaded || !this.jsonLoaded) {
            setTimeout(function () {
                spriteManager.drawSprite(ctx, name,  x, y);
            }, 100);
        } else {
            var sprite = this.getSprite(name); // получить спрайт по имени
            if(!mapManager.isVisible(x, y, sprite.w, sprite.h))
                return; // не рисуем за пределами видимой зоны

            // сдвигаем видимую зону
            x -= mapManager.view.x;
            y -= mapManager.view.y;
            // отображаем спрайт на холсте
            ctx.drawImage(this.image, sprite.x, sprite.y, sprite.w, sprite.h, x, y, sprite.w, sprite.h);
        }
    }

    getSprite(name) { // получить объект по имени
        for (var i = 0; i < this.sprites.length; i++) {
            var s = this.sprites[i];
            if (s.name === name) // имя совпало - вернуть объект
                return s;
        }
        return null; // не нашли
    }

    drawPlayerHealth(ctx, player) {
        let health = player.health;
        let heart_size = 15;
        for (let i = 0; i < 5; i ++) {
            if (health - 1 > 0) {
                health --;
                let sprite = this.getSprite('heart_full');
                ctx.drawImage(this.image, sprite.x, sprite.y, sprite.w, sprite.h, 165 + i * heart_size, 10, sprite.w, sprite.h);
            } else if (health - 1 === 0) {
                health --;
                let sprite = this.getSprite('heart_full');
                ctx.drawImage(this.image, sprite.x, sprite.y, sprite.w, sprite.h, 165 + i * heart_size, 10, sprite.w, sprite.h);
            } else if (health - 0.5 > 0) {
                health -= 0.5;
                let sprite = this.getSprite('heart_half');
                ctx.drawImage(this.image, sprite.x, sprite.y, sprite.w, sprite.h, 165 + i * heart_size, 10, sprite.w, sprite.h);
            } else if (health - 0.5 === 0) {
                health -= 0.5;
                let sprite = this.getSprite('heart_half');
                ctx.drawImage(this.image, sprite.x, sprite.y, sprite.w, sprite.h, 165 + i * heart_size, 10, sprite.w, sprite.h);
            } else if (health === 0) {
                let sprite = this.getSprite('heart_empty');
                ctx.drawImage(this.image, sprite.x, sprite.y, sprite.w, sprite.h, 165 + i * heart_size, 10, sprite.w, sprite.h);
            }
        }
    }

    drawCoins(ctx, player) {
        ctx.fillStyle = "#f1e4f5";
        ctx.font = "normal 18px PixelarRegular";
        let coins = player.coins;
        let x = 190;
        if (coins >= 10 && coins < 100) {
            x -= 10;
        } else if (coins >= 100 && coins < 1000) {
            x -= 20;
        }
        ctx.fillText(coins + " coins", x, 40);
    }
    drawKey(ctx, player) {
        let key = player.key;
        let sprite = this.getSprite('key');
         if (key){
            ctx.drawImage(this.image, sprite.x, sprite.y, sprite.w, sprite.h, 220, 50, sprite.w, sprite.h);
        }
        }

    drawHealth(ctx, obj) {
        let health = obj.health;
        let heart_size = 5;

        if(!mapManager.isVisible(obj.pos_x, obj.pos_y, heart_size, heart_size))
            return;
        let x = obj.pos_x - mapManager.view.x;
        let y = obj.pos_y -  mapManager.view.y;

        let max = Math.round(health + 0.5);

        for (let i = 0; i < max; i ++) {
            if (health - 1 > 0) {
                health --;
                let sprite = this.getSprite('heart_full');
                ctx.drawImage(this.image, sprite.x, sprite.y, sprite.w, sprite.h,
                    x - 10 + i * heart_size, y - obj.size_y / 2 - 10, sprite.w, sprite.h);
            } else if (health - 1 === 0) {
                health --;
                let sprite = this.getSprite('heart_full');
                ctx.drawImage(this.image, sprite.x, sprite.y, sprite.w, sprite.h,
                    x - 10 + i * heart_size, y - obj.size_y / 2 - 10, sprite.w, sprite.h);
            } else if (health - 0.5 > 0) {
                health -= 0.5;
                let sprite = this.getSprite('heart_half');
                ctx.drawImage(this.image, sprite.x, sprite.y, sprite.w, sprite.h,
                    x - 10 + i * heart_size, y - obj.size_y / 2 - 10, sprite.w, sprite.h);
            } else if (health - 0.5 === 0) {
                health -= 0.5;
                let sprite = this.getSprite('heart_half');
                ctx.drawImage(this.image, sprite.x, sprite.y, sprite.w, sprite.h,
                    x - 10 + i * heart_size, y - obj.size_y / 2 - 10, sprite.w, sprite.h);
            }
        }
    }

    endGame(ctx){
        ctx.fillStyle = "#758520";
        ctx.globalAlpha = 0.7;
        ctx.fillRect(0, 0, 240, 240);

        ctx.globalAlpha = 1.0;
        ctx.fillStyle = "#e9fc82";
        ctx.font = "normal 20px PixelarRegular";
        ctx.fillText("Game over!", 90, 70);
        ctx.fillText("Try again", 90, 130);
        ctx.fillText(" [ENTER]", 90, 190);
    }

    win(ctx){
        ctx.fillStyle = "#758520";
        ctx.globalAlpha = 0.7;
        ctx.fillRect(0, 0, 240, 240);

        ctx.globalAlpha = 1.0;
        ctx.fillStyle = "#e9fc82";
        ctx.font = "normal 20px PixelarRegular";
        ctx.fillText("You win", 90, 70);
        ctx.fillText("Congratulation!", 80, 130);
        ctx.fillText("  [ENTER]", 90, 190);
    }

}