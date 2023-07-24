function distance(obj1, obj2) {
    let dx = obj1.pos_x - obj2.pos_x;
    let dy = obj1.pos_y - obj2.pos_y;
    let d = Math.sqrt(dx**2 + dy**2);
    return {
        dx: dx,
        dy: dy,
        d:d
    }
}

class Entity {
    constructor(x, y, w, h) {
        this.pos_x = x;
        this.pos_y = y; // позиция объекта
        this.size_x = w;
        this.size_y = h; // размеры объекта
    }
}

// player
class Player extends Entity {
    constructor(x, y, w, h, name, health = 1.0, speed = 1.5, move_x = 0, move_y = 0) {
        super(x, y, w, h);
        this.max_health = health;
        this.health = health;
        this.speed = speed;
        this.move_x = move_x;
        this.move_y = move_y;
        this.name = name;
        this.coins = 0;
        this.force = 0.5;
        this.weapon = new StartWeapon(0, 0, 54, 54, 'start_weapon');
        this.length_of_attack = 50;
        this.left_face = false;
        this.down_face = true;
        this.right_face = false;
        this.up_face = false;
        this.animation_numb = 1;
        this.stop = true;
        this.last_attack = Date.now();
        this.in_attack = false;
        this.alive = true;
        this.time_between_attacks = 0.5;
        this.killed_big_orc = false;
        this.last_step = Date.now();
        this.key = false;
        this.win = false;
    }

    draw(ctx) {
        let side = "down";
        if (this.up_face){
            side = "up";
        }
        else if (this.left_face){
            side = "left";
        }
        else if (this.right_face){
            side = "right";
        } 
        if (this.weapon.animation_numb === 2){
            this.in_attack = false;
            this.weapon.visible = false;
            this.weapon.animation_numb = 0;
        }
        if (this.in_attack) {
            this.weapon.animation_numb = this.weapon.animation_numb % 3 + 1;
            spriteManager.drawSprite(ctx, "weapon_" + side + "_" + this.weapon.animation_numb, this.pos_x, this.pos_y);
        }
        else {
            spriteManager.drawSprite(ctx, "player_" + side + "_" + this.animation_numb, this.pos_x, this.pos_y);
                this.animation_numb = (this.animation_numb) % 4 + 1;
        }
        spriteManager.drawPlayerHealth(ctx, this);
        spriteManager.drawCoins(ctx, this);
        spriteManager.drawKey(ctx, this);
    }

    update() {

        let res = physicManager.updatePlayer(this);
        this.stop = res === "stop";

        let cur_time = Date.now();
        let dt = (cur_time - this.last_step) / 1000.0;
        if (!this.stop && dt > 1.0) {
            soundManager.playWorldSound("../../sounds/player_step.wav", this.pos_x, this.pos_y);
            this.last_step = cur_time;
        }
        if (this.move_x === -1) {
            this.left_face = true;
            this.right_face = false;
            this.up_face = false;
            this.down_face = false;
        } else if (this.move_x === 1){
            this.right_face = true;
            this.left_face = false;
            this.up_face = false;
            this.down_face = false;
        }
        if (this.move_y === 1 || this.move_x === 0 && this.move_y === 0){
            this.down_face = true;
            this.right_face = false;
            this.left_face = false;
            this.up_face = false;
        }
        else if (this.move_y === -1){
            this.down_face = false;
            this.up_face = true;
            this.right_face = false;
            this.left_face = false;
        }
        this.weapon.pos_y = this.pos_y + 5;
    }

    attack() {
        let cur_time = Date.now();
        let dt = (cur_time - this.last_attack) / 1000.0;
        if (dt >= this.time_between_attacks && !this.in_attack) {

            if (this.weapon.name.match(/start_weapon/))
                soundManager.playWorldSound("../../sounds/base_weapon.mp3", this.pos_x, this.pos_y, 0.5);
            else soundManager.playWorldSound("../../sounds/katana.mp3", this.pos_x, this.pos_y);

            this.last_attack = cur_time;

            this.in_attack = true;
            this.weapon.visible = true;
        }
    }

