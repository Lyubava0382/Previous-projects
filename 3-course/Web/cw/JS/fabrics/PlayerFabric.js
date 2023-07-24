class PlayerFabric {
    constructor() {
    }
    create(x, y, w, h, name) {
        return new Player(x, y, w, h, name);
    }
}