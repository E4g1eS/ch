const LOG = true;

function log(toLog: any) {
  if (!LOG) return;

  console.log(toLog);
}

enum Color {
  White,
  Black,
}

interface Vector2 {
  x: number;
  y: number;
}

abstract class Piece {
  color: Color;

  constructor(color: Color) {
    this.color = color;
  }

  abstract notation(): string;
}

class King extends Piece {
  notation(): string {
    return "K";
  }
}
class Queen extends Piece {
  notation(): string {
    return "Q";
  }
}
class Rook extends Piece {
  notation(): string {
    return "R";
  }
}
class Bishop extends Piece {
  notation(): string {
    return "B";
  }
}
class Knight extends Piece {
  notation(): string {
    return "N";
  }
}
class Pawn extends Piece {
  notation(): string {
    return "P";
  }
}

class Board {
  squares: Piece[][];
}

interface IGame {}

class Game implements IGame {
  board: Board;
}

class Renderer {
  game: IGame;

  constructor(game: IGame) {
    this.game = game;
  }
}

function main() {
  log("Starting...");
}

document.addEventListener("DOMContentLoaded", main);
