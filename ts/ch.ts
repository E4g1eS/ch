const LOG = true;

function log(toLog: any) {
  if (!LOG) return;

  console.log(toLog);
}

enum Color {
  White,
  Black,
}

const UNICODE_REPRESENTATION = {
  "white-king": "\u2654",
  "white-queen": "\u2655",
  "white-rook": "\u2656",
  "white-bishop": "\u2657",
  "white-knight": "\u2658",
  "white-pawn": "\u2659",
  "black-king": "\u265A",
  "black-queen": "\u265B",
  "black-rook": "\u265C",
  "black-bishop": "\u265D",
  "black-knight": "\u265E",
  "black-pawn": "\u265F",
};

class Vector2 {
  x: number;
  y: number;

  constructor(x: number, y: number)
  {
    this.x = x;
    this.y = y;
  }

  public compare(other: Vector2): boolean
  {
    return (this.x === other.x) && (this.y === other.y);
  }
}

interface IPiece {
  getColor() : Color;
  getNotation(): string;
}

abstract class Piece implements IPiece{
  color: Color;

  constructor(color: Color) {
    this.color = color;
  }

  abstract notation(): string;

  getColor(): Color {
    return this.color;
  }

  getNotation(): string {
      return this.notation();
  }
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
  squares: Array<Array<Piece | null>>;
  readonly size: number;

  constructor() {
    this.size = 8;
    this.initSqaures(); 
  }

  private initSqaures():void {
    this.squares = [];
    for (let i = 0; i < this.size; i++)
    {
      this.squares[i] = [];
      for (let j = 0; j < this.size; j++)
      {
        this.squares[i][j] = null;
      }
    }
  }

  public defaultPosition():void {
    this.initSqaures();

    // WHITE
    this.squares[0][0] = new Rook(Color.White);
    this.squares[1][0] = new Knight(Color.White);
    this.squares[2][0] = new Bishop(Color.White);
    this.squares[3][0] = new Queen(Color.White);
    this.squares[4][0] = new King(Color.White);
    this.squares[5][0] = new Bishop(Color.White);
    this.squares[6][0] = new Knight(Color.White);
    this.squares[7][0] = new Rook(Color.White);

    this.squares[0][1] = new Pawn(Color.White);
    this.squares[1][1] = new Pawn(Color.White);
    this.squares[2][1] = new Pawn(Color.White);
    this.squares[3][1] = new Pawn(Color.White);
    this.squares[4][1] = new Pawn(Color.White);
    this.squares[5][1] = new Pawn(Color.White);
    this.squares[6][1] = new Pawn(Color.White);
    this.squares[7][1] = new Pawn(Color.White);

    // BLACK
    this.squares[0][7] = new Rook(Color.Black);
    this.squares[1][7] = new Knight(Color.Black);
    this.squares[2][7] = new Bishop(Color.Black);
    this.squares[3][7] = new Queen(Color.Black);
    this.squares[4][7] = new King(Color.Black);
    this.squares[5][7] = new Bishop(Color.Black);
    this.squares[6][7] = new Knight(Color.Black);
    this.squares[7][7] = new Rook(Color.Black);

    this.squares[0][6] = new Pawn(Color.Black);
    this.squares[1][6] = new Pawn(Color.Black);
    this.squares[2][6] = new Pawn(Color.Black);
    this.squares[3][6] = new Pawn(Color.Black);
    this.squares[4][6] = new Pawn(Color.Black);
    this.squares[5][6] = new Pawn(Color.Black);
    this.squares[6][6] = new Pawn(Color.Black);
    this.squares[7][6] = new Pawn(Color.Black);
  }
}

interface IGame {
  newGame(): void;
  size(): number;
  getBoardState(): Array<Array<IPiece | null>>;
  getActiveSquare(): Vector2 | null;
  clicked(position: Vector2): void;
}

class Game implements IGame {
  private board: Board;
  private activeSquare: Vector2 | null;