    onTouchEntity(e) {
        if (e.name.match(/coin[\d*]/)) {
            e.take();
            this.coins ++;
            return;
        }
        if (e.name.match(/big_heal[\d*]/)) {
            if (this.health + e.property <= this.max_health) {
                e.take();
                this.health += e.property;
            }
            return;
        }

        if (e.name.match(/door/)) {
            if (this.key) {
                e.take();
                this.win = true;
            }
            return;
        }
    
        if (e.name.match(/treasure[\d*]/)) {
            let res = e.touch();
            if (res.match('taken')){
                if (e.name.match(/treasure2/)) {
                    this.key = true;
                }
                else this.coins += e.property;
            }
                
            return;
        }
        if (e.name.match(/next_level/)) {
            gameManager.next_level = true;
        }
    }

    onTouchEnemy(e) {
        if (e.name.match(/middle_undead[\d*]/)) {
            let res = e.getAttack(this);
            if (res.match('killed')) {
                this.coins++;
                if (this.health < this.max_health)
                    this.health += 0.5;
            }
        } else if (e.name.match(/middle_orc[\d*]/)) {
            let res = e.getAttack(this);
            if (res.match('killed'))
                this.coins += 2;
        } else if (e.name.match(/middle_demon[\d*]/)) {
            let res = e.getAttack(this);
            if (res.match('killed'))
                this.coins += 3;
        } 
    }

    getDamage (obj) {
        if (obj.weapon)
            this.health -= (obj.force + obj.weapon.force);
        else
            this.health -= obj.force;

        if (this.health <= 0) {
            this.alive = false;
        }
    }
}


// weapons
class StartWeapon extends Entity{
    constructor(x, y, w, h, name) {
        super(x, y, w, h);
        this.name = name;
        this.force = 0.5;
        this.visible = false;
        this.left = true;
        this.animation_numb = 0;
    }
    draw(ctx) {
        this.animation_numb = this.animation_numb % 3 + 1;
    }
}


// monsters

class MiddleUndead extends Entity{
    constructor(x, y, w, h, name, health = 2.5,  move_x = 0, move_y = 0) {
        super(x, y, w, h);
        this.health = health;
        this.move_x = move_x;
        this.move_y = move_y;
        this.name = name;
        this.left_face = true;
        this.animation_numb = 1;
    }

    draw(ctx) {
        let side = (this.left_face) ? 'left' : 'right';
        spriteManager.drawSprite(ctx, "middle_undead_" + this.animation_numb, this.pos_x, this.pos_y);
        this.animation_numb = (this.animation_numb) % 3 + 1;
        spriteManager.drawHealth(ctx, this);
    }

    onTouchPlayer(obj) {
    }

    update() {

        if(gameManager.player) {
            let dist = distance(gameManager.player, this);
            if (dist.dx < 0) {
                this.left_face = true;
            } else {
                this.left_face = false;
            }
        }

        let res = physicManager.update(this);
        this.stop = res === "stop";
    }

    getAttack(player) {
        this.health -= (player.force + player.weapon.force);
        if(this.health <= 0) {
            gameManager.laterKill.push(this);
            return 'killed'
        }
        return "alive";
    }
}

class MiddleOrc extends Entity {
    constructor(x, y, w, h, name, health = 2.0, speed = 1, move_x = 0, move_y = 0) {
        super(x, y, w, h);
        this.health = health;
        this.speed = speed;
        this.move_x = move_x;
        this.move_y = move_y;
        this.name = name;
        this.force = 0.5;
        this.left_face = true;
        this.animation_numb = 1;
        this.stop = true;
        this.last_attack = Date.now();
        this.in_attack = false;
        this.time_between_atacks = 3.0;
        this.visible_zone = 50;
        this.last_step = Date.now();
    }

    draw(ctx) {
        let side = (this.left_face) ? 'left' : 'right'
        let side_numb = (this.left_face) ? -1 : 1;
        let attack = (this.in_attack) ? 1 : 0
            spriteManager.drawSprite(ctx, "middle_orc_"  + this.animation_numb, this.pos_x, this.pos_y );
            this.animation_numb = (this.animation_numb) % 5 + 1;
        
        if (attack) {
            this.in_attack = false;
        }
        spriteManager.drawHealth(ctx, this);
    }

