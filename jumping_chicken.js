// Hauptvariablen für das Spiel
const canvas = document.getElementById("gameCanvas");
const ctx = canvas.getContext("2d");

const SCREEN_WIDTH = canvas.width;
const SCREEN_HEIGHT = canvas.height;

const CHICKEN_WIDTH = 64;
const CHICKEN_HEIGHT = 64;
const EGG_WIDTH = 32;
const EGG_HEIGHT = 32;
const JUMP_HEIGHT = 150;

let chickenX = SCREEN_WIDTH / 2 - CHICKEN_WIDTH / 2;
let chickenY = SCREEN_HEIGHT / 2 - CHICKEN_HEIGHT / 2;
let isJumping = false;
let jumpOffset = 0;
let jumpDirection = -1;

let eggs = []; // Array, das die Positionen der Eier speichert

// Lade die Bilder für Huhn und Ei
const chickenImg = new Image();
chickenImg.src = 'chicken.png';

const eggImg = new Image();
eggImg.src = 'egg.png';

// Sound für den Sprung
const jumpSound = new Audio('jump_sound.wav');

// Event Listener für Tastendrücke
window.addEventListener('keydown', (event) => {
    if (!isJumping) {
        isJumping = true;
 
        // Spiele den Sprung-Sound ab
        jumpSound.play();

        // Platziere das Ei direkt unterhalb des Huhns
        let egg = {
            x: chickenX + (CHICKEN_WIDTH - EGG_WIDTH) / 2,
            y: chickenY + CHICKEN_HEIGHT
        };
        eggs.push(egg);
    }
});

// Haupt-Render-Loop
function gameLoop() {
    ctx.clearRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT); // Bildschirm leeren

    // Zeichne das Huhn
    ctx.drawImage(chickenImg, chickenX, chickenY + jumpOffset, CHICKEN_WIDTH, CHICKEN_HEIGHT);

    // Zeichne alle Eier
    eggs.forEach(egg => {
        ctx.drawImage(eggImg, egg.x, egg.y, EGG_WIDTH, EGG_HEIGHT);
    });

    if (isJumping) {
        jumpOffset += jumpDirection * 10;
        if (jumpOffset <= -JUMP_HEIGHT || jumpOffset >= 0) {
            jumpDirection *= -1;
        }
        if (jumpOffset === 0) {
            isJumping = false;

            // Bewege das Huhn nach dem Sprung an eine zufällige Position
            chickenX = Math.random() * (SCREEN_WIDTH - CHICKEN_WIDTH);
            chickenY = Math.random() * (SCREEN_HEIGHT - CHICKEN_HEIGHT);
        }
    }

    requestAnimationFrame(gameLoop); // Wiederhole die Schleife
}

// Starte das Spiel
chickenImg.onload = function() {
    gameLoop();
}
