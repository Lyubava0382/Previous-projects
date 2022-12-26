import Tetris from './src/game.js';
import GUI from './src/gui.js';
import ControlUnit from './src/controlUnit.js';
const main = document.querySelector('#main');
const tetris = new Tetris();
const width = 450;
const height = 450;
const bar = 20;
const column = 10;
const gui = new GUI(main, width, height, bar, column);
const controlUnit = new ControlUnit(tetris, gui);
window.tetris = tetris;
window.gui = gui;
window.controlUnit = controlUnit;

gui.displayStart(tetris.status());