    onTouchPlayer(obj) {
        let cur_time = Date.now();
        let dt = (cur_time - this.last_attack) / 1000.0;
        if (dt >= this.time_between_atacks && ! this.in_attack) {
            soundManager.playWorldSound("../../sounds/kus.mp3", obj.pos_x, obj.pos_y);
            this.last_attack = cur_time;
            this.in_attack = true;
            obj.getDamage(this);
        }
    }

    update() {
        this.move_x = 0;
        this.move_y = 0;

        if(gameManager.player) {
            let dist = distance(gameManager.player, this);
            if (dist.d <= this.visible_zone) {
                if (Math.abs(dist.dx) < Math.abs(dist.dy)) {
                    if (dist.dy < 0) {
                        this.move_y = -1;
                    } else {
                        this.move_y = 1;
                    }
                } else {
                    if (dist.dx < 0) {
                        this.move_x = -1;
                    } else {
                        this.move_x = 1;
                    }
                }
            }
        }

        if (this.move_x === -1) {
            this.left_face = true;
        } else if (this.move_x === 1){
            this.left_face = false;
        }

        let res = physicManager.update(this);
        this.stop = res === "stop";

        let cur_time = Date.now();
        let dt = (cur_time - this.last_step) / 1000.0;
        if (!this.stop && dt > 0.9) {
            soundManager.playWorldSound("../../sounds/enemies_step.wav",
                gameManager.player.pos_x, gameManager.player.pos_y);
            this.last_step = cur_time;
        }
    }

    getAttack(player) {
        this.health -= (player.force + player.weapon.force);
        if(this.health <= 0) {
            gameManager.laterKill.push(this);
            return 'killed'
        }
        return 'alive';
    }
}

class MiddleDemon extends Entity {
    constructor(x, y, w, h, name, health = 2.5, speed = 2, move_x = 0, move_y = 0) {
        super(x, y, w, h);
        this.health = health;
        this.speed = speed;
        this.move_x = move_x;
        this.move_y = move_y;
        this.name = name;
        this.force = 0.5;
        this.left_face = false;
        this.down_face = true;
        this.right_face = false;
        this.up_face = false;
        this.animation_numb = 1;
        this.stop = true;
        this.last_attack = Date.now();
        this.in_attack = false;
        this.time_between_atacks = 1.5;
        this.visible_zone = 100;
        this.last_step = Date.now();
    }

    draw(ctx) {
        let side = "down";
        if (this.up_face){
            side = "up";
        }
        else if (this.left_face){
            side = "left";
        }
        else if (this.right_face){
            side = "right";
        } 
        let attack = (this.in_attack) ? 1 : 0
            spriteManager.drawSprite(ctx, "middle_demon_" + side + "_" + this.animation_numb, this.pos_x, this.pos_y );
            this.animation_numb = (this.animation_numb) % 4 + 1;
        if (attack) {
            this.in_attack = false;
        }
        spriteManager.drawHealth(ctx, this);
    }

    onTouchPlayer(obj) {
        let cur_time = Date.now();
        let dt = (cur_time - this.last_attack) / 1000.0;
        if (dt >= this.time_between_atacks && ! this.in_attack) {
            soundManager.playWorldSound("../../sounds/kus.mp3", obj.pos_x, obj.pos_y);
            this.last_attack = cur_time;
            this.in_attack = true;
            obj.getDamage(this);
        }
    }