  constructor() {
    this.board = new Board();
    this.activeSquare = null;
  }

  public newGame(): void {
    this.board.defaultPosition();
  }

  public size(): number {
    return this.board.size;
  }

  public getBoardState(): Array<Array<IPiece | null>> {
    return this.board.squares;
  }

  getActiveSquare(): Vector2 | null {
    return this.activeSquare;
  }

  public clicked(position: Vector2): void {

    if (this.activeSquare === null)
    {
      if (this.board.squares[position.x][position.y] === null) return;

      this.activeSquare = position;
    }

    else {
      if (position.compare(this.activeSquare)) this.activeSquare = null;
    }
  }
}

class Renderer {
  game: IGame;
  divContainer: HTMLDivElement;
  squares: HTMLDivElement[][]

  constructor(game: IGame, divContainer: HTMLDivElement) {
    this.game = game;
    this.divContainer = divContainer;
    this.initSquares();
  }

  private initSquares(): void {
    let size = this.game.size();
    this.squares = [];

    for (let i = 0; i < size; i++)
    {
      this.squares[i] = [];

      let column = document.createElement("div");
      column.classList.add("chessboard-column");
      this.divContainer.appendChild(column);

      for (let j = 0; j < size; j++)
      {
        this.squares[i][j] = document.createElement("div");
        this.squares[i][j].classList.add("chessboard-square");
        
        if (((i + (j % 2)) % 2) === 0)
        {
          this.squares[i][j].classList.add("chessboard-square-black");
        }
        
        else
        {
          this.squares[i][j].classList.add("chessboard-square-white");
        }

        this.squares[i][j].addEventListener("click", () => {
          this.clickedAtSquare(new Vector2(i, j));
        });

        column.appendChild(this.squares[i][j]);
      }
    }
  }

  public render(): void {
    let state = this.game.getBoardState();

    let size = this.game.size();
    for (let x = 0; x < size; x++)
    {
      for (let y = 0; y < size; y++)
      {
        this.squares[x][y].classList.remove("chessboard-square-highlighted");
        this.renderSquare(this.squares[x][y], state[x][y]);
      }
    }

    let activeSquare = this.game.getActiveSquare();
    if (activeSquare !== null)
    {
      this.squares[activeSquare.x][activeSquare.y].classList.add("chessboard-square-highlighted");
    }

    log(this);
  }

  private renderSquare(square : HTMLDivElement, piece : IPiece | null): void {

    if (piece === null)
    {
      square.innerText = "";
      square.classList.remove("white-piece");
      square.classList.remove("black-piece");
     return; 
    }

    switch(piece.getNotation())
    {
      case "K":
        square.innerText = UNICODE_REPRESENTATION["black-king"];
        break;
      case "Q":
        square.innerText = UNICODE_REPRESENTATION["black-queen"];
        break;
      case "R":
        square.innerText = UNICODE_REPRESENTATION["black-rook"];
        break;
      case "B":
        square.innerText = UNICODE_REPRESENTATION["black-bishop"];
        break;
      case "N":
        square.innerText = UNICODE_REPRESENTATION["black-knight"];
        break;
      case "P":
        square.innerText = UNICODE_REPRESENTATION["black-pawn"];
        break;
    }

    switch(piece.getColor())
    {
      case Color.White:
        square.classList.remove("black-piece");
        square.classList.add("white-piece");
        break;

      case Color.Black:
        square.classList.add("black-piece");
        square.classList.remove("white-piece");
        break;
    }
  }

  private clickedAtSquare(position : Vector2): void {
    log(`Clicked (${position.x},${position.y})`);
    this.game.clicked(position);
    this.render();
  }
}

let renderer: Renderer;

function main() {
  log("Starting...");

  const game = new Game();
  game.newGame();

  const div = document.createElement("div");
  div.classList.add("chessboard");
  document.body.appendChild<HTMLDivElement>(div);

  renderer = new Renderer(game, div);
  renderer.render();
}

document.addEventListener("DOMContentLoaded", main);