    update() {
        this.move_x = 0;
        this.move_y = 0;

        if(gameManager.player) {
            let dist = distance(gameManager.player, this);
            if (dist.d <= this.visible_zone) {
                if (Math.abs(dist.dx) < Math.abs(dist.dy)) {
                    if (dist.dy < 0) {
                        this.move_y = -1;
                    } else {
                        this.move_y = 1;
                    }
                } else {
                    if (dist.dx < 0) {
                        this.move_x = -1;
                    } else {
                        this.move_x = 1;
                    }
                }
            }
        }

        if (this.move_x === -1) {
            this.left_face = true;
            this.right_face = false;
            this.up_face = false;
            this.down_face = false;
        } else if (this.move_x === 1){
            this.right_face = true;
            this.left_face = false;
            this.up_face = false;
            this.down_face = false;
        }
        if (this.move_y === 1){
            this.down_face = true;
            this.right_face = false;
            this.left_face = false;
            this.up_face = false;
        }
        else if (this.move_y === -1){
            this.down_face = false;
            this.up_face = true;
            this.right_face = false;
            this.left_face = false;
        } 

        let res = physicManager.update(this);
        this.stop = res === "stop";

        let cur_time = Date.now();
        let dt = (cur_time - this.last_step) / 1000.0;
        if (!this.stop && dt > 0.7) {
            soundManager.playWorldSound("../../sounds/enemies_step.wav",
                gameManager.player.pos_x, gameManager.player.pos_y);
            this.last_step = cur_time;
        }
    }

    getAttack(player) {
        this.health -= (player.force + player.weapon.force);
        if(this.health <= 0) {
            gameManager.laterKill.push(this);
            return 'killed'
        }
        return 'alive';
    }
}


// bonuses
class Coin extends Entity{
    constructor(x, y, w, h, name) {
        super(x, y, w, h);
        this.animation_numb = 1;
        this.name = name;
    }

    draw(ctx) {
        spriteManager.drawSprite(ctx, "coin_" + this.animation_numb, this.pos_x, this.pos_y);
        this.animation_numb = (this.animation_numb) % 4 + 1;
    }
    take() {
        soundManager.playWorldSound("../../sounds/get_coin.wav",
            gameManager.player.pos_x, gameManager.player.pos_y);
        gameManager.laterKill.push(this);
    }

    update(){}
}

class Door extends Entity{
    constructor(x, y, w, h, name) {
        super(x, y, w, h);
        this.animation_numb = 1;
        this.name = name;
    }

    draw(ctx) {
        spriteManager.drawSprite(ctx, "door", this.pos_x, this.pos_y);
    }
    take() {
        soundManager.playWorldSound("../../sounds/get_coin.wav",
            gameManager.player.pos_x, gameManager.player.pos_y);
        gameManager.laterKill.push(this);
    }

    update(){}
}


class BigHeal extends Entity {
    constructor(x, y, w, h, name) {
        super(x, y, w, h);
        this.name = name;
        this.property = 1.0;
    }

    draw(ctx) {
        spriteManager.drawSprite(ctx, "heal", this.pos_x, this.pos_y);
    }
    take() {
        soundManager.playWorldSound("../../sounds/heal.wav",
            gameManager.player.pos_x, gameManager.player.pos_y);
        gameManager.laterKill.push(this);
    }
    update(){}
}

class Treasure extends Entity {
    constructor(x, y, w, h, name) {
        super(x, y, w, h);
        this.name = name;
        this.property = 10.0;
        this.animation_numb = 1;
        this.touched = false;
    }

    draw(ctx) {
        if (this.animation_numb <= 3) {
            spriteManager.drawSprite(ctx, "treasure_" + this.animation_numb, this.pos_x, this.pos_y);
            if (this.touched) this.animation_numb++;
        }

    }
    take() {
        if (this.animation_numb >= 3) {
            soundManager.playWorldSound("../../sounds/get_treasure.wav",
                gameManager.player.pos_x, gameManager.player.pos_y);
            gameManager.laterKill.push(this);
            return 'taken'
        }
        return 'not taken'
    }
    touch () {
        if (this.touched)
           return this.take();
        this.touched = true;
        return 'not taken';
    }
    update(){}
}
class NextLevel extends Entity {
    constructor(x, y, w, h, name) {
        super(x, y, w, h);
        this.name = name;
    }

    draw(ctx) {
        spriteManager.drawSprite(ctx, "next_level", this.pos_x, this.pos_y);

    }
    take() {
        gameManager.next_level = true;
    }
    update(){}
}